#ifndef RECORD_H
#define RECORD_H

#include "Config.h"
#include "Buffer.h"
#include "API.h"
#include <QFile>

struct Attribute{
    short flag[32];//data type
    QString name[32];//attribute name
    bool unique[32];//unique
    int num;
};

struct Index{
    int num;
    short location[10];
    std::string indexname[10];
};

// implement the table
/*class TABLE{
    friend class CataLog;
    public:
        int blockNum;//total number of blocks occupied in data file;

        int dataSize(){ //size of a single tuper;
        int res = 0;
        for (int i = 0; i < attr.num;i++){
            switch (attr.flag[i]){
                case -1:res += sizeof(int); break;
                case 0:res += sizeof(float); break;
                default:res += attr.flag[i]+1; break; //多一位储存'\0'
            }
        }
        return res;
        }

    public:
        QString Tname;
        Attribute attr;//number of attributes

    public:
        TABLE(QString s,Attribute aa, int bn):Tname(s),attr(aa),blockNum(bn){
            primary = -1;
            for(int i = 0;i<32;i++){ aa.unique[i] = false; }
            index.num=0;
        }
        //Construct with Tname and column.
        Table(const Table& t);
        ~Table();
        std::vector<tuper*> T;//pointers to each tuper
        short primary;//the location of primary key. -1 means no primary key.
        Index index;

        Attribute getattribute(){
            return attr;
        }

        void setindex(short i, std::string iname);

        void dropindex(std::string iname);

        void Copyindex(Index ind){
            index = ind;
        }

        Index Getindex(){
            return index;
        }

        void setprimary(int p){
            primary = p;
        }//set the primary key

        void disp();

        std::string getname(){
            return Tname;
        }

        int getCsize() const{
            return attr.num;
        }

        int getRsize() const{
            return (int)T.size();
        }

        void addData(tuper* t);
    }
}*/

// record the basic table info including length and block usage
struct TABLE_HEADER{
   int blockNum;//total number of blocks occupied in data file;
   int dataSize(){ //size of a single tuper;
       int res = 0;
       for (int i = 0; i < attr.num;i++){
           switch (attr.flag[i]){
                case -1:res += sizeof(int); break;
                case 0:res += sizeof(float); break;
                default:res += attr.flag[i]+1; break; //多一位储存'\0'
            }
        }
        return res;
        }
    QString Tname;
    Attribute attr;//number of attributes

    public:
        TABLE(QString s,Attribute aa, int bn):Tname(s),attr(aa),blockNum(bn){
            primary = -1;
            for(int i = 0;i<32;i++){ aa.unique[i] = false; }
            index.num=0;
        }
        //Construct with Tname and column.
        Table(const Table& t);
        ~Table();
        std::vector<tuper*> T;//pointers to each tuper
        short primary;//the location of primary key. -1 means no primary key.
        Index index;

        void setindex(short i, std::string iname);

        void dropindex(std::string iname);

        void disp();

        void addData(tuper* t);
}

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
    //~RECORD();

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
