/***************************************************************
 * Timer.c
 * 
 * 
 ***************************************************************/
#include <xc.h>
#include <GenericTypeDefs.h>

#include  "HardwareProfile.h"
#include "Timer.h"
#include "Key.h"

#define LedsLcd LATDbits.LATD11
volatile unsigned char TimeOutSav;
volatile int    TimeByte;
extern UINT8 Light;
UINT8 Lcnt;
/******************************************************************************
 * ��������� ������ TMR1
 * period ������ � ��
 *
 *
 *****************************************************************************/
void    Timer_Init(void){
    T1CON = 0;          /* Clear T1CON*/
    T1CONbits.TCKPS=0b01;  /* ��������� 1:8 */
    T1CONbits.TCS=0;    /* ���������� ��������� */
    T1CONbits.TGATE=0;  /* ������ ������� �� �������� ������� */
    PR1   = period;     /* ��������� ������� */
    TMR1 = 0;           /* �������� TMR1*/
    // ��������� ����������
    INTCON1bits.NSTDIS=1; /*������ ��������� ����������*/
    IPC0bits.T1IP = 4;  //��������� ���������� ������� 4
    IEC0bits.T1IE =1;   //��������� ���������� ������� 1
    T1CONbits.TON =1;   /* �������� ������*/
    Lcnt=0;
}
/***********************************************************************
 * ���������� ���������� �� �������
 * 
 * 
 ***********************************************************************/
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    //LATDbits.LATD1^=1; //������ ����������
    Scan_Key();
    TimeOutSav++;
    TimeByte--;
    if(Light>0){
        if(Lcnt>=0 && Lcnt<=16){
            if(Lcnt==0) LedsLcd=1;
            if(Lcnt==Light) LedsLcd=0;
        }
    }else{
        LedsLcd=0;
    }
    if(++Lcnt>16) Lcnt=0;
}
