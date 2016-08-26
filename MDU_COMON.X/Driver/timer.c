#include "timer.h"
#include "p30F4012.h"

static uint32_t p,x=0;
static int16_t flag=0;
const static uint32_t period_default=250000;//us


void timer_setup(){
    SRbits.IPL=0;
    
    IPC1bits.T3IP=6;
    IFS0bits.T3IF=false;
    IEC0bits.T3IE=true;
    
    T2CONbits.TON=0;
    T2CONbits.TSIDL=0;
    T2CONbits.TGATE=0;
    T2CONbits.TCKPS0=0;
    T2CONbits.TCKPS1=0;
    T2CONbits.T32=1;
    T2CONbits.TCS=0;
    
    TMR2=0;
    TMR3=0;
    TMR3HLD=0;
    
    timer_period(period_default);//割り込みの周期 単位はμs(下限:2us)
    PR2=0x0000FFFF & p;
    PR3=p>>16;
    
}

void timer_period(uint32_t period){
    p=20*period;
}

void timer_enable(bool check){
    T2CONbits.TON=check;
    if(check==false){
        flag=0;
    }
}

/*int16_t timer_check(){
    return flag;
}*/
