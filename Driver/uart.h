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
#define uart_back() uart_remove(1) //一文字削除
inline void uart_remove_all();

char* uart_gets(char*,size_t);

//補助(送信)
inline uint16_t uart_used();
inline char uart_bufc(char);//バッファに追加(送信はしない)
inline char uart_bufnl();
const char* uart_bufs(const char*);//バッファに追加(送信はしない)
const char* uart_bufl(const char*);//バッファに追加(送信はしない)　改行あり

inline void uart_flush();//バッファのデータを強制送信
void uart_clr();//送信バッファを破棄


inline void  uart_stop();
inline void uart_begin();
//送信系
inline char uart_putc(char);
inline char uart_putnl();
const char* uart_puts(const char*);
const char* uart_putl(const char*);

#endif	/* UART_H */

