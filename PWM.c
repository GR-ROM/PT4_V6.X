/****************************************************************************
 * PWM.c
 * 
 * Используется для генерации частот
 * 
 ****************************************************************************/

/****************************************************************************
1.установить требуемый период сигнала, загрузив соответствующий регистр
периода PRx;
2.установить требуемую длительность активного уровня ШИМ, загрузив
соответствующий регистр OCxRC;
3.установить начальную длительность активного уровня ШИМ, загрузив
соответствующий регистр OCxR;
4.если необходимо разрешить прерывание по совпадению таймера с
регистром периода и прерывание от модуля сравнения (это прерывание
генерируется по событию аварии);
5.сконфигурировать режим работы модуля PWM – биты OCM<2:0>
(OCxCON<2:0>);
 6. установить пределитель базового таймера и разрешить его работу
установкой бита TON (TxCON<15>).
 
 ****************************************************************************/
#include <xc.h>

#include "HardwareProfile.h"
#include "PWM.h"


#define TF0  7197  //  1000000/719.7
#define TF1  7697  // 1000000/769.7
#define TF2  7250   //
#define TF3  7750   //

#define LEDOUT  LATDbits.LATD1

//#define PERIODF0 (GetPeripheralClock()*10/TF0)-1
//#define PERIODF1 (GetPeripheralClock()*10/TF1)-1

volatile unsigned int PERIODF0, PERIODF1;

/************************************************************
 * Function Prototype : void    InitPWM(void)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void InitPWM(void) {
    unsigned int m;
    m = PERIODF1;
    PR2 = m;
    OC1RS = m / 2;
    OC1R = m - 10;
    OC1CONbits.OCM = 0b110;
    T2CONbits.TON = 1;

}

/************************************************************
 * Function Prototype : viod SetPerF0(unsigned int per)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void SetPerF0(unsigned int val) {
    PERIODF0 = (GetPeripheralClock()*10 / val) - 1;
}

/************************************************************
 * Function Prototype : viod SetPerF1(unsigned int per)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void SetPerF1(unsigned int val) {
    PERIODF1 = (GetPeripheralClock()*10 / val) - 1;
}

/******************************************************************************
 *Устанавливает одну из частот
 *
 *
 *****************************************************************************/
void FreqOut(unsigned char val) {
    if (val == 0) {
        //T2CONbits.TON = 0;
        PR2 = PERIODF0;
        OC1RS = PERIODF0 / 2;
        OC1R = PERIODF0 - 10;
        //T2CONbits.TON = 1;
        //LEDOUT=0;
    }

    if (val == 1) {
        //T2CONbits.TON = 0;
        PR2 = PERIODF1;
        OC1RS = PERIODF1 / 2;
        OC1R = PERIODF1 - 10;
        //T2CONbits.TON = 1;
        //LEDOUT=1;
    }
}