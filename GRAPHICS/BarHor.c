/***********************************************************
 * BarHor.c
 ***********************************************************/

#include "SCREEN_DRV.h"
#include "Primitive.h"

/********************************************************************
 * Функция: void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * Аргументы: left,top,right,bottom координаты углов
 *            vol Ширина в %
 * 
 ********************************************************************/
void ProgressBarHor(SHORT left, SHORT top, SHORT right, SHORT bottom,
        WORD vol) {
    BYTE temp_color,
            temp_LineType,
            temp_LineThickness,
            x;
    x = (right - left) * vol / 100;
    temp_color = GetColor();
    temp_LineThickness = _lineThickness;
    temp_LineType = _lineType;
    SetColor(BLACK);
    SetLineThickness(THICK_LINE);
    SetLineType(SOLID_LINE);
    Bevel(left, top, right, bottom, 3);
    SetColor(WHITE);
    Bar(left, top, right, bottom);
    SetColor(BLACK);
    Bar(left, top, x, bottom);
    SetColor(temp_color);
    SetLineThickness(temp_LineThickness);
    SetLineType(temp_LineType);
}

/********************************************************************
 * Функция: void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol)
 * Аргументы: left,top,right,bottom координаты углов
 *            vol Высота в %
 * 
 ********************************************************************/
void ProgressBarVer(SHORT left, SHORT top, SHORT right, SHORT bottom, WORD vol) {
    BYTE temp_color,
            temp_LineType,
            temp_LineThickness,
            x;
    temp_color = GetColor();
    temp_LineThickness = _lineThickness;
    temp_LineType = _lineType;
    SetColor(BLACK);
    SetLineThickness(THICK_LINE);
    SetLineType(SOLID_LINE);
    /****************************/
    Bevel(left, top, right, bottom, 3);
    SetColor(WHITE);
    Bar(left, top, right, bottom);
    /*Высота BAR*/
    x = (bottom - top) * vol / 100;
    SetColor(BLACK);
    Bar(left,top+(bottom-x),right, bottom);
    SetColor(temp_color);
    SetLineThickness(temp_LineThickness);
    SetLineType(temp_LineType);
}
