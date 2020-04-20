/****************************************************************
 * UC1601_DRV.c
 * 
 * 
 ****************************************************************/
#include "UC1601_Commands.h"
#include "I2C_DRV.h"
#include "SCREEN_DRV.h"
#define FCY GetSystemClock()	// Наша тактовая 
#include <libpic30.h>	// библиотека функций
/*******************************************************
 * Uc1601_Initialise(void)
 * 
 *******************************************************/
void    Uc1601_Initialise(void){
    /*Сброс дисплея*/
	__delay_ms(10); // 10мС
    i2c_Init();
    i2c_Open(UC1601S | WriteComand);
	i2c_Write(SystemReset);				//Системный сброс
	i2c_Stop();
	__delay_ms(10); // 10мС
	/* */
	i2c_Open(UC1601S | WriteComand);
	//i2c_Write(SetLCDBiasRatio);			//Установить отношение BIAS для LCD
	i2c_Write(SetVbias);				//Установить VBIAS потенциометр
	i2c_Write(120);						//120~124
	//i2c_Write(0b11000110);		// настройка типа разветки свеху в низ, и слево на право 154
	i2c_Write(SetLCDMapping); //Стандартная X Y адресация (биты 1-2)
	// i2c_Write(0b11000000); 	// настройка типа разветки свеху в низ, и слево на право 120/77
	// i2c_Write(0b10001000);	//
	i2c_Write(DisplayEnable); 	// Включить дисплей
	i2c_Stop();
}

/********************************************************
 * Clear_UC1601(void)
 * Очистить дисплей
 ********************************************************/
void Clear_UC1601(void){
    int i;
    UINT8 * pScrn;
    i2c_Open(UC1601S | WriteComand);
	i2c_Write(0b10110000); //Set Page Address страница 0
    i2c_Write(0b00000000); // колонка 0 MSB CA0-CA3
    i2c_Write(0b00010000); // колонка 0 LSB CA4-CA7
    i2c_Stop();
    pScrn=ScrenBuf;
    i2c_Open(UC1601S | WriteData); //Запись данных
    for(i=0;i<ScrnBufSize;i++){
        i2c_Write(0x00);
        *pScrn++=0x00;
    }
    i2c_Stop();
}

/************************************************************
 * void Update_Screen(void)
 ************************************************************/
void Update_Screen(void){
    UINT8 * pScrn;
    int i;
    i2c_Open(UC1601S | WriteComand);
    i2c_Write(0b10110000); //Страница 0
    i2c_Write(0b00000000); // колонка 0 MSB
    i2c_Write(0b00010000); // колонка 0 LSB
    i2c_Stop();
    pScrn=ScrenBuf;
    i2c_Open(UC1601S | WriteData); //Запись данных
    for(i=0;i<ScrnBufSize;i++){
        i2c_Write(*pScrn++);
    }
    i2c_Stop();
}


