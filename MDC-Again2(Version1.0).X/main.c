
#define _XTAL_FREQ 320000
#include <pic.h>

#include "pwm.h"
#include "i2c.h"
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF     // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF  // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


//i2cのアドレス
const uint8_t address = 0x39;


void main (){
    //clock config
    OSCCON=0b11110000;
    
    motor_init();//モーターとチャージポンプを有効にする。
    i2c_init(address);//i2cを有効にする。
    
    //わりこみの初期化を行う。
    INTCONbits.PEIE=true;
    INTCONbits.GIE=true;
    
    //tmr_dt(Q8(0.25f),200);//チャージポンプの周期とdutu比
    //pwm_dt(0x7FFF);//モーターのduty比。
    while (1){
        pwm_dt((int16_t)i2c_get()<<8);
        
    }
}

//割り込みルーチン
void interrupt isr(){
    
    if (PIR1bits.SSP1IF){
        i2c_isr();
        
    }
//    if (INTCONbits.T0IF){
//        GIE=false;
//        INTCONbits.T0IF=false;
//        isr_tmr();
//        GIE=true;
//    }
    
    
}