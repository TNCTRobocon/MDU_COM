#include "encoder.h"
#include "p30F4012.h"

const int16_t pos=0x7fff;
static int16_t spin=400; 
static uint32_t ev_period=2000000;
static uint16_t period=1200;//現在100ms(10Hz)

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
    IEC2bits.QEIIE=false;
    
}

inline int16_t encoder_raw(){
    //int16_t sub=pos-POSCNT;
    //POSCNT=pos;
    return POSCNT;
}

inline int16_t encoder_speed_raw(){
    return (pid_rate());//パルス/kHz
}

inline int16_t encoder_spin_raw(){
    return(pid_rate()/spin);//r/kHz
}

inline void encoder_direction(bool dir){
    //set direction
    QEICONbits.SWPAB=dir;
}

void encoder_period(uint16_t e_period){//ms
    ev_period=20000*(uint32_t)e_period;
    period=12*e_period;
   pwm_pid_period(period); 
}




uint32_t get_encoder_period(){
    return ev_period;
}