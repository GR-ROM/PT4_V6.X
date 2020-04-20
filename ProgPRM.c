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

/*Для хранения кодов ПРМ*/
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

/*Строки меню программирования*/
const XCHAR * SpsPE[8] = {
    (XCHAR *) {
        "Выход"}
,
    (XCHAR *) {
        "Читать ПРМ"}
,
    (XCHAR *) {
        "Записать ПРМ"}
,
    (XCHAR *) {
        "Выз="}
,
    (XCHAR *) {
        "Авар1="}
,
    (XCHAR *) {
        "Авар2="}
,
    (XCHAR *) {
        "Авар3="}
,
    (XCHAR *) {
        "Авар4="}
};
const XCHAR * Yes = "\"Ввод\"     ДА";
/*Номер строки меню*/
INT8 NumItem;

enum {
    Exit_Item = 0, /*Позиция выйти*/
    Read_Item, /*Позиция чтения из ПРМ*/
    Write_Item, /*Позиция запись в ПРМ*/
    Vyz_Item, /*Позиция ВЫЗОВ*/
    Av1_Item, /*Позиция АВАРИЯ1*/
    Av2_Item, /*Позиция АВАРИЯ2*/
    Av3_Item, /*Позиция АВАРИЯ3*/
    Av4_Item /*Позиция АВАРИЯ4*/
};
/*Заголовок для вывода*/
const char * NamePE = "Редактирование";



/******************************************************************************
 * Вводит цифры и "," в строку ввода
 * коррекция клавишей забой '_'
 * при переполнении строка очищается
 *****************************************************************************/
XCHAR StrInp[15]; /*Строка ввода*/
UINT8 PosInp; /*Номер вводимого символа*/

void UpdateInput(char in) {
    if (in != '_') {
        StrInp[PosInp++] = in;
        StrInp[PosInp] = 0;
    } else {
        if (PosInp > 0) PosInp--;
        StrInp[PosInp] = 0; /*Последний код в строке должен быть 0*/
    }
    if (PosInp > 15) {
        PosInp = 0;
        //StrInp[0] = 0;
        memset(StrInp, 0x0, 15);
    }
}

/******************************************************
 * Упаковывает КОД,МИГ,ПОВТ в строку для вывода
 * pSt-адрес строки pSt
 * num-Номер строки КОДА,МИГАНИЯ,ПОВТОРОВ (Вызова 0 и Аварий 1-4)
 ******************************************************/
void CodePack(char * pSt, UINT8 num) {
    unsigned char conn[6];
    /*Имя текущего КОДА,МИГАНИЯ,ПОВТОРОВ*/
    strcpy(pSt, SpsPE[num + Vyz_Item]);
    utoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumAdr, 10);
    /*КОД*/
    strcat(pSt, (char *) &conn);
    /*Разделитель ","*/
    strcat(pSt, ",");
    itoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumFls, 10);
    /*МИГАНИЯ*/
    strcat(pSt, (char *) &conn);
    /*Разделитель ","*/
    strcat(pSt, ",");
    itoa((char *) &conn, CodesPreset.Ust.CodesNum[num].NumRepl, 10);
    /*ПОВТОРЫ*/
    strcat(pSt, (char *) &conn);
}

