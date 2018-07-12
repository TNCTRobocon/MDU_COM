#ifndef GCMEM_H
#define	GCMEM_H
#include <stdint.h>

//Shell用内部GC

enum FileFags{
    AccessNone = 0x0000,
    AccessExcute = 0x0001,
    AccessWrite = 0x0002,
    AccessRead = 0x0004,
    AccessReadAndWrite = 0x0006,
    AccessLock = 0x0008, //システムファイルに利用する。
    AccessMask = 0x000F,
    FileTypeNone = 0x00, //エラー認識用
    FileTypeDirectory = 0x10,
    FileTypeExcute=0x20,
    FileTypeInteger = 0x30,
    FileTypeFloat = 0x40,
    FileTypeText = 0x40,
    FileTypeMask = 0xF0//これ以上の値を作ってはいけない。
};

typedef enum FileFags Access_t;
typedef enum FileFags FileType_t;

struct FileItem {
    const char *name;
    struct FileItem *parent, *next; //木構造を作成
    //PathType_t type;//unionの使い方を決定する。
    uint16_t fags;
    union {//
        int (*func)(int, char**);
        struct FileItem *child; //子ディレクトリ
        int* ptr_int;
        float* ptr_float;
    };
    
};

union FileUnit {
    struct FileItem item; //この要素は位置を変えてはいけない。
    union FileUnit *next; //単方向リストを構成する。
};
typedef union FileUnit GC_Body_t;

void file_init();
uint16_t file_free(); //O(n)
uint16_t file_used(); //O(n)
uint16_t file_memory();//[Byte]


typedef struct FileItem* file_t;
//これらは単純にメモリーを確保、開放しているだけである。よってこれらは通常呼び出さない。
file_t file_create(const char *name);
void file_delete(file_t);



#endif	/* GCMEM_H */

