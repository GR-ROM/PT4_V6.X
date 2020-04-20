/* 
 * File:   BarHor.h
 * Author: Grinev
 *
 * Created on 16 ������� 2016 �., 14:09
 */

#ifndef BARHOR_H
#define	BARHOR_H

/********************************************************************
 * �������: void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * ���������: left,top,right,bottom ���������� �����
 *            vol ������ � %
 * 
 ********************************************************************/
void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol);
/********************************************************************
 * �������: void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * ���������: left,top,right,bottom ���������� �����
 *            vol ������ � %
 * 
 ********************************************************************/
void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol);

#endif	/* BARHOR_H */

