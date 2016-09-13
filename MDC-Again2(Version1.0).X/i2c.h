/* 
 * File:   i2c.h
 * Author: TERU
 *
 * Created on 2015/08/21, 14:02
 */

#ifndef I2C_H
#define	I2C_H
#include <stdint.h>
#include <stdbool.h>
void i2c_init(uint8_t address);


int8_t i2c_get();
//bool i2c_recived();

//void i2c_task();


inline void i2c_isr();
#endif	/* I2C_H */

