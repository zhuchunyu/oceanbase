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

#pragma once

#include "common/object/ob_obj_type.h"
#include "lib/string/ob_string.h"
#include "share/schema/ob_schema_getter_guard.h"
#include "share/schema/ob_table_param.h"
#include "share/schema/ob_table_schema.h"
#include "share/table/ob_table_load_array.h"
#include "share/table/ob_table_load_define.h"

namespace oceanbase
{
namespace observer
{

class ObTableLoadSchema
{
public:
  static int get_schema_guard(uint64_t tenant_id,
                              share::schema::ObSchemaGetterGuard &schema_guard,
                              const int64_t schema_version = common::OB_INVALID_VERSION);
  static int get_table_schema(share::schema::ObSchemaGetterGuard &schema_guard,
                              uint64_t tenant_id,
                              uint64_t database_id,
                              const common::ObString &table_name,
                              const share::schema::ObTableSchema *&table_schema);
  // 获取最新schema_guard和table_schema
  static int get_table_schema(uint64_t tenant_id, uint64_t table_id,
                              share::schema::ObSchemaGetterGuard &schema_guard,
                              const share::schema::ObTableSchema *&table_schema);
  // 指定schema_guard获取table_schema
  static int get_table_schema(share::schema::ObSchemaGetterGuard &schema_guard,
                              uint64_t tenant_id, uint64_t table_id,
                              const share::schema::ObTableSchema *&table_schema);
  // 指定tenant schema version 和 table id 获取schema version
  static int get_table_schema_version(const uint64_t tenant_id,
                                      const int64_t tenant_schema_version,
                                      const uint64_t table_id,
                                      int64_t &schema_version);

  static int get_user_column_schemas(const share::schema::ObTableSchema *table_schema,
                                     ObIArray<const share::schema::ObColumnSchemaV2 *> &column_schemas,
                                     bool contain_invisible_column = false);
  static int get_user_column_ids(const share::schema::ObTableSchema *table_schema,
                                 common::ObIArray<uint64_t> &column_ids);
  static int get_user_column_id_and_names(const share::schema::ObTableSchema *table_schema,
                                          common::ObIArray<uint64_t> &column_ids,
                                          common::ObIArray<common::ObString> &column_names);

  static int get_column_ids(const share::schema::ObTableSchema *table_schema,
                            common::ObIArray<uint64_t> &column_ids,
                            bool contain_hidden_pk_column = false);
  static int check_has_non_local_index(share::schema::ObSchemaGetterGuard &schema_guard,
                                       const share::schema::ObTableSchema *table_schema,
                                       bool &bret);
  static int check_is_heap_table_with_single_unique_index(share::schema::ObSchemaGetterGuard &schema_guard,
                                       const share::schema::ObTableSchema *table_schema,
                                       bool &bret);
  static int get_tenant_optimizer_gather_stats_on_load(const uint64_t tenant_id, bool &value);
  static int get_tablet_ids_by_part_ids(const ObTableSchema *table_schema,
                                        const ObIArray<ObObjectID> &part_ids,
                                        ObIArray<ObTabletID> &tablet_ids);
  static int prepare_col_descs(const ObTableSchema *table_schema,
                               common::ObIArray<share::schema::ObColDesc> &col_descs);
public:
  ObTableLoadSchema();
  ~ObTableLoadSchema();
  void reset();
  int init(uint64_t tenant_id, uint64_t table_id, const int64_t schema_version);
  bool is_valid() const { return is_inited_; }
  bool is_column_store() const { return cg_cnt_ > 1; }
  TO_STRING_KV(K_(table_name), K_(is_partitioned_table), K_(is_table_without_pk), K_(is_table_with_hidden_pk_column),
               K_(has_autoinc_column), K_(has_identity_column), K_(has_lob_rowkey), K_(rowkey_column_count), K_(store_column_count),
               K_(cg_cnt), K_(collation_type), K_(column_descs), K_(is_inited));
private:
  int init_table_schema(const share::schema::ObTableSchema *table_schema);
  int init_cmp_funcs(const common::ObIArray<share::schema::ObColDesc> &column_descs,
                     const bool is_oracle_mode);
  int init_lob_storage(const common::ObIArray<share::schema::ObColDesc> &column_descs);
  int gen_lob_meta_datum_utils();
public:
  common::ObArenaAllocator allocator_;
  uint64_t table_id_;
  common::ObString table_name_;
  bool is_index_table_;
  bool is_lob_table_;
  bool is_partitioned_table_;
  bool is_table_without_pk_;
  bool is_table_with_hidden_pk_column_;
  share::schema::ObIndexType index_type_;
  bool has_autoinc_column_;
  bool has_identity_column_;
  bool has_lob_rowkey_;
  int64_t rowkey_column_count_;
  // column count in store, does not contain virtual generated columns
  int64_t store_column_count_;
  common::ObCollationType collation_type_;
  share::schema::ObPartitionLevel part_level_;
  int64_t schema_version_;
  uint64_t lob_meta_table_id_;
  int64_t lob_inrow_threshold_;
  int64_t cg_cnt_;
  common::ObArray<uint64_t> index_table_ids_;
  common::ObArray<int64_t> lob_column_idxs_;
  // if it is a heap table, it contains hidden primary key column
  // does not contain virtual generated columns
  common::ObArray<share::schema::ObColDesc> column_descs_;
  blocksstable::ObStorageDatumUtils datum_utils_;
  common::ObArray<share::schema::ObColDesc> lob_meta_column_descs_;
  blocksstable::ObStorageDatumUtils lob_meta_datum_utils_;
  blocksstable::ObStoreCmpFuncs cmp_funcs_; // for sql statistics
  common::ObIVector *non_partitioned_tablet_id_vector_;
  bool is_inited_;
};

}  // namespace observer
}  // namespace oceanbase
