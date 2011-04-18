#ifndef HACC_DB_DEFINES_H
#define HACC_DB_DEFINES_H


#define HACC_DB_CREATE_TABLE_BEGIN(_table) exec("create table " #_table "("

#define HACC_DB_FIELD_DELIMITER         ","
#define HACC_DB_FIELD_NOT_NULL          " not null"
#define HACC_DB_FIELD_UNIQUE            " unique"
#define HACC_DB_FIELD_DEFAULT(_default) " default(" #_default ")"

#define HACC_DB_INTEGER(_name)  #_name " integer"
#define HACC_DB_TEXT(_name)     #_name " text"
#define HACC_DB_BOOL(_name)     #_name " integer" HACC_DB_FIELD_NOT_NULL HACC_DB_FIELD_DEFAULT(0)
#define HACC_DB_ID(_name)       #_name " integer" HACC_DB_FIELD_NOT_NULL
#define HACC_DB_BLOB(_name)     #_name " blob"
#define HACC_DB_REAL(_name)     #_name " real"
#define HACC_DB_MONEY(_name)    #_name " real"    HACC_DB_FIELD_DEFAULT(0)
#define HACC_DB_DATETIME(_name) #_name " timestamp"

#define HACC_DB_CREATE_TABLE_END ");");

#define HACC_DB_ID_FIELD          HACC_DB_ID(id)            " primary key"
#define HACC_DB_ICON_FIELD        HACC_DB_ID(icon_id)       HACC_DB_FIELD_DEFAULT(1)
#define HACC_DB_CURRENCY_FIELD    HACC_DB_ID(currency_id)   HACC_DB_FIELD_DEFAULT(1)
#define HACC_DB_NAME_FIELD        HACC_DB_TEXT(name)        HACC_DB_FIELD_NOT_NULL
#define HACC_DB_UNIQUE_NAME_FIELD HACC_DB_NAME_FIELD        HACC_DB_FIELD_UNIQUE
#define HACC_DB_FULL_DESCRIPTION  HACC_DB_TEXT(description) HACC_DB_FIELD_DELIMITER HACC_DB_BLOB(image)

#define HACC_DB_CREATE_INDEX(_table,_field) \
    exec("create index i_" #_table "_" #_field " on " #_table " (" #_field " ASC);");

#define HACC_DB_CREATE_INDEX_2(_table,_field_one,_field_two) \
    exec("create index i_" #_table "_" #_field_one "_" #_field_two " on " #_table " (" #_field_one " ASC, " #_field_two " ASC);");

#define HACC_DB_CREATE_UNIQNAME_ID_INDEX(_table) HACC_DB_CREATE_INDEX_2(_table, id, name)

#define HACC_DB_CREATE_TAGS_TABLE(_table) \
    exec("create table " HACC_TAG_TABLE_NAME(_table) "(" HACC_DB_ID(tag_id) "," HACC_TAG_TABLE_ID_NAME(_table) "integer not null"                     ");"); \
    exec("create "     "index i_" #_table "s_tags_tag"          " on " HACC_TAG_TABLE_NAME(_table) "(tag_id "                                     " asc);"); \
    exec("create "     "index i_" #_table "s_tags_"     #_table " on " HACC_TAG_TABLE_NAME(_table) "( "            HACC_TAG_TABLE_ID_NAME(_table) " asc);"); \
    exec("create unique index i_" #_table "s_tags_tag_" #_table " on " HACC_TAG_TABLE_NAME(_table) "(tag_id asc, " HACC_TAG_TABLE_ID_NAME(_table) " asc);");

#define HDB_APPEND_CONTRACTOR(_name, _icon, _own) \
        exec("insert into contractors (id, name, icon_id, own_account) values (?,?,?,?)", \
        QVariantList() << ++contractorID << _name << _icon << _own);

#define HDB_APPEND_ACCOUNT(_name, _icon, _currency) \
        exec("insert into accounts (id, name, icon_id, contractor_id, currency_id) values (?,?,?,?,?)" , \
        QVariantList() << ++accountID << _name << _icon << contractorID << _currency);

#define HDB_APPEND_MANUFACTURER_FULL(_name, _description, _icon) \
        exec("insert into manufacturers (id, name, icon_id) values (?,?,?)", \
        QVariantList() << ++manufacturerID << _name << _icon);

#define HDB_APPEND_MANUFACTURER(_name, _icon) HDB_APPEND_MANUFACTURER_FULL(_name, _name, _icon);

#define HDB_APPEND_THING(_name, _icon, _enumerated, _thing_type) \
        exec("insert into things (id, name, icon_id, manufacturer_id, enumerated_type_id) values (?,?,?,?,?)", \
        QVariantList() << ++thingID << _name << _icon << manufacturerID << _enumerated); \
        HACC_THINGS->attachTag(_thing_type, thingID);

#define HDB_APPEND_CURRENCY(_name, _reduction, _before_value, _icon) \
    exec("insert into currencyes (id,name,reduction,show_reduction_before_value,icon_id) values (?,?,?,?,?)", \
              QVariantList() << ++currencyID << _name << _reduction  << _before_value << HACC_DB_ICONS->add(":/flags/" _icon ".png"  ));


#endif // HACC_DB_DEFINES_H
