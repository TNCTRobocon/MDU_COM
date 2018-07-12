#include "../Setting/configuration.h"
#include "ports.h"

void ports_setup(){
    //Switch (STOP)
    TRISEbits.TRISE8=true;
    //Switch Address (Din)
    TRIS_SEL1(true);
    TRIS_SEL2(true);
    TRIS_SEL4(true);
    TRIS_SEL8(true);
    
    ADPCFGbits.PCFG0=true;
    ADPCFGbits.PCFG1=true;
    //ENCODER (Din)
    TRISBbits.TRISB3=true;
    TRISBbits.TRISB4=true;
    TRISBbits.TRISB5=true;
    
    ADPCFGbits.PCFG3=true;
    ADPCFGbits.PCFG4=true;
    ADPCFGbits.PCFG5=true;

    //LED(Dout)
    TRISEbits.TRISE2=false;//LED_ERROR
    TRISBbits.TRISB2=false;//LED_APP
    TRISDbits.TRISD0=false;//LED_RX
    TRISDbits.TRISD1=false;//LED_TX
    
    LATEbits.LATE2=false;
    LATBbits.LATB2=false;
    LATDbits.LATD0=false;
    LATDbits.LATD1=false;
    //UART
    LATCbits.LATC13=true;
    TRISCbits.TRISC14=true;//RX
    TRISCbits.TRISC13=false;//TX

    //PWM
    TRISEbits.TRISE3=false;//HalfBridge A
    TRISEbits.TRISE4=false;//ST
    TRISEbits.TRISE5=false;//HalfBridge B
    //PWM_ENABLE
    LATEbits.LATE4=true;//begin
}

inline uint16_t port_address(){
    return  ((!PIN_SEL1())<<0)+
            ((!PIN_SEL2())<<3)+
            ((!PIN_SEL4())<<2)+
            ((!PIN_SEL8())<<1);   
}

inline void led_rx(bool fag){
    LED_RX=fag;
}

inline int16_t port_get(int idx){
    switch (idx){
        case 1:
            return PORTB;
        case 2:
            return PORTC;
        case 3:
            return PORTD;
        case 4:
            return PORTE;
        case 5:
            return PORTF;
        default:
            return -1;//ERROR
    }
}

inline bool pin_encode_idx(){
    return PORTBbits.RB3;
}
inline bool pin_encode_x(){
    return PORTBbits.RB4;
}
inline bool pin_encode_y(){
    return PORTBbits.RB5;
}