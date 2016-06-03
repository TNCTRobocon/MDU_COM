/* 
 * File:   uart.h
 * Author: TERU
 *
 * Created on 2016/03/23, 2:58
 */

#ifndef UART_H
#define	UART_H
#include "../Setting/types.h"

void uart_setup();

//補助(受信)
inline uint16_t uart_depth();//受信バッファの深度
#define uart_exist() (uart_depth()>0)
int16_t uart_find(char);//対象の文字が最初に見つかった場所
#define uart_have(x) (uart_find(x)!=-1)
//受信系
inline char uart_getc();//一文字受信
inline char uart_seek(int16_t idx);//idx文字先の文字を読む
#define uart_next() uart_seek(1)
inline void uart_remove(uint16_t);//文字を削除
inline void uart_remove_all();

char* uart_gets(char*,size_t);

//補助(送信)
inline uint16_t uart_used();
inline char uart_bufc(char);//バッファに追加(送信はしない)
inline const char* uart_bufs(const char*);//バッファに追加(送信はしない)
inline void uart_flush();//バッファのデータを強制送信

inline void  uart_stop();
inline void uart_begin();
//送信系
inline char uart_putc(char);
const char* uart_print(const char*,bool nl);//改行選択付き出力
#define uart_puts(str) uart_print(str,false)
#define uart_putl(str) uart_print(str,true)



#endif	/* UART_H */

