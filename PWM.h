/* 
 * File:   PWM.h
 * Author: Grinev
 *
 * Created on 28 марта 2016 г., 15:17
 */

#ifndef PWM_H
#define	PWM_H

void    InitPWM(void);

/************************************************************
 * Function Prototype : viod SetPerF0(unsigned int per)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/

void SetPerF0(unsigned int val);

/************************************************************
 * Function Prototype : viod SetPerF1(unsigned int per)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void SetPerF1(unsigned int val);

/******************************************************************************
 *Устанавливает одну из частот
 *
 *
 *****************************************************************************/
void FreqOut(unsigned char val);



#endif	/* PWM_H */

