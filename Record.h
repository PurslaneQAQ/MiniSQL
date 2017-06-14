#ifndef RECORD_H
#define RECORD_H

#include "Config.h"
#include "Buffer.h"
#include "API.h"


// implement the table
class TABLE{};

// record the basic table info including length and block usage
struct TABLE_HEADER{};

// link all the table files
struct TABLE_LIST
{
    QString TableName;
    TABLE *Table;
    TABLE_HEADER *TableInfo;
    TABLE_LIST *Next;
};

class RECORD : private TABLE
{
private:
    QString DB_Name;
    TABLE_LIST *ListHead;

public:
    RECORD();

    // all above need to return file names for sake of CATALOG
    const QString& CreateTable(const QString &table_name, int offset, const ATTR_CATA_LIST &attr_list);
    const QString& DropTable(QString &table_name);

    bool Insert(const QString &table_name, const RECORD_FLOW &value);

    // Attention : pAttr and pValue should correspond with each other accordingly
    bool DirectUpdate(const QString &table_name, const CONDITION_TREE &cond, const ATTR_LIST &pAttr, const ATTR_LIST &pValue);
    bool UpdateWithIndex(const QString &table_name, RECORD_TRACE_LIST &record_list, const ATTR_LIST &pAttr, const ATTR_LIST &pValue);
    bool UpdateFromIndex(const QString &table_name, RECORD_TRACE &index_record, const ATTR_LIST &pAttr, const ATTR_LIST &pValue, DIRECTION dir);

    // Attention : when 'pAttr == NULL', it means 'select *'
    const RECORD_FLOW& DirectSelectFrom(const QString &table_name, const QString &pAttr) const;
    const RECORD_FLOW& DirectSelectFromWhere(const QString &table_name, const QString &pAttr, const CONDITION_TREE &cond) const;
    const RECORD_FLOW& SelectWithIndex(const QString &table_name, const QString &pAttr, const RECORD_TRACE_LIST &record_list) const;
    const RECORD_FLOW& SelectFromIndex(const QString &table_name, const QString &pAttr, const RECORD_TRACE &index_record, DIRECTION dir) const;

    // Attention : when 'cond == NULL', it means 'delete *'
    bool DirectDelete(const QString &table_name, const CONDITION_TREE &cond);
    bool DeleteWithIndex(const QString &table_name, RECORD_TRACE_LIST &record_list);
    bool DeleteFromIndex(const QString &table_name, RECORD_TRACE &index_record, DIRECTION dir);

    bool SortByPrimaryKey(const QString &table_name);
    bool SortByIndex(const QString &table_name, RECORD_TRACE_LIST &key_order);

    bool CloseDB();
};
namespace RECORD{
    enum DIRECTION{UP_FROM_THIS,DOWN_FROM_THIS,UP_WITHOUT_THIS,DOWN_WITHOUT_THIS};
}


#endif // RECORD_H
