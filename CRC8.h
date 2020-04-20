/* 
 * File:   CRC8.h
 * Author: Grinev
 * http://www.zorc.breitbandkatze.de/crc.html
 * Created on 29 Сентябрь 2015 г., 16:54
 */

#ifndef CRC8_H
#define	CRC8_H

#ifdef	__cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Poly : 0x31	 x^8 + x^5 + x^4 + 1 (1-Wire bus)
 * Init : 0xFF
 * Revert: false
 * XorOut: 0x00
 * Check : 0xF7 ("123456789")
 * MaxLen: 15 байт(127 бит) - обнаружение
 * одинарных, двойных, тройных и всех нечетных ошибок
 ******************************************************************************/
UINT8 CRC8(UINT8 *pcBlock, UINT8 len);

#ifdef	__cplusplus
}
#endif

#endif	/* CRC8_H */

