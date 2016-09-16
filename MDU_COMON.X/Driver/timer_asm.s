;
    .include "p30f4012.inc"
    .text 
    .global _delay_ns
_delay_ns:
    SUB #400,W0;//補正値
    BRA N,delay_ns_exit
    MOV #434,W1
    MUL.UU W0,W1,W0;//[W1,W0]=inst*(1/150),W1にほしい結果がある。
    ;初回　0チェック
    SUB #0,W1
    BRA Z,delay_ns_exit
delay_ns_loop: 
    SUB #1,W1
    BRA NZ,delay_ns_loop
delay_ns_exit:
    return
    
    .global _delay_us
_delay_us:
;timer1を使い指定された時間待つ    
;W0~W7は自由に利用できる
    MUL.UU W0,#5,W0;output [W0,W1]
    LSR W1, W1
    RRC W0, W0;//W0 as Period
    BRA Z,delay_us_exit;//if Delay==0 return
    MOV #0x4010,W2
    MOV W2,T1CON;Stop Timer
    ;Period and Counter Reset
    MOV W0,PR1
    CLR TMR1
    ;Initialize Interrupt
    BCLR IFS0,#3
    BCLR IEC0,#3
    ;Start Timer1
    BSET T1CON,#15
    ;Start Pauling
delay_us_loop:
    BTSS IFS0,#3
    goto delay_us_loop;
delay_us_exit:
    return
    
    
    .global _delay_ms
_delay_ms:
    ;//引数1 uint16_t -> W0
    MOV #79,W1
    MUL.UU W0,W1,W0 ;//W0 を補正
    CP0 W0
    BRA Z, delay_ms_exit;
    MOV #0x4030,W2 ;//Prescaler 256
    MOV W2,T1CON;Stop Timer
    ;Period and Counter Reset
    MOV W0,PR1
    CLR TMR1
    ;Initialize Interrupt
    BCLR IFS0,#3
    BCLR IEC0,#3
    ;Start Timer1
    BSET T1CON,#15
    ;Start Pauling
delay_ms_loop:
    BTSS IFS0,#3
    goto delay_ms_loop;
delay_ms_exit:
    return   
    .end


