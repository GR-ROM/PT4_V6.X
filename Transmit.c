/*********************************************************
 * Transmit.c
 *********************************************************/
#include <xc.h>
#include "mytype.h"
#include "CRC8.h"
#include "PWM.h"
#include "Timer.h"
#include "Key.h"


void ByteOut(UINT8 bt);
void DltByte(void);

extern volatile int TimeByte;

void Transmit(Codes_t BufPrd) {
    int i, m;
    LATDbits.LATD1 = 1; //Включить светодиод передача
    FreqOut(1);
    while (1) {
        /*Пауза 15 бит*/
        for (i = 15; i > 0; i--) {
            DltByte();
        }
        for (m = 0; m < 4; m++) {
            ByteOut(BufPrd.BufP[m]);
        }
        if (kbhit()) return;
    }
}

void ByteOut(UINT8 bt) {
    int j;
    FreqOut(0);
    DltByte(); //Старт
    for (j = 8; j > 0; j--) {
        FreqOut(bt & 0x01);
        DltByte();
        bt = bt >> 1;
    }
    FreqOut(1); //Стоп
    DltByte();
    DltByte();
}

void DltByte(void) {
    TimeByte = 343;
    while (TimeByte) {
        if(kbhit()){
            Nop();
            UnpressedKey();
            Nop();
            __asm__ volatile ("reset"); 
        }
        
    }
}