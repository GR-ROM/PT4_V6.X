/* 
 * File:   SPI.h
 * Author: Grinev
 *
 * Created on 21 ������� 2015 �., 15:41
 */

#ifndef SPI_H
#define	SPI_H

#include <GenericTypeDefs.h>

/******************************************************
 * void    SPI_Init(void)
 * �������������� SPI1
 * �� 16 ������� �������
 ******************************************************/
void    SPI_Init(void);

/*******************************************************
 * void SPI_Put(UINT16 dat)
 * ������� � SPI
 * ���� �������
 * ������ ������� ���������
 * �� ���������� ���������
 *******************************************************/
void    SPI_Put(UINT16 dat);


#endif	/* SPI_H */

