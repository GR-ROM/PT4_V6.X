/* 
 * File:   AD9833.h
 * Author: Grinev
 *
 * Created on 21 ������� 2015 �., 15:47
 */

#ifndef AD9833_H
#define	AD9833_H

#include <GenericTypeDefs.h>

#include "SPI.h"
#include "mytype.h"


// ������� ����������, ������������� � AD9833
#define FMCLK 3656000UL
#define Chip_Select()   LATDbits.LATD9=0
#define ChipUnselect() LATDbits.LATD9=1
#define freq_hz 2125
//#define UINT32 FREQ = ((UINT64)freq_hz * (UINT64)0x10000000)/(UINT64)FMCLK;
// 72090
// 2^28=268435456
// 268435456/8192000=
//(2200*268435456)/8192000=72089.6
#define WRITE_TO_FREQ1_REG	 0x8000
#define WRITE_TO_FREQ0_REG	 0x4000
#define WRITE_TO_PHASE1_REG	 0xE000
#define WRITE_TO_PHASE0_REG	 0xC000
//-------------------------------
#define SINUS			 0
#define TRIANGLE		 1
#define SQUARE			 2

#define USE_FREQ0_REG		 0
#define USE_FREQ1_REG		 1
#define USE_PHASE0_REG		 0
#define USE_PHASE1_REG		 1
//-------------------------------
#define POWER_OFF		 0
#define POWER_ON		 1
#define PHASE_RESOLUTION	 1    // 10
#define VSUPPLY 		 3250 // 3300 mV



void AD9833_init(unsigned char mode, Ust SetParam);

//-------------------------------
/* AD9833 SET PHASE *
 * ������������� ���� � � ���� �� ���� ������� ���������
 * ���� ������ ���� � ��������: �� 0 .. �� 360 � ��������� � 1 ������
 * ����� ���������� ���� � ��������� �� 0.1 ������
 * ������� ������� �������� ������� PHASE_RESOLUTION � 1 �� 10
 * ����� ���� ������������� ����*10,
 * ������ ���� ����� ���������� 22.5 �������� ������� ��������:
 * AD9833_setPhase(WRITE_TO_PHASE0_REG, 225);
------------------------------- */
void AD9833_setPhase(UINT16 REG, unsigned long Phase);
void AD9833_usedPhaseReg(unsigned char REG);
UINT16  GET_STATAD9833(void);
/* AD9833, 
 * CHANGE USED FREQVENCY REGISTER
 * � AD9833 ������� 2 ��������� ��������. 
 * ���� � ����� �������� �������� ������� �������,
 * ����� ������� �� ������ ������� ��������� ������� 
 * � � ������ ������ ������������ �� ���.
 * ��������� ������� ��� ��� � ������������ ��� 
 * ������������ ����� ����� ����� ����������
 * ��� ������ �������������� ��������  
//-------------------------------*/
void AD9833_usedFreqReg(unsigned char REG);

#define _SetFreq0    SetParam.SetDat.SetFreq0
#define _SetFreq1    SetParam.SetDat.SetFreq1
#define _SetPhase0    SetParam.SetDat.SetPhase0
#define _SetPhase1    SetParam.SetDat.SetPhase1


#endif	/* AD9833_H */

