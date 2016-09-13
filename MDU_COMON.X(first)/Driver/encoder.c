#include "encoder.h"
#include "p30F4012.h"

const int16_t pos=0x7fff;
static int16_t rate=0;
static int8_t flag=0;
//static int8_t cnt_flag=0;
static int16_t spin=400; 
static uint16_t period=1200;//現在100ms(10Hz)_
static uint32_t ev_period=2000000;

void encoder_setup(){
    
    //QEI Wake up
    QEICONBITS qcon;
    qcon.QEISIDL=false;//when idle mode, begin 
    qcon.QEIM=0b111;//as comparing between max and pos 
    qcon.SWPAB=false;//swap fag
    qcon.PCDOUT=false;//direction output
    qcon.TQGATE=true;//timer gate
    qcon.TQCKPS=0b00;//priscaler 1:1
    qcon.POSRES=false;//position reset
    qcon.TQCS=false;//clock sourse is form Tcy
    QEICONbits=qcon;
    
    DFLTCONBITS dcon;
    dcon.CEID=false;//an interrput of position error diseable
    dcon.QEOUT=false;//digital filiter enable
    
    dcon.QECK=1;//priscaler divsion
    DFLTCONbits=dcon;
    
    
    MAXCNT=0xFFFF;
    POSCNT=pos;
    
    IFS2bits.QEIIF=false;    
}

void counter_setup(){
    
 IEC0bits.CNIE=false;
 CNEN1bits.CN6IE=true;
 IFS0bits.CNIF=false;
 //IEC0bits.CNIE=true;
 IPC3bits.CNIP=6;
 
 
    T4CONbits.TON=0;
    T4CONbits.TSIDL=0;
    T4CONbits.TGATE=0;
    T4CONbits.TCKPS0=0;
    T4CONbits.TCKPS1=0;
    T4CONbits.T32=1;
    T4CONbits.TCS=0;
    
    TMR4=0;
    TMR5=0;
    TMR5HLD=0;
 
}



inline int16_t encoder_raw(){
    //int16_t sub=pos-POSCNT;
    //POSCNT=pos;
    return POSCNT;
}

inline int16_t encoder_speed_raw(){
    return (rate);//パルス/kHz
}

inline int16_t encoder_spin_raw(){
    return(rate/spin);//r/kHz
}

inline void encoder_direction(bool dir){
    //set direction
    QEICONbits.SWPAB=dir;
}

void encoder_period(uint16_t e_period){//ms
    ev_period=20000*(uint32_t)e_period;
    period=12*e_period;
}

int16_t timer_flag(){
    return flag;
}

void _ISR _PWMInterrupt(){
static uint16_t cnt;
    if(cnt==period/*(++cnt & 0xFF)==0x01*/){
       // LATEbits.LATE2=true;
     flag=1;
     rate=POSCNT-pos;
     POSCNT=pos;
     cnt=0;
    }else{
        flag=0;
    }
    cnt++;
    IFS2bits.PWMIF=false;
}

void _ISR _CNInterrupt(){
       T4CONbits.TON=0;
      uint32_t hz=0; 
       hz=0x0000FFFF&TMR4;
       uint32_t c=TMR5HLD;
       hz=hz+(c<<16);
       period=12*hz/20000;
    TMR4=0;
    TMR5=0;
    TMR5HLD=0;
}

uint32_t get_encoder_period(){
    return ev_period;
}