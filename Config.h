// This is a list for universal data structure

#ifndef COMMAND_H
#define COMMAND_H
#define DEBUG 1
#include <QString>
#include <vector>
#include <algorithm>

// parameter
const int MAX_ATTR_NUM = 32;
const int MAX_CHAR_LEN = 255;

// illustrate the structure of an index for table or for index
struct ATTR_CATA_LIST
{
    TYPE Type;
    QString AttrName;
    int OffSet; // memory taken
    int SetLen; // fixed char length, set 0 means no limit
    KEY Key;
    ATTR_CATA_LIST *Next;
};
namespace ATTR_CATA_LIST{
    enum TYPE{CHAR_N,VARCHAR,INT,DOUBLE};
    enum KEY{PRIMARY,CANDIDATE};
}

struct ATTR_LIST
{
    QString AttrName;
    ATTR_LIST *Next;
};

// inner transmission of record
struct RECORD_FLOW{
    ATTR_CATA_LIST::TYPE Type;
    void* Value;
    ATTR_CATA_LIST::KEY Key;
    RECORD_FLOW *Next;
};

// store the conditions for selection or deletion (built by Interpreter)
struct CONDITION_TREE
{
    CONDITION_TREE *Left;
    CONDITION_TREE *Right;
    CONDITION_TREE_NODE_TYPE NodeType;
    struct OP{              // meaningful only it is an "OPERATION Node"
        QString LeftOprand;
        QString RightOprand;
        OPRAND_TYPE Oprand;
    };
};
namespace CONDITION_TREE{
    enum CONDITION_TREE_NODE_TYPE{AND, OR, OPERATION};
    enum OPRAND_TYPE{EQUAL,SMALLER,BIGGER,NOT_EQUAL,NO_SMALLER,NO_BIGGER};
}

// transmit record address (relative) between index and record through API
struct RECORD_TRACE
{
    QString *table_name;
    int offset; // in order for decoupling with record node and length structure, this is record number in the table
};
struct RECORD_TRACE_LIST
{
    QString *table_name;
    vector<int> offset_list;
};

#endif // COMMAND_H
