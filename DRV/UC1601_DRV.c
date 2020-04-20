/****************************************************************
 * UC1601_DRV.c
 * 
 * 
 ****************************************************************/
#include "UC1601_Commands.h"
#include "I2C_DRV.h"
#include "SCREEN_DRV.h"
#define FCY GetSystemClock()	// ���� �������� 
#include <libpic30.h>	// ���������� �������
/*******************************************************
 * Uc1601_Initialise(void)
 * 
 *******************************************************/
void    Uc1601_Initialise(void){
    /*����� �������*/
	__delay_ms(10); // 10��
    i2c_Init();
    i2c_Open(UC1601S | WriteComand);
	i2c_Write(SystemReset);				//��������� �����
	i2c_Stop();
	__delay_ms(10); // 10��
	/* */
	i2c_Open(UC1601S | WriteComand);
	//i2c_Write(SetLCDBiasRatio);			//���������� ��������� BIAS ��� LCD
	i2c_Write(SetVbias);				//���������� VBIAS ������������
	i2c_Write(120);						//120~124
	//i2c_Write(0b11000110);		// ��������� ���� �������� ����� � ���, � ����� �� ����� 154
	i2c_Write(SetLCDMapping); //����������� X Y ��������� (���� 1-2)
	// i2c_Write(0b11000000); 	// ��������� ���� �������� ����� � ���, � ����� �� ����� 120/77
	// i2c_Write(0b10001000);	//
	i2c_Write(DisplayEnable); 	// �������� �������
	i2c_Stop();
}

/********************************************************
 * Clear_UC1601(void)
 * �������� �������
 ********************************************************/
void Clear_UC1601(void){
    int i;
    UINT8 * pScrn;
    i2c_Open(UC1601S | WriteComand);
	i2c_Write(0b10110000); //Set Page Address �������� 0
    i2c_Write(0b00000000); // ������� 0 MSB CA0-CA3
    i2c_Write(0b00010000); // ������� 0 LSB CA4-CA7
    i2c_Stop();
    pScrn=ScrenBuf;
    i2c_Open(UC1601S | WriteData); //������ ������
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
    i2c_Write(0b10110000); //�������� 0
    i2c_Write(0b00000000); // ������� 0 MSB
    i2c_Write(0b00010000); // ������� 0 LSB
    i2c_Stop();
    pScrn=ScrenBuf;
    i2c_Open(UC1601S | WriteData); //������ ������
    for(i=0;i<ScrnBufSize;i++){
        i2c_Write(*pScrn++);
    }
    i2c_Stop();
}


