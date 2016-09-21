 /* File:   types.h
 * Author: TERU
 *
 * Created on 2016/03/24, 22:16
 */

#ifndef TYPES_H
#define	TYPES_H

//プログラミング 環境

#include <stdbool.h>
#include <stddef.h>
#include "../Helper/dsp_helper.h"
//#include <stdint.h>

typedef int8_t triple_t;
#define plus ((int8_t)+1)
#define zero ((int8_t)0)
#define minus ((int8_t)-1)

typedef unsigned short Q3_13;
typedef unsigned short Q4_12;
typedef uint32_t Q16_16;


typedef int16_t count_t; //個数表記用
#define nullptr NULL

//EEPROM DataSet
typedef uint16_t word_t;

//メモリー配置
#define NEAR    __attribute__ ((near))
#define FAR     __attribute__ ((far))
#define AT(X)   __attribute__ ((address(X)))
#define XMEM    __attribute__ ((space(xmemory))
#define YMEM    __attribute__ ((space(ymemory))
#define EEPROM  __attribute__ ((space(eedata)))
#define PSV     __attribute__((space(psv)))

//タスク管理用関数
typedef int (*func_t)(int, char**);

typedef enum {
    OptionNone,
    OptionSystem,
    OptionDisenable
} option_t;



#endif	/* TYPES_H */

