/*****************************************************************************
 * CRC8.c
 * Poly : 0x31	 x^8 + x^5 + x^4 + 1	(1-Wire bus)
 * Init : 0xFF
 * Revert: false
 * XorOut: 0x00
 * Check : 0xF7 ("123456789")
 * MaxLen: 15 байт(127 бит) - обнаружение
 * одинарных, двойных, тройных и всех нечетных ошибок
 * TO DO: заменить на табличный алгоритм
 ******************************************************************************/
#include <GenericTypeDefs.h>

UINT8 CRC8(UINT8 *pcBlock, UINT8 len) {
    UINT8 crc = 0xFF;
    UINT8 i;
    while (len--) {
        crc ^= *pcBlock++;
        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
    return crc;
}
