#ifndef BUFFER_H
#define BUFFER_H

#include "Config.h"
#include "Record.h"
#include "Index.h"

#define BLOCK_LEN			4096	// the size of one block
#define MAX_FILE_ACTIVE 	5		// limit the active files in the buffer
#define MAX_BLOCK			40		// the max number of the blocks

struct BUFFER_BLOCK_HEADER{
    int blockID;                // the block ID of the block, which indicate it when it be newed
    bool dirtyBit;              // 0 -> flase， 1 -> indicate dirty, write back
    FILE_HEADER *file;          // the pointer point to the file, which the block belongs to
    int charNum;                // the number of chars in the block
    char *cBlock;            	// the array space for storing the records in the block in buffer
    int iTime;                  // it indicate the age of the block in use
    int lock;                   // prevent the block from replacing
    //lock属性是用来做什么的orz
};

struct FILE_HEADER{
    int type;                   	// 0-> data file， 1 -> index file
    QString fileName;               // the name of the file
    int recordAmount;               // the number of record in the file
    int freeNum;                    // the free block number which could be used for the file
    int recordLength;               // the length of the record in the file
    FILE_HEADER *next;              // the pointer points to the next file
    BUFFER_BLOCK_HEADER *firstBlock;// point to the first block within the file
};

namespace BUFFER{
    enum BUFFER_REPLACE_STRATEGY{LRU, MRU};
}

class BUFFER
{
private:
    //QString DB_Name;
    BUFFER_BLOCK_HEADER *BlockHead;
    void initializeBlock(BUFFER_BLOCK_HEADER *Block){
        Block->blockID = -1;
        Block->dirtyBit = false;
        Block->next = NULL;
        Block->file = NULL;
        Block->charNum = 0;
        Block->cBlock = NULL;
        Block->iTime = 0;
        Block->lock = 0;
    }
    void flashBack(BUFFER_BLOCK_HEADER *Block);


public:
    BUFFER();
    ~BUFFER(){}

    BUFFER_BLOCK_HEADER& OfferFreeBlock();//如果找不到
    //BUFFER_BLOCK_HEADER& OfferReplacedBlock(BUFFER_REPLACE_STRATEGY BRS);

    // Check if the file is in the block, ruturn the existed block or allocate one
    BUFFER_BLOCK_HEADER& FileIntoFreeBlock(const FILE_HEADER &file_info);
    BUFFER_BLOCK_HEADER& FileIntoReplacedBlock(const FILE_HEADER &file_info, BUFFER_REPLACE_STRATEGY BRS);

    FILE_HEADER& GetFileInfo(const QString &file_name); // create one when not existing
    TABLE& ReadTable(const QString &table_name, const TABLE_HEADER &table_info);
    INDEX_LIST& ReadIndex(const QString &index_name, const INDEX_HEADER &index_info);

    bool SaveBlockToFile(BUFFER_BLOCK_HEADER& Block);

    // all above need to return file names for sake of CATALOG
    const QString& SaveTableToFile(const QString &table_name, const TABLE_HEADER &table_info);
    const QString& SaveIndexToFile(const QString &index_name, const INDEX_HEADER &index_info);

    // release memory
    bool CloseTable(TABLE_HEADER &table_info);
    bool CloseIndex(INDEX_HEADER &index_info);
    bool CloseFile(FILE_HEADER &file_info);
    bool CloseDB();
};

#endif // BUFFER_H
