/* 
 * File:   UC1601_Commands.h
 * Author: Grinev
 *
 * Created on 13 ноября 2015 г., 17:06
 */

#ifndef UC1601_COMMANDS_H
#define	UC1601_COMMANDS_H

#define BiasRatio   0x03    //Соотношение между VLCD и VD 11:9
#define PM          125     //VBIAS потенциометр

     
#define UC1601S         0x70    //Адрес UC1601S
#define WriteComand     0x00    //Запись Команд
#define WriteData       0x02    //Запись Данных
#define ReadData        0x03    //Чтение данных

//Команды
#define SystemReset     0xE2    //Системный сброс
#define SetLCDBiasRatio 0xEB    //Установить отношение BIAS для LCD
#define SetVbias        0x81    //Установить VBIAS потенциометр
#define SetLCDMapping   0xC6    //Стандартная X Y адресация (биты 1-2)
#define DisplayEnable   0xAF    //Включить дисплей (


#endif	/* UC1601_COMMANDS_H */

