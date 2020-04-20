/* 
 * File:   Timer.h
 * Author: Grinev
 *
 * Created on 22 ќкт€брь 2015 г., 15:31
 */

#include "HardwareProfile.h"

#ifndef TIMER_H
#define	TIMER_H

#define TimBase 1   //1 мс период системного таймера
#define period  ((GetPeripheralClock()/1000/8)*TimBase)-1

/******************************************************************************
 * —истемный таймер TMR1
 * period ѕериод в мс
 *
 *
 *****************************************************************************/
void    Timer_Init(void);


#endif	/* TIMER_H */

