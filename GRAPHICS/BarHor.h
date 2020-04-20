/* 
 * File:   BarHor.h
 * Author: Grinev
 *
 * Created on 16 февраля 2016 г., 14:09
 */

#ifndef BARHOR_H
#define	BARHOR_H

/********************************************************************
 * Функция: void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * Аргументы: left,top,right,bottom координаты углов
 *            vol Ширина в %
 * 
 ********************************************************************/
void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol);
/********************************************************************
 * Функция: void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * Аргументы: left,top,right,bottom координаты углов
 *            vol Высота в %
 * 
 ********************************************************************/
void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol);

#endif	/* BARHOR_H */

