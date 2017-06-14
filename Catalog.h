#ifndef CATALOG_H
#define CATALOG_H

#include "Config.h"
#include "Interpreter.h"
#include "API.h"

class INDEX_CATA_LIST{};

class TABLE_CATA_LIST{};

class CATALOG
{
private:
    QString DB_Name;
public:
    bool CreateDatabase(const QString &DB_name);
    bool CreateTable(const QString &table_name, const QString &file_name, const ATTR_CATA_LIST &attr_list);
    bool CreateIndex(const QString &index_name, const QString &file_name, const ATTR_CATA_LIST &attr_list);

    bool DropDatabase();
    bool DropTable(const QString &table_name);
    bool DropIndex(const QString &index_name);

    // called by INTERPRETER to do mode conflict check
    bool CheckInsert(const QString &table_name, const RECORD_FLOW &value) const;
    bool CheckAttr(const QString &table_name, const ATTR_LIST &pAttr) const;
    bool CheckCond(const QString &table_name, const CONDITION_TREE &cond) const;

    // primary / candidate key uniqueness check
    bool CheckKey(const QString &table_name, const QString &key) const;

};

#endif // CATALOG_H
