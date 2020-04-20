/* 
 * File:   i2c_DRV.h
 * Author: Grinev
 *
 * Created on 13 ноября 2015 г., 16:43
 */

#ifndef I2C_DRV_H
#define	I2C_DRV_H

#include "..\HardwareProfile.h"
#include <xc.h>

/***********************************
 * I2CxBRG = (FCY/FSCL - FCY/10,000,000) - 1
 * Fcy=GetPeripheralClock()
 * Fscl=400000
 ***********************************/
#define Fscl (400000ul)
#define I2CxBRG (GetPeripheralClock()/Fscl-GetPeripheralClock()/10000000L)-1

/*********************************************************************
Function Prototype : void i2c_Close(void)
Description        : This function turns off the I2C module 
Arguments          : None 
Return Value       : None 
Remarks            : This function disables the I2C module and clears the
                     Master and Slave Interrupt Enable and Flag bits.
*********************************************************************/
void i2c_Close(void);

/************************************************************
 * Function Prototype : void i2c_Init(unsigned int cfg, unsigned int baudcfg)
 * Description        : Инициализация I2C
 * Arguments          : cfg - конфигурация
 *                    : baudcfg - скорость
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Init(void);

/************************************************************
 * Function Prototype : void i2c_idle (void)
 * Description        : ожидание окончания активности
 * Arguments          : None
 * Return Value       : None
 * Remarks            : 
 ***********************************************************/
void i2c_Idle (void);

/************************************************************
 * Function Prototype : void i2c_stop (void)
 * Description        : формировать бит стоп
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Stop(void);

/************************************************************
 * Function Prototype : void i2c_start (void)
 * Description        : формирования START
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Start(void);

/************************************************************
 * Function Prototype : void i2c_Restart (void)
 * Description        : формирования начала START для записи
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void i2c_Restart(void);

/************************************************************
 * Function Prototype : char i2c_Write (char data)
 * Description        : формирования записи байта в устройство
 * Arguments          : 
 * Return Value       : 0-ok 1-error
 * Remarks            : 
 ***********************************************************/
char i2c_Write(unsigned char data);

/*********************************************************************
Function Prototype  : void i2c_ACK(void)
Description         : Generates I2C bus Acknowledge condition.
Arguments           : None
Return Value        : None
Remarks             : This function generates an I2C bus Acknowledge condition.
 *********************************************************************/
void i2c_ACK(void);

/*********************************************************************************
Function Prototype : void i2c_NACK(void)
Description        : Generates I2C bus Not Acknowledge condition during Master Receive.
Arguments          : None
Return Value       : None
Remarks            : This function generates an I2C bus Not Acknowledge condition.
 **********************************************************************************/
void i2c_NACK(void);

/************************************************************
 * Function Prototype : char i2c_Read(void)
 * Description        : Чтение байта
 * Arguments          : None
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
unsigned char i2c_Read(void);

/************************************************************
 * Function Prototype : unsigned char i2c_Read_ACK(void)
 * Description        : 
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
unsigned char i2c_Read_ACK(void);

/************************************************************
 * Function Prototype : unsigned char i2c_Read_NACK(void)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
unsigned char i2c_Read_NACK(void);

/************************************************************
 * Function Prototype : unsigned char i2c_Open(unsigned char adres)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
unsigned char i2c_Open(unsigned char adres);

/************************************************************
 * Function Prototype :
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/


#endif	/* I2C_DRV_H */

