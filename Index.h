#ifndef INDEX_H
#define INDEX_H

#include "Config.h"
#include "Buffer.h"
#include "API.h"

// implement the index structure (node only) and BP-Tree operation
class INDEX_TREE{};

// record the basic index info including type, length and block usage
class INDEX_HEADER{};
class MULTI_LEVEL_INDEX_HEADER : public INDEX_HEADER{};

// link all the index files
struct INDEX_LIST
{
    QString IndexName;
    INDEX_TREE *IndexRoot;
    INDEX_HEADER *IndexInfo;
    INDEX_LIST *Next;
};

class INDEX : private INDEX_TREE
{
private:
    QString DB_Name;
    INDEX_LIST *ListHead;
public:
    INDEX();

    bool IfIndexNameExist(const QString &index_name) const;
    const QString& IfIndexKeyExist(const QString &table_name, const QString &key) const; // return index name

    // all above need to return file names for sake of CATALOG
    virtual const QString& CreateIndex(const QString &table_name, const QString &key, const QString &index_name, const TABLE &table);
    virtual const QString& DropIndex(const QString &index_name);

    virtual bool ReIndex(const QString &index_name, const TABLE &table);

    virtual bool InsertIndexRec(const QString &index_name, const QString &key_value, RECORD_TRACE &pRecAddr);
    virtual bool DeleteIndexRec(const QString &index_name, const QString &key_value);
    virtual bool UpdateIndexRecName(const QString &index_name, const QString &key_value, const QString &key_new);
    virtual bool UpdateIndexRecAddr(const QString &index_name, const QString &key_value, RECORD_TRACE &pRecAddr);

    // accelerate select operation using index
    virtual RECORD_TRACE& FindSingleIndex(const QString &index_name, const QString &key) const;
    virtual RECORD_TRACE_LIST& FindMultiIndexList(const QString &index_name, const CONDITION_TREE &cond) const;

    // list all indices
    virtual INDEX_LIST& GetIndexList(const QString &index_name) const;
    // return record order in table sorted by index (used for table sorting)
    virtual RECORD_TRACE_LIST& GetIndexOrderPtr(const QString &index_name) const;

    virtual bool IndexLevelUp(const QString &index_name);
};

class MULTI_LEVEL_INDEX : public INDEX
{
public:
    virtual const QString& CreateIndex(const QString &table_name, const QString &key, const QString &index_name, const TABLE &table);
    virtual const QString& DropIndex(const QString &index_name);

    virtual bool ReIndex(const QString &index_name, const TABLE &table);

    virtual bool InsertIndexRec(const QString &index_name, const QString &key_value, RECORD_TRACE &pRecAddr);
    virtual bool DeleteIndexRec(const QString &index_name, const QString &key_value);
    virtual bool UpdateIndexRecName(const QString &index_name, const QString &key_value, const QString &key_new);
    virtual bool UpdateIndexRecAddr(const QString &index_name, const QString &key_value, RECORD_TRACE &pRecAddr);

    // accelerate select operation using index
    virtual RECORD_TRACE& FindSingleIndex(const QString &index_name, const QString &key) const;
    virtual RECORD_TRACE_LIST& FindMultiIndexList(const QString &index_name, const CONDITION_TREE &cond) const;

    // list all indices
    virtual INDEX_LIST& GetIndexList(const QString &index_name) const;
    // return record order in table sorted by index (used for table sorting)
    virtual RECORD_TRACE_LIST& GetIndexOrderPtr(const QString &index_name) const;

    virtual bool IndexLevelUp(const QString &index_name);
};

#endif // INDEX_H
