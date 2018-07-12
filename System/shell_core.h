/* 
 * File:   shell_core.h
 * Author: TERU
 *
 * Created on 2016/09/07, 16:48
 */

#ifndef SHELL_CORE_H
#define	SHELL_CORE_H
#include "file.h"
#include <stddef.h>
//Directory構造取得用:制約path_initが実行されていること。
file_t path_root();
void path_root_move(file_t);
file_t path_current();
void path_move(file_t);
//最初に必ず実行する必要がある関数
void path_init();

int path_insert(file_t brother, file_t it); //同位に要素を追加(root用)(親が追加されないので注意)
//ファイルの基本属性について
Access_t path_access_get(file_t);
void path_access_set(file_t,Access_t);
FileType_t path_filetype_get(file_t);
void path_filetype_set(file_t,FileType_t);
//ファイル名(文字列)からfile_tを取得する
file_t path_get_all(const char*); //Pathを含む
file_t path_get(const char*);

file_t directory_create(const char *name);
int directory_insert(file_t directory, file_t file);
int directory_registor(file_t); //Pathに登録する。
void directory_registor_init();

int shell_system(char* name);
int shell_system_s(int argc, char** argv);

//file
file_t execute_create(const char* name, int(*)(int, char**)); //そのまま実行可能なものつまり関数。
file_t integer_create(const char* name, int* ptr, Access_t acc);
file_t float_create(const char* name,float* ptr,Access_t acc);

//select 処理系
// 関数ポインタに復帰処理を記述すること。
void select_listen();
void select_listen_set(void (*)(void));
void select_general();
void select_general_set(void (*)(void));
void select_selected();
void select_selected_set(void (*)(void));

//まとめて登録系
typedef int(*command_t)(int, char**);
typedef struct {
    const char* name;
    command_t command;
} excute_pair;

file_t directory_insert_excute(file_t directory,const excute_pair* pair,uint16_t size);


#endif	/* SHELL_CORE_H */

