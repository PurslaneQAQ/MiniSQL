#ifndef RECORD_CPP
#define RECORD_CPP

#include "Record.h"

using namespace RECORD;

RECORD::RECORD(){}

// all above need to return file names for sake of CATALOG
const QString& RECORD::CreateTable(const QString &table_name, int offset, const ATTR_CATA_LIST &attr_list)
{
    QString filename = table_name + ".table";
    QFile fout(filename.c_str(), ios::out);
    fout.close();
    tableIn.blockNum = 1;
    CataManager Ca;
    Ca.changeblock(tableIn.getname(), 1);
    return true;
}

const QString& RECORD::DropTable(QString &table_name);

bool Insert(const QString &table_name, const RECORD_FLOW &value);

// Attention : pAttr and pValue should correspond with each other accordingly
bool RECORD::DirectUpdate(const QString &table_name, const CONDITION_TREE &cond, const ATTR_LIST &pAttr, const ATTR_LIST &pValue);
bool RECORD::UpdateWithIndex(const QString &table_name, RECORD_TRACE_LIST &record_list, const ATTR_LIST &pAttr, const ATTR_LIST &pValue);
bool RECORD::UpdateFromIndex(const QString &table_name, RECORD_TRACE &index_record, const ATTR_LIST &pAttr, const ATTR_LIST &pValue, DIRECTION dir);

// Attention : when 'pAttr == NULL', it means 'select *'
const RECORD_FLOW& RECORD::DirectSelectFrom(const QString &table_name, const QString &pAttr) const;
const RECORD_FLOW& RECORD::DirectSelectFromWhere(const QString &table_name, const QString &pAttr, const CONDITION_TREE &cond) const;
const RECORD_FLOW& RECORD::SelectWithIndex(const QString &table_name, const QString &pAttr, const RECORD_TRACE_LIST &record_list) const;
const RECORD_FLOW& RECORD::SelectFromIndex(const QString &table_name, const QString &pAttr, const RECORD_TRACE &index_record, DIRECTION dir) const;

// Attention : when 'cond == NULL', it means 'delete *'
bool RECORD::DirectDelete(const QString &table_name, const CONDITION_TREE &cond);
bool RECORD::DeleteWithIndex(const QString &table_name, RECORD_TRACE_LIST &record_list);
bool RECORD::DeleteFromIndex(const QString &table_name, RECORD_TRACE &index_record, DIRECTION dir);

bool RECORD::SortByPrimaryKey(const QString &table_name);
bool RECORD::SortByIndex(const QString &table_name, RECORD_TRACE_LIST &key_order);

bool RECORD::CloseDB();

#endif // RECORD_CPP
