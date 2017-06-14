#ifndef BUFFER_CPP
#define BUFFER_CPP

#include "Buffer.h"
#include <iostream>
/*Page::Page():
file_name(""),
block_id(-1),
pin_count(-1),
dirty(false),
ref(false),
avaliable(true)
{
    for (int i = 0;i < BLOCK_LEN;i++)
        buffer_[i] = '\0';
}
// 初始化*/

BUFFER::BUFFER()
{
    bufferBlock = new BUFFER_BLOCK_HEADER;
    initializeBlock(BlockHead);
}

BUFFER_BLOCK_HEADER& BUFFER::OfferFreeBlock()
{
    BUFFER_BLOCK_HEADER* least_recent_block = BlockHead;
    BUFFER_BLOCK_HEADER* last_block, recent_block = BlockHead;
    for (int count = 1; count < MAX_BLOCK, recent_block != NULL; count++){
        if (!recent_block->dirtyBit){
            initialize(recent_block);
            return recent_block;
        }
        else if (least_recent_block->iTime > recent_block->iTime){
            least_recent_block = recent_block;
        }
        last_block = recent_block;
        recent_block = recent_block->next;
    }
    //执行到这里，最不常访问的block下标为least_recent_block

    if(count < MAX_BLOCK){
        recent_block = new BUFFER_BLOCK_HEADER;
        initialize(recent_block);
        last_block->next = recent_block;
        return recent_block;
    }
    /************待补全，真的用链表吗***********/
    SaveBlockToFile(least_recent_block);
    //bufferBlock[least_recent_block].isValid = 1;
    return &(*least_recent_block);//这句完全是乱写的，忘了地址和&的关系
}

//BUFFER::BUFFER_BLOCK_HEADER& OfferReplacedBlock(BUFFER_REPLACE_STRATEGY BRS){} //并不是很清楚在干嘛

// Check if the file is in the block, ruturn the existed block or allocate one
BUFFER_BLOCK_HEADER& FileIntoFreeBlock(const FILE_HEADER &file_info){
    BUFFER_BLOCK_HEADER Block = file_info.firstBlock;
    if (Block == NULL) {
       Block = OfferFreeBlock();
       GetFileInfo(file_info.fileName);
       //这个函数和getfileinfo函数的关系是什么样子的？分别要完成哪一部分操作？
    }
    return Block;
}

//BUFFER_BLOCK_HEADER& FileIntoReplacedBlock(const FILE_HEADER &file_info, BUFFER_REPLACE_STRATEGY BRS);

FILE_HEADER& GetFileInfo(const QString &file_name)// create one when not existing
{
    FILE_HEADER* file;
    FILE *f = fopen(file_name.data() , "a+");//以附加方式打开可读写的文件。若文件不存在，则会建立该文件，
    //如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
    //参考 http://blog.sina.com.cn/s/blog_6e7fed390100z0j1.html
    // 打开失败返回-1
    file.type = 0;                	// 0-> data file， 1 -> index file
    /*非常疑惑存储规则了*/
    file->recordAmount;               // the number of record in the file
    file->freeNum;                    // the free block number which could be used for the file
    //此参数意义何在？
    int recordLength;               // the length of the record in the file
    file->fileName = file_name;     // the name of the file
    file->next = NULL;              // the pointer points to the next file
    BUFFER_BLOCK_HEADER *firstBlock;// point to the first block within the file
}

TABLE& ReadTable(const QString &table_name, const TABLE_HEADER &table_info)
{s
}

INDEX_LIST& ReadIndex(const QString &index_name, const INDEX_HEADER &index_info){
}

bool SaveBlockToFile(BUFFER_BLOCK_HEADER& Block){
    if(!Block->dirtyBit) return;//如果没有被改写
    //被改写
    QString filename = Block->file->fileName;
    //fstream fout;
    FILE *fp;
    if ((fp = fopen(filename.data() ,"r+b"))==NULL	){
        qDebug() << "Open file error!" << endl; // #Todo
        return;
    }
    //
    /*********************这里完全不理解******************/
    fseek(fp, Block->charNum * Block.blockOffset, SEEK_SET);
    fwrite(Block->cBlock, BLOCKSIZE, 1, fp);
    Block.initialize();
    fclose(fp);
    /*fout.open(filename.c_str(), ios::in | ios::out);
    fout.seekp(BLOCKSIZE*bufferBlock[bufferNum].blockOffset, fout.beg);
    fout.write(bufferBlock[bufferNum].values, BLOCKSIZE);
    bufferBlock[bufferNum].initialize();
    fout.close();*/
}

// all above need to return file names for sake of CATALOG
const QString& SaveTableToFile(const QString &table_name, const TABLE_HEADER &table_info){
    BUFFER_BLOCK_HEADER& Block = OfferFreeBlock();
    Block.file->fileName = table_info.Tname + ".table";
    Block.cBlock = clock();
    //CataManager ca;
    //ca.changeblock(tableinfor.getname(), tableinfor.blockNum);
    /************看起来在这个称程序里上述操作是在catalog模块完成的**************/
}

const QString& SaveIndexToFile(const QString &index_name, const INDEX_HEADER &index_info);

// release memory
bool CloseTable(TABLE_HEADER &table_info){
    if(delete table_info)return true;
    else return false;
}

bool CloseIndex(INDEX_HEADER &index_info){
    if(delete index_info)return true;
    else return false;
}

bool CloseFile(FILE_HEADER &file_info){
    if(delete file_info)return true;
    else return false;
}

bool CloseDB(){
    for (int i = 0;i < frame_size_;i++) {
        QString file_name;
        int block_id;
        file_name = Frames[i].getFileName();
        block_id = Frames[i].getBlockId();
        flushPage(i , file_name , block_id);
    }
}

#endif // BUFFER_CPP
