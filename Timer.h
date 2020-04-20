/* 
 * File:   Timer.h
 * Author: Grinev
 *
 * Created on 22 ������� 2015 �., 15:31
 */

#include "HardwareProfile.h"

#ifndef TIMER_H
#define	TIMER_H

#define TimBase 1   //1 �� ������ ���������� �������
#define period  ((GetPeripheralClock()/1000/8)*TimBase)-1

/******************************************************************************
 * ��������� ������ TMR1
 * period ������ � ��
 *
 *
 *****************************************************************************/
void    Timer_Init(void);


#endif	/* TIMER_H */

