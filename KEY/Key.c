/************************************************************
 * Key.c
 * 
 * 
 * 
 ************************************************************/

#include <xc.h>
#include <GenericTypeDefs.h>
#include "Key.h"

#define     InKey       PORTE
#define     LinKey      LATE
#define     TrisKey     TRISE
#define     PortKey     LATE

#define RouInp()    (~InKey & 0x000f) //Берём состояние сканируемой линии
#define Mask_FN     0b1111111111111101 /*Маска кнопки Fn*/

int KeyUp(void);
int ScanCod(UINT8 ch);

const unsigned char TabKey[] = {//Без нажатия меню
    '\n', 'M', '0', ',',
    '_', '7', '8', '9',
    '<', '4', '5', '6',
    '>', '1', '2', '3',
    //С нажатием меню
    'p', 'm', 'n', 'o',
    'l', 'i', 'j', 'k',
    'h', 'e', 'f', 'g',
    'b', 'a', 'b', 'c'
};

enum {
    Lin0 = 0,
    Lin1,
    Lin2,
    Lin3
};

volatile UINT8 LineKey; /*Счётчик сканирования*/
volatile UINT16 TimKey;
UINT8 Key;

volatile MAP16_VAL MapRou, MapPrev, MapKey;

volatile
struct {
    unsigned Prezent : 1;
    unsigned Pressed : 1;
    unsigned KeyFn  : 1;
    unsigned KeyRdy : 1;
    unsigned KeyRpt : 1;
} KeyFlag;

/************************************************************
 * Инициализация
 * 
 ************************************************************/
void Init_Key(void) {
    LineKey = Lin0;
    TrisKey = 0b11101111;
    LinKey = 0b00001111;
    ODCE = 0x00;
    KeyFlag.KeyFn=0;
    KeyFlag.KeyRdy=0;
    KeyFlag.KeyRpt=0;
    KeyFlag.Pressed=0;
    KeyFlag.Prezent=0;
    MapPrev.val=0;
}

/************************************************************
 * Scan_Key(void)
 * Сканирование клавиатуры
 ************************************************************/
void Scan_Key(void) {
    volatile UINT16 in;
    int CodKey;
    in = RouInp();

    switch (LineKey) {
        case Lin0:
        {
            MapRou.tetr.L0 = in;
            LineKey++;
            PortKey=TrisKey = 0b11011111;
            break;
        }
        case Lin1:
        {
            MapRou.tetr.L1 = in;
            LineKey++;
            PortKey=TrisKey = 0b10111111;
            break;
        }
        case Lin2:
        {
            MapRou.tetr.L2 = in;
            LineKey++;
            PortKey=TrisKey = 0b01111111;
            break;
        }
        case Lin3:
        {
            MapRou.tetr.L3 = in;
            LineKey = Lin0;
            PortKey=TrisKey = 0b11101111;
            break;
        }
        default:
        {
            LineKey = Lin0;
            PortKey=TrisKey = 0b11101111;
            break;
        }
    }
    if (LineKey == Lin0) {
        if (MapRou.val != 0) {
            KeyFlag.Prezent = 1;
        }
    }
    if (KeyFlag.Pressed != 1) {
        if (KeyFlag.Prezent) {
            if (MapPrev.val == MapRou.val) {
                TimKey++;
                if (TimKey == 100) {
                    if (MapRou.val & Mask_FN) {
                        KeyFlag.Pressed = 1;
                        MapKey.val = MapRou.val;
                        
                        CodKey=KeyUp();                //Готовим скан код
                        if(CodKey>=0){
                            KeyFlag.KeyRdy=1;
                            Key=TabKey[CodKey];
                        }
                        
                    } else {
                        TimKey = 0;
                    }
                }
            } else {
                KeyFlag.Pressed = 0;
                KeyFlag.Prezent = 0;
                MapKey.val=0;
                TimKey = 0;
            }
        }
    }
    MapPrev.val = MapRou.val;
}

/***********************************************************
 * UINT8 KeyUp(void)
 * Возвращает скан код клавиши
 ***********************************************************/

int KeyUp(void) {
    int   c;
    if(MapKey.val & (~Mask_FN)){
        KeyFlag.KeyFn=1;    //Нажата кнопка Fn
    }else{
        KeyFlag.KeyFn=0;    //Кнопка Fn не нажата
    }
    MapKey.val&=Mask_FN;    //Замаскировать Fn
    if(MapKey.tetr.L0){
        c=ScanCod(MapKey.tetr.L0);
        if(c<0)return -1;
        else{
            if(KeyFlag.KeyFn==1){
                return (c+16);
            }
            return c;
        }
    }
    if(MapKey.tetr.L1){
        c=ScanCod(MapKey.tetr.L1);
        if(c<0)return -1;
        else{
            if(KeyFlag.KeyFn==1){
                return ((c+4)+16);
            }
            return (c+4);
        }
    }
    if(MapKey.tetr.L2){
        c=ScanCod(MapKey.tetr.L2);
        if(c<0)return -1;
        else{
            if(KeyFlag.KeyFn==1){
                return ((c+8)+16);
            }
            return (c+8);
        }
    }
    if(MapKey.tetr.L3){
        c=ScanCod(MapKey.tetr.L3);
        if(c<0)return -1;
        else{
            if(KeyFlag.KeyFn==1){
                return ((c+12)+16);
            }
            return (c+12);
        }
    }
    return 0;
}

/*************************************************************************
 * Возвращает флаг готовности кнопки
 *
 ************************************************************************/
unsigned int kbhit(void) {

    return KeyFlag.KeyRdy;
}
/************************************************************
 * Возвращает код нажатой кнопки
 * 
 ************************************************************/
unsigned char getch(void){
    KeyFlag.KeyRdy=0;
    KeyFlag.Pressed=0;
    KeyFlag.Prezent=0;
    return Key;
}
unsigned char GetKey(void){
    while(!kbhit()) continue;
    return getch();
}
void KeyClear(void){
    KeyFlag.KeyRdy=0;
    KeyFlag.Pressed=0;
    KeyFlag.Prezent=0;
}
void KeyNul(void){
    Key=0;
}
/************************************************************
 * int ScanCod(UINT8 ch)
 * 
 * 
 * 
 ************************************************************/
int ScanCod(UINT8 ch){
    if(ch==1) return 0;
    if(ch==2) return 1;
    if(ch==4) return 2;
    if(ch==8) return 3;
    return -1;
}
/************************************************************
 * Ожидает отпускание клавиши
 ************************************************************/
void UnpressedKey(void){
    while(MapRou.val != 0) continue;
}

