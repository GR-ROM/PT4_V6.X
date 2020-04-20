/***************************************************************
 * ProgPRM.c
 *
 *
 ***************************************************************/
#include <GenericTypeDefs.h>
#include <string.h>
#include <stdlib.h>
#include "Primitive.h"
#include "Key.h"
#include "EEPR24C16.h"
#include "SCREEN_DRV.h"
#include "UC1601_DRV.h"
/* Fonts */
//extern const FONT_FLASH Calibri_13pixels_0x20_0xFF;
extern const FONT_FLASH Arial_16pix;
extern volatile unsigned char TimeOutSav;

/*��� �������� ����� ���*/
typedef struct{
    UINT16 NumAdr;
    UINT8 NumFls;
    UINT8 NumRepl;
}CodesNum_t;

union {
    UINT8 BufCodes[23];
    struct{
    CodesNum_t CodesNum[5]; 
    UINT8 CodeMayack_ON;
    UINT8 CodeMayack_OFF;
    UINT8 InvLamp;
    }Ust;

} CodesPreset;

/*������ ���� ����������������*/
const XCHAR * SpsPE[8] = {
    (XCHAR *) {
        "�����"}
,
    (XCHAR *) {
        "������ ���"}
,
    (XCHAR *) {
        "�������� ���"}
,
    (XCHAR *) {
        "���="}
,
    (XCHAR *) {
        "����1="}
,
    (XCHAR *) {
        "����2="}
,
    (XCHAR *) {
        "����3="}
,
    (XCHAR *) {
        "����4="}
};
const XCHAR * Yes = "\"����\"     ��";
/*����� ������ ����*/
INT8 NumItem;

enum {
    Exit_Item = 0, /*������� �����*/
    Read_Item, /*������� ������ �� ���*/
    Write_Item, /*������� ������ � ���*/
    Vyz_Item, /*������� �����*/
    Av1_Item, /*������� ������1*/
    Av2_Item, /*������� ������2*/
    Av3_Item, /*������� ������3*/
    Av4_Item /*������� ������4*/
};
/*��������� ��� ������*/
const char * NamePE = "��������������";



/******************************************************************************
 * ������ ����� � "," � ������ �����
 * ��������� �������� ����� '_'
 * ��� ������������ ������ ���������
 *****************************************************************************/
XCHAR StrInp[15]; /*������ �����*/
UINT8 PosInp; /*����� ��������� �������*/

void UpdateInput(char in) {
    if (in != '_') {
        StrInp[PosInp++] = in;
        StrInp[PosInp] = 0;
    } else {
        if (PosInp > 0) PosInp--;
        StrInp[PosInp] = 0; /*��������� ��� � ������ ������ ���� 0*/
    }
    if (PosInp > 15) {
        PosInp = 0;
        //StrInp[0] = 0;
        memset(StrInp, 0x0, 15);
    }
}

/******************************************************
 * ����������� ���,���,���� � ������ ��� ������
 * pSt-����� ������ pSt
 * num-����� ������ ����,�������,�������� (������ 0 � ������ 1-4)
 ******************************************************/
void CodePack(char * pSt, UINT8 num) {
    unsigned char conn[6];
    /*��� �������� ����,�������,��������*/
    strcpy(pSt, SpsPE[num + Vyz_Item]);
    utoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumAdr, 10);
    /*���*/
    strcat(pSt, (char *) &conn);
    /*����������� ","*/
    strcat(pSt, ",");
    itoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumFls, 10);
    /*�������*/
    strcat(pSt, (char *) &conn);
    /*����������� ","*/
    strcat(pSt, ",");
    itoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumRepl, 10);
    /*�������*/
    strcat(pSt, (char *) &conn);
}

/**************************************************
 * void StoryCode(UINT8 Num)
 * ��������� ������
 * 
 **************************************************/
void StoryCode(UINT8 Num) {
    int i, j, k;
    i = strcspn((char *) &StrInp, ",");
    if (i > 0) {
        CodesPreset.Ust.CodesNum[Num].NumAdr = atoi((char *) &StrInp);
    }else return;
    j = strcspn(((char *) &StrInp) + i + 1, ",");
    if (j > 0) {
        CodesPreset.Ust.CodesNum[Num].NumFls = atoi((char *) &StrInp + i + 1);
    } else {
        CodesPreset.Ust.CodesNum[Num].NumFls = 5;
    }
    k = strcspn(((char *) &StrInp) + j + i + 2, ",");
    if (k > 0) {
        CodesPreset.Ust.CodesNum[Num].NumRepl = atoi((char *) &StrInp + j + i + 2);
    } else {
        CodesPreset.Ust.CodesNum[Num].NumRepl = 7;
    }
}

