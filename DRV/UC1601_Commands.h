/* 
 * File:   UC1601_Commands.h
 * Author: Grinev
 *
 * Created on 13 ������ 2015 �., 17:06
 */

#ifndef UC1601_COMMANDS_H
#define	UC1601_COMMANDS_H

#define BiasRatio   0x03    //����������� ����� VLCD � VD 11:9
#define PM          125     //VBIAS ������������

     
#define UC1601S         0x70    //����� UC1601S
#define WriteComand     0x00    //������ ������
#define WriteData       0x02    //������ ������
#define ReadData        0x03    //������ ������

//�������
#define SystemReset     0xE2    //��������� �����
#define SetLCDBiasRatio 0xEB    //���������� ��������� BIAS ��� LCD
#define SetVbias        0x81    //���������� VBIAS ������������
#define SetLCDMapping   0xC6    //����������� X Y ��������� (���� 1-2)
#define DisplayEnable   0xAF    //�������� ������� (


#endif	/* UC1601_COMMANDS_H */

