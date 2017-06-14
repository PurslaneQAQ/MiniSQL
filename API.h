#ifndef API_H
#define API_H

#include "Config.h"
#include "Interpreter.h"
#include "Record.h"
#include "Index.h"
#include "Catalog.h"

class API
{
private:
    QString DB_Name;
    INDEX *Index;
    RECORD Record;

public:
    API();

    // transfer operation to the lower modules
    // Attention : remember to deliver file names to CATALOG after creation
    bool CreateDatabase(const QString &DB_name);
    bool CreateTable(const QString &table_name, int offset, const ATTR_CATA_LIST &attr_list);
    bool CreateIndex(const QString &table_name, const QString &attr, const QString &index_name);
    bool ReIndex(const QString &index_name) const;

    // Note : remember to call CATALOG to delete mode info
    bool DropDatabase();
    bool DropTable(const QString &table_name);
    bool DropIndex(const QString &index_name);

    // Attention : when 'pAttr == NULL', it means 'select *'
    const RECORD_FLOW& SelectFrom(const QString &table_name, ATTR_LIST &pAttr) const;
    const RECORD_FLOW& SelectFromWhere(const QString &table_name, ATTR_LIST &pAttr, CONDITION_TREE &cond) const;

    // Note : remember to call INDEX to check and update index
    bool Insert(const QString &table_name, const RECORD_FLOW &value) const;
    // Attention : pAttr and pValue should correspond with each other accordingly
    bool Update(const QString &table_name, CONDITION_TREE &cond, ATTR_LIST &pAttr, ATTR_LIST &pValue) const;
    // Attention : when 'cond == NULL', it means 'delete *'
    bool Delete(const QString &table_name, CONDITION_TREE &cond) const;
    // Attention : remember to update index after sorting
    bool SortByIndex(const QString &table_name, const QString &key);
};

#endif // API_H
