/* 
 * File:   PT4_V6.c
 * Author: Grinev
 *
 * Created on 16 ������� 2016 �., 14:10
 */

//#include <p24fxxxx.h>
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <GenericTypeDefs.h>
#include "Config.h"
#include "HardwareProfile.h"
#include "EEPR24C16.h"
#include "CRC8.h"
#include "Timer.h"
#include "Key.h"
#include "UC1601_DRV.h"
#include "GraphicsConfig.h"
#include "Primitive.h"
#include "BarHor.h"
#include "mytype.h"
#include "ProgPRM.h"
#include "PWM.h"
#include "Menu.h"
#include "Transmit.h"
#include "CRC8.h"


//#pragma jis //����� �� ���������� �� �������
/*
 * 
 */

/*****************************************
 * ���� ���������
 * ����������:
 * 0- ����������� �������
 * 1- ����� ������
 * 2- ������ �� ���������
 *****************************************/
SHORT MnuUstan(void);
/********************************************
 * ���������� ���������� �������
 ********************************************/
void LightSCRN(void);
/********************************************************
 * ����� ������
 ********************************************************/
void SelFreq(void);
/*************************************************
 * ��������� ������ �����
 * � ������������� ��������
 *************************************************/
void Init_PRD(XCHAR *pStr);

///////////////////////////////// FONTS ///////////////////////////////////////
//extern const FONT_FLASH Calibri_13pixels_0x20_0xFF;
extern const FONT_FLASH Arial_16pix;
//extern const FONT_FLASH Digit_22pix;
extern const FONT_FLASH Arial_23pix_20_3F;
extern const FONT_FLASH Arial_Black_18pix;
/***Predefine Func*******/


XCHAR str_inp[12]; //������ �����
UINT8 str_pos; //������� �����
INT8 Light; //���������� ��������

param SetParm;

int main(void) {
    //    BYTE v;
    SHORT com;
    SHORT ch;
    str_pos = 0;
    str_inp[0] = 0;
    CLKDIV = 0;
    CLKDIVbits.RCDIV = 1;
    AD1PCFG = 0xffff; // Setup PortB IOs as digital
    InitGraph(); // ����� �������
    LATDbits.LATD1 = 0; //��������� ��������� ��������
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD11 = 0;
    LATDbits.LATD11 = 0;    //���������
    TRISCbits.TRISC13=0;
    LATCbits.LATC13=0;
    ReadUst(SetParm.Buf, sizeof (param)); //������ ���������
    SetPerF0(SetParm.ParamWord.PF0); //���������� ������� 0
    SetPerF1(SetParm.ParamWord.PF1); //���������� ������� 1
    Light = SetParm.ParamWord.BRLED;
    FreqOut(1);
    InitPWM();
    Init_Key();
    Timer_Init();

    
    SetColor(WHITE); //BLACK
    ClearDevice();
    SetLineType(SOLID_LINE); //SOLID_LINE
    SetColor(BLACK);
    SetLineThickness(THICK_LINE); //THICK_LINE 3 pixels

   


    
    Nop();
    while (1) {
        Nop();
        //width=CRC8(Blk,9);
        SetColor(WHITE);
        ClearDevice();
        SetColor(BLACK);
        SetFont((void*) &Arial_Black_18pix);
        OutTextXY(20, 0, "����� ����");
        SetFont((void*) & Arial_23pix_20_3F);

        OutTextXY(5, 22, ">");
        OutText((char *) &str_inp);
        Update_Screen();
        //        DelayMs(500);
        com = GetKey();
        //SetFont((void*) &Calibri_13pixels_0x20_0xFF);
        SetFont((void*) &Arial_16pix);
        if (com == 'b') {
            /*�������������� �����*/
            EditPROG();
        }
        if (((com >= '0' && com <= '9') || com == ',' || com == '_')) {
            /* Digit */
            if (com != '_') {
                str_inp[str_pos++] = com;
                str_inp[str_pos] = 0;
            } else {
                if (str_pos > 0) {
                    str_pos--;
                    str_inp[str_pos] = 0;
                }
            }
            if (str_pos >= 10) {
                str_pos = 0;
                str_inp[str_pos] = 0;
            }
            com = 0;
        }
        if (com == '\n') {
            com = 0;
            /*���������� � ��������*/
            /*�������� ����*/
            Init_PRD((XCHAR *) & str_inp);
            str_pos = 0;
            str_inp[str_pos] = 0;
        }
        if (com == 'a') {
            ch = MnuUstan();
            if (ch == 0) {
                /*�������*/
                LightSCRN();

            }
            if (ch == 1) {
                /*�������*/
                SelFreq();
            }
            if (ch == 2) {
                /*�����*/
            }
        }
    }
    return (0);
}

