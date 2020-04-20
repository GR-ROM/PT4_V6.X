/* 
 * File:   mytype.h
 * Author: Grinev
 *
 * Created on 21 ќкт€брь 2015 г., 15:49
 */

#ifndef MYTYPE_H
#define	MYTYPE_H

#include <GenericTypeDefs.h>

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

#if !defined(__PACKED)
#define __PACKED
#endif

typedef union tagUst {
    unsigned char SetUst[10];

    struct {
        unsigned int SetFreq0,
        SetFreq1,
        SetPhase0,
        SetPhase1;
    } SetDat;
} Ust;

/*******************************************
 * ”становки дл€ частот и миганий
 *******************************************/
typedef union {
    unsigned char Buf[6];

    struct {
        unsigned int PF0;
        unsigned int PF1;
        unsigned int BRLED;
    } ParamWord;
} param;

/**************************************************************
 * ќпределение типа данных
 * MenuPar
 *
 **************************************************************/
typedef
struct {
    void * p_font;
    const char * Name_Menu;
    const char * Spis[5];
    unsigned int Num_Sp;
    unsigned int Num_Item;
} MenuPar;

/*************************************************************
 * ќпределение дл€ передачи кода
 *************************************************************/
typedef
union {
    UINT8 BufP[4];

    struct {
        UINT16 Cod;
        UINT8 Com;
        UINT8 CRC;
    } Code_p;
} Codes_t;
#endif	/* MYTYPE_H */

