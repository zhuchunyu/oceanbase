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

#define USING_LOG_PREFIX SHARE_SCHEMA
#include "ob_inner_table_schema.h"

#include "share/schema/ob_schema_macro_define.h"
#include "share/schema/ob_schema_service_sql_impl.h"
#include "share/schema/ob_table_schema.h"
#include "share/scn.h"

namespace oceanbase
{
using namespace share::schema;
using namespace common;
namespace share
{

int ObInnerTableSchema::all_virtual_pl_recompile_objinfo_real_agent_ora_schema(ObTableSchema &table_schema)
{
  int ret = OB_SUCCESS;
  uint64_t column_id = OB_APP_MIN_COLUMN_ID - 1;

  //generated fields:
  table_schema.set_tenant_id(OB_SYS_TENANT_ID);
  table_schema.set_tablegroup_id(OB_INVALID_ID);
  table_schema.set_database_id(OB_ORA_SYS_DATABASE_ID);
  table_schema.set_table_id(OB_ALL_VIRTUAL_PL_RECOMPILE_OBJINFO_REAL_AGENT_ORA_TID);
  table_schema.set_rowkey_split_pos(0);
  table_schema.set_is_use_bloomfilter(false);
  table_schema.set_progressive_merge_num(0);
  table_schema.set_rowkey_column_num(1);
  table_schema.set_load_type(TABLE_LOAD_TYPE_IN_DISK);
  table_schema.set_table_type(VIRTUAL_TABLE);
  table_schema.set_index_type(INDEX_TYPE_IS_NOT);
  table_schema.set_def_type(TABLE_DEF_TYPE_INTERNAL);

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_table_name(OB_ALL_VIRTUAL_PL_RECOMPILE_OBJINFO_REAL_AGENT_ORA_TNAME))) {
      LOG_ERROR("fail to set table_name", K(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_compress_func_name(OB_DEFAULT_COMPRESS_FUNC_NAME))) {
      LOG_ERROR("fail to set compress_func_name", K(ret));
    }
  }
  table_schema.set_part_level(PARTITION_LEVEL_ZERO);
  table_schema.set_charset_type(ObCharset::get_default_charset());
  table_schema.set_collation_type(ObCollationType::CS_TYPE_UTF8MB4_BIN);

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("RECOMPILE_OBJ_ID", //column_name
      ++column_id, //column_id
      1, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("REF_OBJ_NAME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      OB_MAX_CORE_TALBE_NAME_LENGTH, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("SCHEMA_VERSION", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("FAIL_COUNT", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("GMT_CREATE", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObTimestampLTZType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      0, //column_length
      -1, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("GMT_MODIFIED", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObTimestampLTZType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      0, //column_length
      -1, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }
  table_schema.set_index_using_type(USING_BTREE);
  table_schema.set_row_store_type(ENCODING_ROW_STORE);
  table_schema.set_store_format(OB_STORE_FORMAT_DYNAMIC_MYSQL);
  table_schema.set_progressive_merge_round(1);
  table_schema.set_storage_format_version(3);
  table_schema.set_tablet_id(0);
  table_schema.set_micro_index_clustered(false);

  table_schema.set_max_used_column_id(column_id);
  return ret;
}

int ObInnerTableSchema::tenant_virtual_show_create_catalog_ora_schema(ObTableSchema &table_schema)
{
  int ret = OB_SUCCESS;
  uint64_t column_id = OB_APP_MIN_COLUMN_ID - 1;

  //generated fields:
  table_schema.set_tenant_id(OB_SYS_TENANT_ID);
  table_schema.set_tablegroup_id(OB_INVALID_ID);
  table_schema.set_database_id(OB_ORA_SYS_DATABASE_ID);
  table_schema.set_table_id(OB_TENANT_VIRTUAL_SHOW_CREATE_CATALOG_ORA_TID);
  table_schema.set_rowkey_split_pos(0);
  table_schema.set_is_use_bloomfilter(false);
  table_schema.set_progressive_merge_num(0);
  table_schema.set_rowkey_column_num(1);
  table_schema.set_load_type(TABLE_LOAD_TYPE_IN_DISK);
  table_schema.set_table_type(VIRTUAL_TABLE);
  table_schema.set_index_type(INDEX_TYPE_IS_NOT);
  table_schema.set_def_type(TABLE_DEF_TYPE_INTERNAL);

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_table_name(OB_TENANT_VIRTUAL_SHOW_CREATE_CATALOG_ORA_TNAME))) {
      LOG_ERROR("fail to set table_name", K(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_compress_func_name(OB_DEFAULT_COMPRESS_FUNC_NAME))) {
      LOG_ERROR("fail to set compress_func_name", K(ret));
    }
  }
  table_schema.set_part_level(PARTITION_LEVEL_ZERO);
  table_schema.set_charset_type(ObCharset::get_default_charset());
  table_schema.set_collation_type(ObCollationType::CS_TYPE_UTF8MB4_BIN);

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("CATALOG_ID", //column_name
      ++column_id, //column_id
      1, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("CATALOG_NAME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      OB_MAX_CATALOG_NAME_LENGTH, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("CREATE_CATALOG", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObLongTextType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      0, //column_length
      -1, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }
  table_schema.set_index_using_type(USING_HASH);
  table_schema.set_row_store_type(ENCODING_ROW_STORE);
  table_schema.set_store_format(OB_STORE_FORMAT_DYNAMIC_MYSQL);
  table_schema.set_progressive_merge_round(1);
  table_schema.set_storage_format_version(3);
  table_schema.set_tablet_id(0);
  table_schema.set_micro_index_clustered(false);

  table_schema.set_max_used_column_id(column_id);
  return ret;
}

int ObInnerTableSchema::all_virtual_dynamic_partition_table_ora_schema(ObTableSchema &table_schema)
{
  int ret = OB_SUCCESS;
  uint64_t column_id = OB_APP_MIN_COLUMN_ID - 1;

  //generated fields:
  table_schema.set_tenant_id(OB_SYS_TENANT_ID);
  table_schema.set_tablegroup_id(OB_INVALID_ID);
  table_schema.set_database_id(OB_ORA_SYS_DATABASE_ID);
  table_schema.set_table_id(OB_ALL_VIRTUAL_DYNAMIC_PARTITION_TABLE_ORA_TID);
  table_schema.set_rowkey_split_pos(0);
  table_schema.set_is_use_bloomfilter(false);
  table_schema.set_progressive_merge_num(0);
  table_schema.set_rowkey_column_num(0);
  table_schema.set_load_type(TABLE_LOAD_TYPE_IN_DISK);
  table_schema.set_table_type(VIRTUAL_TABLE);
  table_schema.set_index_type(INDEX_TYPE_IS_NOT);
  table_schema.set_def_type(TABLE_DEF_TYPE_INTERNAL);

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_table_name(OB_ALL_VIRTUAL_DYNAMIC_PARTITION_TABLE_ORA_TNAME))) {
      LOG_ERROR("fail to set table_name", K(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(table_schema.set_compress_func_name(OB_DEFAULT_COMPRESS_FUNC_NAME))) {
      LOG_ERROR("fail to set compress_func_name", K(ret));
    }
  }
  table_schema.set_part_level(PARTITION_LEVEL_ZERO);
  table_schema.set_charset_type(ObCharset::get_default_charset());
  table_schema.set_collation_type(ObCollationType::CS_TYPE_UTF8MB4_BIN);

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TENANT_ID", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TENANT_SCHEMA_VERSION", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("DATABASE_NAME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      OB_MAX_DATABASE_NAME_LENGTH, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TABLE_NAME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      OB_MAX_TABLE_NAME_LENGTH, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TABLE_ID", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObNumberType, //column_type
      CS_TYPE_INVALID, //column_collation_type
      38, //column_length
      38, //column_precision
      0, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("MAX_HIGH_BOUND_VAL", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      OB_MAX_PARTITION_EXPR_LENGTH, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("ENABLE", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TIME_UNIT", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("PRECREATE_TIME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("EXPIRE_TIME", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("TIME_ZONE", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }

  if (OB_SUCC(ret)) {
    ADD_COLUMN_SCHEMA("BIGINT_PRECISION", //column_name
      ++column_id, //column_id
      0, //rowkey_id
      0, //index_id
      0, //part_key_pos
      ObVarcharType, //column_type
      CS_TYPE_UTF8MB4_BIN, //column_collation_type
      1024, //column_length
      2, //column_precision
      -1, //column_scale
      false, //is_nullable
      false); //is_autoincrement
  }
  table_schema.set_index_using_type(USING_HASH);
  table_schema.set_row_store_type(ENCODING_ROW_STORE);
  table_schema.set_store_format(OB_STORE_FORMAT_DYNAMIC_MYSQL);
  table_schema.set_progressive_merge_round(1);
  table_schema.set_storage_format_version(3);
  table_schema.set_tablet_id(0);
  table_schema.set_micro_index_clustered(false);

  table_schema.set_max_used_column_id(column_id);
  return ret;
}


} // end namespace share
} // end namespace oceanbase
