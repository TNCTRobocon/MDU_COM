/* 
 * File:   configuration.h
 * Author: TERU
 *
 * Created on 2016/03/23, 0:16
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H


//デバイス環境
#include "p30F4012.h"


//環境構築
#define FORIG (1000000UL)
#define FOSC (FORIG*8/4) //10[MHz]*8[PLL]/4[DIV]=20[MHz] 

//10MHz*8(PLL)/4(divsion))

//アドレス取得　ピン配置
#define SEL1() PORTEbits.RE1
#define SEL2() PORTEbits.RE0
#define SEL4() PORTBbits.RB0
#define SEL8() PORTBbits.RB1
//アドレス取得マクロ



//Stoper
#define SW_ST()   PORTEbits.RE8

//LED
#define LED_RX      LATDbits.LATD0
#define LED_TX      LATDbits.LATD1
#define LED_ERROR   LATEbits.LATE2
#define LED_APP     LATBbits.LATB2

#define LED_HIGH(x) ((x)=true)
#define LED_LOW(x)  ((x)=false)
#define LED_INV(x)  ((x)=(^x))

//PWM
#define ST_PIN      LATEbits.LATE4
//UART
#define RX_BUFFER_SIZE  (64) //受信バッファの一つ当たりの大きさ
#define TX_BUFFER_SIZE  (64)
#define CMD_LENGTH (32)        // システムが受け入れられる文字の最大数、
#define CMD_MAX     (16)        // 最大分割数(1LINEあたり)
#define FILE_MAX    (32)        // 最大ファイル数
#define MULTI_MAX (8) //同時に実行できるコマンドの最大値
#define WORD_MAX (32)
#define PATH_DEPTH_MAX (8)
#define QUICK_MAX (8) 
#define WORD_MAX (32)

//EEPROM
#define EEPROM_BUFFER_SIZE (64) //EEPROMの書き込み用バッファ

#endif	/* CONFIGURATION_H */

