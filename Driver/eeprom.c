#include "eeprom.h"
#include "../Setting/configuration.h"
#include <libpic30.h>
#include <string.h>
#include <stddef.h>


#define WORD_SIZE   (2)                     //WORD長　[Byte]
#define PAGE_WORD   (32)                    //PAGEサイズ [Word]
#define PAGE_SIZE   (WORD_SIZE*PAGE_WORD)   //PAGEサイズ[Byte]
//#define FILE_PAGE   (2)                     //FILEのページ数
//#define FILE_SIZE   (FILE_PAGE*PAGE_SIZE)   //FILEの大きさ 128byteのはず
//#define FILE_MAX   (7)                     //FILEの最大個数

struct FileBuffer {
    //Buffer 関連
    char buf[PAGE_SIZE];
    int pos;
    //Target 関連
    _prog_addressT target;
    
};
#define new(x) malloc(sizeof(x)) 

int __attribute__((space(eedata), aligned(_EE_ROW))) system_file[64];
struct FileBuffer fb;

void eeprom_setup() {
    File fp;
    fp = eeprom_open(FileSystem);
    
    eeprom_puts(fp,"hello world in eeprom.\n");
    eeprom_flush(fp);
    eeprom_close(fp);
    
}

File eeprom_open(FileNames_t name) {
    File fp = NULL;
    _prog_addressT ta;
    switch (name) {
        case FileSystem:
            _init_prog_address(ta,system_file);
        default:
            return NULL; //エラー
    }
    //構造体を初期化
    fp=&fb;
    fp->pos = 0;
    fp->target=ta;
#if defined(IS_SLIM)
    memset(fp->buf,0,sizeof (fp->buf));
#endif
}

int eeprom_close(File fp){
    //free(fp);
    return 0;
}

int eeprom_putc(File fp,char c){
    const int mask =PAGE_SIZE -1;
    
    fp->buf[fp->pos++]=c;
    if ((fp->pos&mask)==mask){
        eeprom_flush(fp);
        return 1;
    }else{
        return 0;
    }    
}

int eeprom_puts(File fp,const char* str){
    while (*str!='\0'){
        eeprom_putc(fp,*(str++));
        
    }
    return 0;
}

int eeprom_flush(File fp){
    _erase_eedata(fp->target,_EE_ROW);
    _wait_eedata();
//    _write_eedata_row(fp->target,fp->buf);
    _wait_eedata();
    return 0;
}