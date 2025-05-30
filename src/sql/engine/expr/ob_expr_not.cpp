/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX SQL_ENG
#include "sql/engine/expr/ob_expr_not.h"

using namespace oceanbase::sql;
using namespace oceanbase::common;

namespace oceanbase
{
namespace sql
{
}
}


ObExprNot::ObExprNot(ObIAllocator &alloc)
    : ObLogicalExprOperator(alloc, T_OP_NOT, N_NOT, 1, NOT_ROW_DIMENSION)
{
}

int ObExprNot::calc_result_type1(ObExprResType &type,
                                 ObExprResType &type1,
                                 ObExprTypeCtx &type_ctx) const
{
  UNUSED(type_ctx);
  int ret = OB_SUCCESS;
  if (NOT_ROW_DIMENSION == row_dimension_) {
    if (ObMaxType == type1.get_type()) {
      ret = OB_ERR_UNEXPECTED;
    } else {
      if ((GET_MIN_CLUSTER_VERSION() >= MOCK_CLUSTER_VERSION_4_2_1_7 && GET_MIN_CLUSTER_VERSION() < CLUSTER_VERSION_4_2_2_0) ||
          (GET_MIN_CLUSTER_VERSION() >= MOCK_CLUSTER_VERSION_4_2_4_0 && GET_MIN_CLUSTER_VERSION() < CLUSTER_VERSION_4_3_0_0) ||
          GET_MIN_CLUSTER_VERSION() >= CLUSTER_VERSION_4_3_2_0) {
        type.set_int32();
      } else {
        type.set_int();
      }
      ObExprOperator::calc_result_flag1(type, type1);
      type.set_scale(DEFAULT_SCALE_FOR_INTEGER);
      type.set_precision(DEFAULT_PRECISION_FOR_BOOL);
      //keep enumset as enumset
    }
  } else {
    ret = OB_ERR_INVALID_TYPE_FOR_OP;
  }
  return ret;
}

int ObExprNot::cg_expr(ObExprCGCtx &expr_cg_ctx,
                       const ObRawExpr &raw_expr,
                       ObExpr &rt_expr) const
{
  int ret = OB_SUCCESS;
  UNUSED(expr_cg_ctx);
  UNUSED(raw_expr);
  if (OB_UNLIKELY(rt_expr.type_ != T_OP_NOT)
      || OB_UNLIKELY(rt_expr.arg_cnt_ != 1)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret));
  } else {
    rt_expr.eval_func_ = &eval_not;
    rt_expr.eval_batch_func_ = &eval_not_batch;
    rt_expr.eval_vector_func_ = &eval_not_vector;
  }
  return ret;
}

int ObExprNot::eval_not(const ObExpr &expr,
                        ObEvalCtx &ctx,
                        ObDatum &expr_datum)
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(expr.args_)
      || OB_UNLIKELY(expr.arg_cnt_ != 1)
      || OB_ISNULL(expr.args_[0])) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret));
  } else {
    // not 表示的参数被加了一个bool表达式，所以逻辑走到这里
    // 参数的值一定是一个int（0或者1）
    ObDatum *param = NULL;
    if (OB_FAIL(expr.args_[0]->eval(ctx, param))) {
      LOG_WARN("failed to eval", K(ret));
    } else if (param->is_null()) {
      expr_datum.set_null();
    } else {
      expr_datum.set_int(param->get_int() == 0);
      LOG_DEBUG("expr not calc result", K(expr_datum.is_null()), K(expr_datum.get_int()));
    }
  }
  return ret;
}

int ObExprNot::eval_not_batch(const ObExpr &expr,
                            ObEvalCtx &ctx,
                            const ObBitVector &skip,
                            const int64_t batch_size)
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(expr.args_)
      || OB_UNLIKELY(expr.arg_cnt_ != 1)
      || OB_ISNULL(expr.args_[0])) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret));
  } else {
    ObBitVector &eval_flags = expr.get_evaluated_flags(ctx);
    if (OB_FAIL(expr.args_[0]->eval_batch(ctx, skip, batch_size))) {
      LOG_WARN("failed to eval", K(ret));
    } else {
      ObDatum *results = expr.locate_batch_datums(ctx);
      for (int64_t i = 0; i < batch_size; ++i) {
        if (skip.at(i) || eval_flags.at(i)) {
          continue;
        }
        ObDatum &datum = expr.args_[0]->locate_expr_datum(ctx, i);
        eval_flags.set(i);
        if (datum.is_null()) {
          results[i].set_null();
        } else {
          results[i].set_int(0 == datum.get_int());
        }
      }
    }
  }
  return ret;
}

template <typename ArgVec, typename ResVec>
static int inner_eval_not_vector(const ObExpr &expr,
                                 ObEvalCtx &ctx,
                                 const ObBitVector &skip,
                                 const EvalBound &bound)
{
  int ret = OB_SUCCESS;
  ArgVec *arg_vec = static_cast<ArgVec *>(expr.args_[0]->get_vector(ctx));
  ResVec *res_vec = static_cast<ResVec *>(expr.get_vector(ctx));
  ObBitVector &eval_flags = expr.get_evaluated_flags(ctx);
  const bool isFixedLenRes = std::is_same<ResVec, IntegerFixedVec>::value;
  int64_t *data_ptr = isFixedLenRes ?
                      const_cast<int64_t *>(reinterpret_cast<const int64_t *>(res_vec->get_payload(0))) :
                      nullptr;
  bool no_skip_no_null = bound.get_all_rows_active() && !arg_vec->has_null();
  if (no_skip_no_null) {
    for (int64_t idx = bound.start(); OB_SUCC(ret) && idx < bound.end(); ++idx) {
      if (isFixedLenRes) {
        data_ptr[idx] = static_cast<int64_t>(0 == arg_vec->get_int(idx));
      } else {
        res_vec->set_int(idx, static_cast<int64_t>(0 == arg_vec->get_int(idx)));
      }
    }
    eval_flags.set_all(bound.start(), bound.end());
  } else {
    for (int64_t idx = bound.start(); OB_SUCC(ret) && idx < bound.end(); ++idx) {
      if (skip.at(idx) || eval_flags.at(idx)) {
        continue;
      } else if (arg_vec->is_null(idx)) {
        res_vec->set_null(idx);
      } else {
        res_vec->set_int(idx, static_cast<int64_t>(0 == arg_vec->get_int(idx)));
      }
      eval_flags.set(idx);
    }
  }
  return ret;
}

int ObExprNot::eval_not_vector(const ObExpr &expr,
                               ObEvalCtx &ctx,
                               const ObBitVector &skip,
                               const EvalBound &bound)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(expr.args_[0]->eval_vector(ctx, skip, bound))) {
    LOG_WARN("failed to eval vector", K(ret));
  } else {
    VectorFormat arg_format = expr.args_[0]->get_format(ctx);
    VectorFormat res_format = expr.get_format(ctx);
    if (VEC_FIXED == arg_format && VEC_FIXED == res_format) {
      ret = inner_eval_not_vector<IntegerFixedVec, IntegerFixedVec>(expr, ctx, skip, bound);
    } else if (VEC_UNIFORM == arg_format && VEC_FIXED == res_format) {
      ret = inner_eval_not_vector<IntegerUniVec, ObVectorBase>(expr, ctx, skip, bound);
    } else {
      ret = inner_eval_not_vector<ObVectorBase, ObVectorBase>(expr, ctx, skip, bound);
    }
  }
  return ret;
}