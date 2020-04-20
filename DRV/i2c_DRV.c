/*************************************************************
 * i2c_DRV.c
 * 
 * 
 * 
 *************************************************************/

#include <xc.h>
#include "i2c_DRV.h"

/*********************************************************************
Function Prototype : void i2c_Close(void)
Description        : This function turns off the I2C module 
Arguments          : None 
Return Value       : None 
Remarks            : This function disables the I2C module and clears the
                     Master and Slave Interrupt Enable and Flag bits.
 *********************************************************************/
void i2c_Close(void) {
    /* clear the I2CEN bit */
    I2C1CONbits.I2CEN = 0;

    /* clear the SI2C & MI2C Interrupt enable bits */
    IEC1bits.SI2C1IE = 0;
    IEC1bits.MI2C1IE = 0;

    /* clear the SI2C & MI2C Interrupt flag bits */
    IFS1bits.SI2C1IF = 0;
    IFS1bits.MI2C1IF = 0;
}

/************************************************************
 * Function Prototype : void i2c_Init(unsigned int cfg, unsigned int baudcfg)
 * Description        : Инициализация I2C
 * Arguments          : cfg - конфигурация
 *                    : baudcfg - скорость
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Init(void)
/* тактовая задается 100/400/1000 кГц */ {
    /* настройка рабочей частоты шины */
    /*I2C1BRG = ((((FCY / 2) / FCLOCK) / 1000)-((FCY / 2) / 10000000 + (FCY % 2 >= 5 ? 1 : 0))) - 1;
    if (I2C1BRG <= 2) I2C1BRG = 3; // значение в регистре не может быть меньше 2 
     */
    I2C1BRG = I2CxBRG;
    I2C1CON = 0b1010001000000000;
      //		|||||||||||||||+-- SEN:
      //		||||||||||||||+--- RSEN:
      //		|||||||||||||+---- PEN:
      //		||||||||||||+----- RCEN:
      //		|||||||||||+------ ACKEN:
      //		||||||||||+------- ACKDT:
      //		|||||||||+-------- STREN:  у нас не используется (для ведомого режима)
      //		||||||||+--------- GCEN: у нас не используется (для ведомого режима) адрес общего вызова отключен
      //		|||||||+---------- SMEN: совместимость у порограми SMBus отключена
      //		||||||+----------- DISSLW: контроль скорости нарастания выходного напряжения отключен
      //		|||||+------------ A10M: у нас не используется (для ведомого режима)
      //		||||+------------- IPMIEN: 0 режим отключен
      //		|||+-------------- SCLREL: у нас не используется (для ведомого режима)
      //		||+--------------- I2CSIDL: 1 - остановить модуль в режиме ожидания
      //		|+---------------- не используется
      //		+----------------- I2CEN: модуль I2C включен, выводы сонфигкрированы под порты
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.PEN = 1; // формировать бит стоп
    while (I2C1CONbits.PEN); // ожидание окончания формирования бита стоп
}

/************************************************************
 * Function Prototype : void i2c_idle (void)
 * Description        : ожидание окончания активности
 * Arguments          : None
 * Return Value       : None
 * Remarks            : 
 ***********************************************************/
void i2c_Idle(void) {
    /* Wait until I2C Bus is Inactive */
    while (I2C1CONbits.SEN || I2C1CONbits.RSEN || I2C1CONbits.PEN || I2C1CONbits.RCEN ||
            I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT) {
        continue;
    }
}

/************************************************************
 * Function Prototype : void i2c_stop (void)
 * Description        : формировать бит стоп
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Stop(void) //формировать бит стоп
{
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.PEN = 1; // формировать бит стоп
    while (I2C1CONbits.PEN); // ожидание окончания формирования бита стоп
}//

/************************************************************
 * Function Prototype : void i2c_start (void)
 * Description        : формирования START
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
void i2c_Start(void) 
{
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности    
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN); //ожидание окончания

}

/************************************************************
 * Function Prototype : void i2c_Restart (void)
 * Description        : формирования начала START для записи
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
void i2c_Restart(void) {
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.RSEN = 1;
    while (I2C1CONbits.RSEN); //ожидание окончания
}

/************************************************************
 * Function Prototype : char i2c_Write (char data)
 * Description        : формирования записи байта в устройство
 * Arguments          : 
 * Return Value       : 0-ok 1-error
 * Remarks            : 
 ***********************************************************/
char i2c_Write(unsigned char data) {
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1TRN = data;
    while (I2C1STATbits.TBF); // ожидание окончания передачи
    if (I2C1STATbits.ACKSTAT == 0) {
        return 0; // байт принят
    } else {
        return 1; // Ok
    }
}

/*********************************************************************
Function Prototype  : void i2c_ACK(void)
Description         : Generates I2C bus Acknowledge condition.
Arguments           : None
Return Value        : None
Remarks             : This function generates an I2C bus Acknowledge condition.
 *********************************************************************/
void i2c_ACK(void) {
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN); //ожидать окончания формирования
}

/*********************************************************************************
Function Prototype : void i2c_NACK(void)
Description        : Generates I2C bus Not Acknowledge condition during Master Receive.
Arguments          : None
Return Value       : None
Remarks            : This function generates an I2C bus Not Acknowledge condition.
 **********************************************************************************/
void i2c_NACK(void) {
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN); //ожидать окончания формирования
}

/************************************************************
 * Function Prototype : char i2c_Read(void)
 * Description        : Чтение байта
 * Arguments          : None
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
unsigned char i2c_Read(void) {
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.RCEN = 1; //enable master for 1 byte reception
    while (!I2C1STATbits.RBF); // wait until byte received
    return ( I2C1RCV); // return with read byte
}

/************************************************************
 * Function Prototype : unsigned char i2c_Read_ACK(void)
 * Description        : 
 * Arguments          : 
 * Return Value       : 
 * Remarks            : 
 ***********************************************************/
unsigned char i2c_Read_ACK(void) {
    /*формирования чтения байта из устройства с подтверждением приема */
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.RCEN = 1; //начать прием данных
    Nop();
    while (!I2C1STATbits.RBF); // ожидание загрузки буфера приема
    I2C1CONbits.ACKDT = 0; //установить бит подтвеждения приема
    I2C1CONbits.ACKEN = 1; //начать формировать бит
    while (I2C1CONbits.ACKEN); //ожидать окончания формирования
    return I2C1RCV; //чтение буфера
}

/************************************************************
 * Function Prototype : unsigned char i2c_Read_NACK(void)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
unsigned char i2c_Read_NACK(void) {
    /* формирования чтения байта из устройства с не_подтверждением приема */
    while (I2C1STATbits.TRSTAT); // ожидание окончания активности
    I2C1CONbits.RCEN = 1; //начать прием данных
    Nop();
    while (!I2C1STATbits.RBF); // ожидание загрузки буфера приема
    I2C1CONbits.ACKDT = 1; //установить бит не-подтвеждения приема
    I2C1CONbits.ACKEN = 1; //начать формировать бит
    while (I2C1CONbits.ACKEN); //ожидать окончания формирования
    I2C1CONbits.ACKDT = 0; //Set for NotACk
    return I2C1RCV; //чтение буфера
}

/************************************************************
 * Function Prototype : unsigned char i2c_Open(unsigned char adres)
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/
unsigned char i2c_Open(unsigned char adres) {
    i2c_Start();
    return i2c_Write(adres);
}
/************************************************************
 * Function Prototype :
 * Description        :
 * Arguments          :
 * Return Value       :
 * Remarks            :
 ***********************************************************/