/**************************************************
 * void StoryCode(UINT8 Num)
 * Разбираем строку
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
    /*Отрисовать бордер и заголовок*/
    SetColor(WHITE); //BLACK
    ClearDevice(); //
    SetColor(BLACK); //WHITE
    //SetFont((void*) &Calibri_13pixels_0x20_0xFF);
    SetFont((void*) &Arial_16pix);
    SetLineThickness(THICK_LINE); //THICK_LINE 3 pixels
    SetLineType(SOLID_LINE); //SOLID_LINE
    //txt_height = GetTextHeight((void*) &Calibri_13pixels_0x20_0xFF); //Высота символов
    txt_height = GetTextHeight((void*) &Arial_16pix); //Высота символов
    //Рисуем бордер
    Bevel(4, 0x9, 127, 59, 2);
    //Ширина текста
    //txt_width = GetTextWidth((XCHAR*) NamePE, (void*) &Calibri_13pixels_0x20_0xFF);
    txt_width = GetTextWidth((XCHAR*) NamePE, (void*) &Arial_16pix);
    /*Вычислить координату для вывода по центру*/
    x = (GetMaxX() - txt_width) >> 1;
    y = 0;
    BarFill(x, y, x + txt_width, y + txt_height); //Чистить место для надписи
    OutTextXY(x, 0, (XCHAR*) NamePE); //Наименование меню
    Update_Screen(); //Вывести на индикацию
    ReadCodesPreset((char *) &CodesPreset.BufCodes); /*Читаем коды из EEPROM*/
    noinp = 0; /*флаг пропуска ввода*/
    /*Очистка буфера ввода*/
    memset(StrInp, 0x0, 15);
    PosInp = 0;
    NumItem = Read_Item; /*Позиция чтения из ПРМ*/
    /*Зациклить меню*/
    while (1) {
        /*** очистка места на экране****/
        BarFill(10, 15, 120, 55);
        if (NumItem == Exit_Item) {
            OutTextXY(10, 15, (XCHAR*) SpsPE[Exit_Item]);
            OutTextXY(10, 28, (XCHAR*) Yes);
            Update_Screen(); /*Вывести на экран*/
            ch = GetKey(); /*взять код от клавиатуры*/
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
            Update_Screen(); /*Вывести на экран*/
            ch = GetKey(); /*взять код от клавиатуры*/
            if (ch == '<' || ch == '>') {
                noinp = 1;
            }
            /*Читаем из ПРМ*/
        }
        if (NumItem == Write_Item) {
            OutTextXY(10, 15, (XCHAR*) SpsPE[Write_Item]);
            OutTextXY(10, 28, (XCHAR*) Yes);
            Update_Screen(); /*Вывести на экран*/
            ch = GetKey(); /*взять код от клавиатуры*/
            if (ch == '<' || ch == '>') {
                noinp = 1;
            }
            /*Записываем в ПРМ*/
        }
        if (NumItem >= Vyz_Item && NumItem <= Av4_Item) {
            /*Редактируем строку ввода*/
            CodePack((char *) str, (NumItem - Vyz_Item)); /*Очередные КОД,МИГАНИЯ,ПОВТОРЫ*/
            OutTextXY(10, 15, (char *) &str); /*Выводим очередную строку с кодом*/
            OutTextXY(10, 28, "=>");
            OutText((char *) & StrInp);
        }
        Update_Screen(); /*Вывести на экран*/
        if (noinp == 0) {
            ch = GetKey(); /*взять код от клавиатуры*/
        }
        noinp = 0;
        /*Обработка кнопок управления*/
        if (ch == '<') { /*Клавиша вниз*/
            NumItem++;
            if (NumItem > Av4_Item) {
                /*Не выходить за пункты меню вниз*/
                NumItem = Write_Item; /*Перейти на пункт запись в ПРМ*/
            }
        }
        if (ch == '>') { /*Клавиша вверх*/
            NumItem--;
            if (NumItem < Exit_Item) {
                NumItem = Exit_Item; /*Не выходить за пункты меню вверх*/
            }
        }

        /*Проверка на допустимый код ввода для строки*/
        if ((ch >= '0' && ch <= '9') || ch == ',' || ch == '_') {
            UpdateInput(ch); /*Очередной символ в строку ввода*/
        }
        if (ch == '\n' && NumItem >= Vyz_Item && NumItem <= Av4_Item) {
            /*Сохраняем введёный КОД,МИГАНИЯ,ПОВТОРЫ*/
            StoryCode(NumItem - Vyz_Item);
            SaveCodePreset((char *) &CodesPreset.BufCodes);
            /*Обнуляем строку ввода*/
            memset(StrInp, 0x0, 15);
            PosInp = 0;
        }

    }

}