/*****************************************
 * ���� ���������
 * ����������:
 * 0- ����������� �������
 * 1- ����� ������
 * 2- ������ �� ���������
 *****************************************/
SHORT MnuUstan(void) {
    MenuPar MNU;
    ///MNU.p_font = (void *) &Calibri_13pixels_0x20_0xFF;
    MNU.p_font = (void *) &Arial_16pix;
    MNU.Name_Menu = "���������";
    MNU.Num_Item = 0;
    MNU.Num_Sp = 3;
    MNU.Spis[0] = "�������";
    MNU.Spis[1] = "�������";
    MNU.Spis[2] = "�����";
    return MenuItem(MNU);
}

/********************************************
 * ���������� ���������� �������
 ********************************************/
void LightSCRN(void) {
    SHORT ls;
    SetFont((void*) &Arial_16pix);
    //SetFont((void*) &Calibri_13pixels_0x20_0xFF);
    while (1) {

        SetColor(WHITE);
        ClearDevice();

        ls = (((UINT16) Light * 100) / 16);
        SetColor(BLACK);
        OutTextXY(35, 15, "�����������");
        OutTextXY(35, 28, "�������");

        ProgressBarVer(5, 5, 25, 56, ls);
        Update_Screen();
        ls = GetKey();
        if (ls == '>') Light++;
        if (ls == '<') Light--;
        if (Light > 16) Light = 16;
        if (Light < 0) Light = 0;
        if (ls == '\n') {
            SetParm.ParamWord.BRLED = Light;
            SaveUst(SetParm.Buf, sizeof (param));
            return;
        }
    }
}

/********************************************************
 * ����� ������
 ********************************************************/
void SelFreq(void) {
    unsigned char inkey;
    MenuPar MNU;
    inkey = 0;
    ReadUst(SetParm.Buf, sizeof (param)); //������ ���������
    //MNU.p_font = (void *) &Calibri_13pixels_0x20_0xFF;
    MNU.p_font = (void *) &Arial_16pix;
    MNU.Name_Menu = "����� ������";
    MNU.Spis[0] = "1 719/769";
    MNU.Spis[1] = "2 875/925";
    MNU.Spis[2] = "3 725/775";
    MNU.Num_Item = 0;
    MNU.Num_Sp = 3;
    inkey = MenuItem(MNU);


    if (inkey == 0) {
        SetParm.ParamWord.PF0 = 7697;
        SetParm.ParamWord.PF1 = 7197;
    }
    if (inkey == 1) {
        SetParm.ParamWord.PF0 = 9250;
        SetParm.ParamWord.PF1 = 8750;
    }
    if (inkey == 2) {
        SetParm.ParamWord.PF0 = 7750;
        SetParm.ParamWord.PF1 = 7250;
    }
    //SetParm.ParamWord.BRLED=8;


    SaveUst(SetParm.Buf, sizeof (param));
    SetPerF0(SetParm.ParamWord.PF0); //���������� ������� 0
    SetPerF1(SetParm.ParamWord.PF1); //���������� ������� 1
    FreqOut(1); //1
    //ReadUst(SetParm.Buf, sizeof (param)); //������ ���������
}

/*************************************************
 * ��������� ������ �����
 * � ������������� ��������
 *************************************************/
void Init_PRD(XCHAR *pStr) {
    int i, j, k;
    Codes_t BufPrd;

    SetColor(WHITE);
    ClearDevice();
    SetColor(BLACK);
    SetFont((void*) &Arial_Black_18pix);
    OutTextXY(26, 0, "��������");
    SetFont((void*) & Arial_23pix_20_3F);
    OutTextXY(5, 22, (char *) &str_inp);
    Update_Screen();

    BufPrd.Code_p.Cod = 0;
    BufPrd.Code_p.Com = 0;
    i = strcspn(pStr, ",");
    if (i > 0) {
        BufPrd.Code_p.Cod = (UINT16) atoi(pStr);
    }
    j = strcspn(pStr + i + 1, ",");
    if (j > 0) {
        BufPrd.Code_p.Com = (UINT8) atoi(pStr + i + 1);
    }
    k = CRC8((UINT8 *) & BufPrd.BufP, 3); //����������� �����
    BufPrd.Code_p.CRC = k;
    Transmit(BufPrd);
    KeyClear();
}