void EditPROG(void) {
    SHORT x, y;
    SHORT txt_width, txt_height;
    unsigned char ch, noinp;
    char str[20]; //
    /*���������� ������ � ���������*/
    SetColor(WHITE); //BLACK
    ClearDevice(); //
    SetColor(BLACK); //WHITE
    //SetFont((void*) &Calibri_13pixels_0x20_0xFF);
    SetFont((void*) &Arial_16pix);
    SetLineThickness(THICK_LINE); //THICK_LINE 3 pixels
    SetLineType(SOLID_LINE); //SOLID_LINE
    //txt_height = GetTextHeight((void*) &Calibri_13pixels_0x20_0xFF); //������ ��������
    txt_height = GetTextHeight((void*) &Arial_16pix); //������ ��������
    //������ ������
    Bevel(4, 0x9, 127, 59, 2);
    //������ ������
    //txt_width = GetTextWidth((XCHAR*) NamePE, (void*) &Calibri_13pixels_0x20_0xFF);
    txt_width = GetTextWidth((XCHAR*) NamePE, (void*) &Arial_16pix);
    /*��������� ���������� ��� ������ �� ������*/
    x = (GetMaxX() - txt_width) >> 1;
    y = 0;
    BarFill(x, y, x + txt_width, y + txt_height); //������� ����� ��� �������
    OutTextXY(x, 0, (XCHAR*) NamePE); //������������ ����
    Update_Screen(); //������� �� ���������
    ReadCodesPreset((char *) &CodesPreset.BufCodes); /*������ ���� �� EEPROM*/
    noinp = 0; /*���� �������� �����*/
    /*������� ������ �����*/
    memset(StrInp, 0x0, 15);
    PosInp = 0;
    NumItem = Read_Item; /*������� ������ �� ���*/
    /*��������� ����*/
    while (1) {
        /*** ������� ����� �� ������****/
        BarFill(10, 15, 120, 55);
        if (NumItem == Exit_Item) {
            OutTextXY(10, 15, (XCHAR*) SpsPE[Exit_Item]);
            OutTextXY(10, 28, (XCHAR*) Yes);
            Update_Screen(); /*������� �� �����*/
            ch = GetKey(); /*����� ��� �� ����������*/
            if (ch == '\n') {
                return;
            }
            if (ch == '<' || ch == '>') {
                noinp = 1;
            }
        }
        if (NumItem == Read_Item) {
            OutTextXY(10, 15, (XCHAR*) SpsPE[Read_Item]);
            OutTextXY(10, 28, (XCHAR*) Yes);
            Update_Screen(); /*������� �� �����*/
            ch = GetKey(); /*����� ��� �� ����������*/
            if (ch == '<' || ch == '>') {
                noinp = 1;
            }
            /*������ �� ���*/
        }
        if (NumItem == Write_Item) {
            OutTextXY(10, 15, (XCHAR*) SpsPE[Write_Item]);
            OutTextXY(10, 28, (XCHAR*) Yes);
            Update_Screen(); /*������� �� �����*/
            ch = GetKey(); /*����� ��� �� ����������*/
            if (ch == '<' || ch == '>') {
                noinp = 1;
            }
            /*���������� � ���*/
        }
        if (NumItem >= Vyz_Item && NumItem <= Av4_Item) {
            /*����������� ������ �����*/
            CodePack((char *) str, (NumItem - Vyz_Item)); /*��������� ���,�������,�������*/
            OutTextXY(10, 15, (char *) &str); /*������� ��������� ������ � �����*/
            OutTextXY(10, 28, "=>");
            OutText((char *) & StrInp);
        }
        Update_Screen(); /*������� �� �����*/
        if (noinp == 0) {
            ch = GetKey(); /*����� ��� �� ����������*/
        }
        noinp = 0;
        /*��������� ������ ����������*/
        if (ch == '<') { /*������� ����*/
            NumItem++;
            if (NumItem > Av4_Item) {
                /*�� �������� �� ������ ���� ����*/
                NumItem = Write_Item; /*������� �� ����� ������ � ���*/
            }
        }
        if (ch == '>') { /*������� �����*/
            NumItem--;
            if (NumItem < Exit_Item) {
                NumItem = Exit_Item; /*�� �������� �� ������ ���� �����*/
            }
        }

        /*�������� �� ���������� ��� ����� ��� ������*/
        if ((ch >= '0' && ch <= '9') || ch == ',' || ch == '_') {
            UpdateInput(ch); /*��������� ������ � ������ �����*/
        }
        if (ch == '\n' && NumItem >= Vyz_Item && NumItem <= Av4_Item) {
            /*��������� ������� ���,�������,�������*/
            StoryCode(NumItem - Vyz_Item);
            SaveCodePreset((char *) &CodesPreset.BufCodes);
            /*�������� ������ �����*/
            memset(StrInp, 0x0, 15);
            PosInp = 0;
        }

    }

}



