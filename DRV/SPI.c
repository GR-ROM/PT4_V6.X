/******************************************************
 * SPI.c
 * 
 * 
 * 
 ******************************************************/

#include <xc.h>
#include <GenericTypeDefs.h>

/******************************************************
 * void    SPI_Init(void)
 * �������������� SPI1
 * �� 16 ������� �������
 ******************************************************/
void    SPI_Init(void){
	SPI1STATbits.SPIEN = 0;		// ��������� SPI
	SPI1CON1 = 0;               // �������� ������������
	SPI1CON1bits.DISSCK = 0;	// Internal SPI clock is enabled
	SPI1CON1bits.DISSDO = 0;	// SDOx pin is controlled by the module
	SPI1CON1bits.MODE16 = 1;	// Communication is byte-wide (16 bits)
    SPI1CON1bits.CKP = 1;
    SPI1CON1bits.CKE = 1;
	SPI1CON1bits.MSTEN = 1;		// Master mode
    SPI1CON2bits.FRMEN = 0;     //
    SPI1STATbits.SPIROV = 0;    //
    SPI1CON1bits.SPRE=7;        //Secondary prescale
    SPI1CON1bits.PPRE=2;        //Primary prescale
	SPI1STATbits.SPIEN = 1;		// �������� SPI
}

/*******************************************************
 * void SPI_Put(UINT16 dat)
 * ������� � SPI
 * ���� �������
 * ������ ������� ���������
 * �� ���������� ���������
 *******************************************************/
void    SPI_Put(UINT16 dat){
    IFS0bits.SPI1IF=0;
    SPI1STATbits.SPIROV = 0;
    SPI1BUF=dat;
    while(!IFS0bits.SPI1IF);
    IFS0=0;
}
/*******************************************************
 * 
 * 
 * 
 *******************************************************/

/******* END SPI.c  **********/