#include "encoder.h"
#include "p30F4012.h"

const int16_t pos=0x7fff;
static int16_t rate=0;

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
    //poss=POSCNT;
    return POSCNT;
}

inline int16_t encoder_speed_raw(){
    return (rate);  
}

inline void encoder_direction(bool dir){
    //set direction
    QEICONbits.SWPAB=dir;
}

void _ISR _T3Interrupt(){
    rate=POSCNT-pos;
    POSCNT=pos;
    IFS0bits.T3IF=false;
}
