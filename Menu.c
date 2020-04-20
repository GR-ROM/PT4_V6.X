/*****************************************************************
 * Menu.c
 * 
 * 
 * 
 *****************************************************************/

#include <GenericTypeDefs.h>
#include "GraphicsConfig.h"
#include "UC1601_DRV.h"
#include "mytype.h"
#include "Primitive.h"
#include "BarHor.h"
#include "Key.h"



SHORT txt_width, txt_height;

SHORT MenuItem(MenuPar mnu) {
    SHORT x, y;
    UINT8 i;
    unsigned char ch;
    INT8 c;
    ch = 0;
    SetFont(mnu.p_font);
    while (ch != '\n') {
        SetColor(WHITE); //�����
        ClearDevice(); //������ �����
        SetColor(BLACK);
        SetLineThickness(THICK_LINE); //THICK_LINE 3 pixels
        SetLineType(SOLID_LINE); //SOLID_LINE

        txt_height = GetTextHeight(mnu.p_font); //������ ��������
        Bevel(4, 0x9, 127, 59, 2); //������ ������
        txt_width = GetTextWidth((XCHAR*)mnu.Name_Menu, mnu.p_font); //������ ������
        x = (GetMaxX() - txt_width) >> 1;
        y = 0;
        BarFill(x, y, x + txt_width, y + txt_height); //������� ����� ��� �������
        OutTextXY(x, 0, (XCHAR*)mnu.Name_Menu); //������������ ����
        /*��������� ������ ����*/
        for (i = 0; i < mnu.Num_Sp; i++) {
            y += txt_height; //����� ����� ������ ����
            txt_width = GetTextWidth((XCHAR*)mnu.Spis[i], mnu.p_font); //������ ������
            OutTextXY(8, y, (XCHAR*)mnu.Spis[i]);
            /*���� ��� �������� ������ �� �����������*/
            if (i == mnu.Num_Item) {
                BarXor(8, y, txt_width + 10, y + txt_height);
            }
        }
        Update_Screen(); /*������� �� �����*/
        c = mnu.Num_Item;
        //while (!kbhit()) continue; /*�������� ������� ������*/
        //ch = getch(); /*�������� ��� ������*/
        ch=GetKey();
        if (ch == '<') c++;
        if (ch == '>') c--;
        if (c >(INT8) mnu.Num_Sp-1) c = 0;
        if (c < 0) c = mnu.Num_Sp-1;
        mnu.Num_Item = c;
    }
    return (SHORT) c;
}

