/* 
 * File:   eeprom.h
 * Author: TERU
 *
 * Created on 2016/04/10, 1:50
 */

#ifndef EEPROM_H
#define	EEPROM_H





//不完全型定義
typedef struct FileBuffer* File;
//ファイル
typedef enum{
    FileSystem//名前は変だがシステム用のファイル
}FileNames_t;
//目的


void eeprom_setup();

File eeprom_open(FileNames_t);
int eeprom_close(File);

int eeprom_putc(File,char);
int eeprom_puts(File,const char*);


int eeprom_flush(File);

#endif	/* EEPROM_H */

