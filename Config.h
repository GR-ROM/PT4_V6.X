/* 
 * File:   Config.h
 * Author: Grinev
 *
 * Created on 22 ќкт€брь 2015 г., 15:39
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

//Ѕиты конфигурации
/*
_CONFIG1(JTAGEN_OFF & GCP_OFF & COE_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2 & WDTPS_PS1024 & FWPSA_PR32 & WINDIS_ON)
_CONFIG2(IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_EC & FNOSC_PRIPLL)
*/        
// CONFIG2
#pragma config POSCMOD = EC             // Primary Oscillator Select (EC Oscillator mode selected)
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS1024           // Watchdog Timer Postscaler (1:1,024)
#pragma config FWPSA = PR32             // WDT Prescaler (Prescaler ratio of 1:32)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)




#endif	/* CONFIG_H */
