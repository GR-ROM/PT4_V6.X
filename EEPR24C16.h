/* 
 * File:   EEPR24C16.h
 * Author: Grinev
 *
 * Created on 9 марта 2016 г., 14:55
 */

#ifndef EEPR24C16_H
#define	EEPR24C16_H

/*************************************************
 * Запись и чтение установок
 *************************************************/
void SaveUst(unsigned char *str, unsigned char dl);
void ReadUst(unsigned char *str, unsigned char dl);
/*********************************************************
 * 
 * 
 * 
 *********************************************************/
void ReadCodesPreset(char * adres);

/*********************************************************
 * 
 * 
 * 
 *********************************************************/
void SaveCodePreset(char * adres);


#endif	/* 24C16_H */

