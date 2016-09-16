
//現在は未使用


#include "timer.h"
#include "p30F4012.h"

static uint32_t p = 0;
static int16_t flag = 0;
const static uint32_t period_default = 100000; //us

void timer23_setup() {
    SRbits.IPL = 0;

    /*IPC1bits.T3IP=6;
    IFS0bits.T3IF=false;
    IEC0bits.T3IE=true;*/

    T2CONbits.TON = 0;
    T2CONbits.TSIDL = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS0 = 0;
    T2CONbits.TCKPS1 = 0;
    T2CONbits.T32 = 1;
    T2CONbits.TCS = 0;

    TMR2 = 0;
    TMR3 = 0;
    TMR3HLD = 0;

    /*timer_period(period_default);//割り込みの周期 単位はμs(下限:2us)
    PR2=0x0000FFFF & p;
    PR3=p>>16;*/

}

void timer23_period(uint32_t period) {
    p = 20 * period;
}

void timer23_enable(bool check) {
    T2CONbits.TON = check;
    if (check == false) {
        flag = 0;
    }
}

int16_t timer23_check() {
    return flag;
}

extern void delay_ns(uint16_t);
/*void delay_ns(uint16_t wait) {
    wait /= 500; //補正値　厳密には2200ns+ [wait]ns待つ
    while (wait-- > 0);
}
 */
/*
inline void delay_us(uint16_t wait) {
    if (wait > 3) {
        wait-=3;
    }else{
        wait=1;
    }
    wait = ((uint32_t) wait * 5) >> 1;
    //timer initialize
    T1CONBITS config;
    config.TON = false;
    config.TSIDL = false; //if idle, but work
    config.TGATE = false;
    config.TCKPS = 1; //8^x prescale
    config.TSYNC = false; //NC
    config.TCS = false; //20MHz

    T1CONbits = config;

    PR1 = wait; //準備中
    TMR1 = 0x0000;
    //initialize interrput
    IFS0bits.T1IF = false;
    IEC0bits.T1IE = false; //ポーリングのため不要
    T1CONbits.TON = true;

    while (!IFS0bits.T1IF);

    return;
}
*/
extern void delay_us(uint16_t);

inline void delay_ms(uint16_t);