/* 
 * File:   error.h
 * Author: TERU
 *
 * Created on 2016/09/17, 1:06
 */

#ifndef ERROR_H
#define	ERROR_H

enum SystemError{
    ERROR_NONE=0,//エラーとして認識されない。
    ERROR_UNKNOWN=1,//原因不明
    ERROR_NOT_EXIST=2,//対象が存在しない
    ERROR_NOT_SURPPORT=3,//まだサポートしていない
    ERROR_NOT_EXCUTE=4,//実行できない(コマンドではない?)
    ERROR_NOT_DIRECTORY=5,//ディレクトリではない
    ERROR_FOUND_OUT=6,//見つからない
    ERROR_INPUT_FEW=7,//入力パラメータが少ない
    ERROR_FILE_TYPE_NONE=8,
    ERROR_FILE_TYPE_DIRECTORY=9,
    ERROR_NOT_ACCESS=10,//アクセス権がない
    ERROR_INTPUT_FRAUD=11,//入力が不正
};
typedef enum SystemError error_t;


int error_print(error_t);
const char* error_text(error_t);
#endif	/* ERROR_H */

