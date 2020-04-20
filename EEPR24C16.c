/***************************************************************************
 * EEPR24C16.c
 *
 *
 *
 ***************************************************************************/

#include "i2c_DRV.h"
#include "EEPR24C16.h"


#define ADR24C16    0xA0
#define write_byte   0
#define read_byte    1


extern volatile unsigned char TimeOutSav;

void SaveUst(unsigned char *str, unsigned char dl) {
    unsigned char i;
    //adres=0;
    i2c_Start();
    i2c_Write(ADR24C16 | write_byte);
    i2c_Write(0);
    for (i = 0; i < dl; i++) {
        i2c_Write(*str++);
    }
    i2c_Stop();
}

void ReadUst(unsigned char *str, unsigned char dl) {
    unsigned char i;
    i2c_Start();
    i2c_Write(ADR24C16 | write_byte);
    i2c_Write(0);
    i2c_Restart();
    i2c_Write(ADR24C16 | read_byte);
    for (i = 0; i < dl - 1; i++) {
        *str++ = i2c_Read_ACK();
    }
    *str++ = i2c_Read_NACK();
    i2c_Stop();
}

/*********************************************************
 * 
 * 
 * 
 *********************************************************/
#define AdrCodes    32
#define LenghtCodes 23  //20
#define PageLenht   16
//Буфер для записи в 24LC16 16байт

void ReadCodesPreset(char * adres) {
    unsigned char i;
    i2c_Start();
    i2c_Write(ADR24C16 | write_byte);
    i2c_Write(AdrCodes);
    i2c_Restart();
    i2c_Write(ADR24C16 | read_byte);
    for (i = 0; i < LenghtCodes - 1; i++) {
        *adres++ = i2c_Read_ACK();
    }
    *adres++ = i2c_Read_NACK();
    i2c_Stop();
}

/*********************************************************
 * 
 * 
 * 
 *********************************************************/
void SaveCodePreset(char * adres) {
    unsigned char i;
    i2c_Start();
    i2c_Write(ADR24C16 | write_byte);
    i2c_Write(AdrCodes);
    for (i = 0; i < PageLenht; i++) {
        i2c_Write(*adres++);
    }
    i2c_Stop();
    i2c_Idle();
    i = TimeOutSav = 0;
    while (TimeOutSav - i < 5) continue;

    i2c_Start();
    i2c_Write(ADR24C16 | write_byte);
    i2c_Write(AdrCodes + PageLenht);
    for (i = 0; i < 8; i++) {
        i2c_Write(*adres++);
    }
    i2c_Stop();
    i2c_Idle();
    i = TimeOutSav = 0;
    while (TimeOutSav - i < 5) continue;
}