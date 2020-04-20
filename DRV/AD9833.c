/*******************************************************
 * AD9833.c
 * 
 * 
 * 
 * 
 *******************************************************/
#include <xc.h>
#include "AD9833.h"



extern  Ust SetParam;

//static UINT16 CONTROL_REGISTER;

static union {
UINT16 REG;
struct
    {
    unsigned    bit0:1;     /* D00 Reserved */
    unsigned    Mode:1;     /* D01 Mode */
    unsigned    bit2:1;     /* D02 Reserved */
    unsigned    DIV2:1;     /* D03 DIV2 */
    unsigned    bit4:1;     /* D04 Reserved */
    unsigned    OPBITEN:1;  /* D05 OPBITEN */
    unsigned    SLEEP12:1;  /* D06 SLEEP12 */
    unsigned    SLEEP1:1;   /* D07 SLEEP1 */
    unsigned    Reset:1;    /* D08 Reset */
    unsigned    bit9:1;     /* D09 Reserved */
    unsigned    PSELECT:1;  /* D10 D10 */
    unsigned    FSELECT:1;  /* D11 D11 */
    unsigned    HLB:1;      /* D12 HIGH/LOW BYTE, D12 */
    unsigned    B28:1;      /* D13 28-BIT/14-BIT WORD, D13 */
    unsigned    bit14:1;    /* D14 Reserved */
    unsigned    bit15:1;    /* D15 Reserved */
    }Control_bits;
}CONTROL_REGISTER;


//-------------------------------
/* AD9833 SEND WORD             */
//-------------------------------
void AD9833_word(UINT16 data)
{/* TEMPLATE FOR WRITE FUNCTIONs */
 SPI_Put (data);    // 16 bits
}


/*-------------------------------
 * WRITE AD9833 REGISTERs        
 * Эта функция используется для   
 * записи значения в упраляющий и 
 * фазовые регистры               
 *-------------------------------*/
void AD9833_write(UINT16 data)
{/* ELEMENTARY WRITE FUNCTION */
 Chip_Select();
 SPI_Put (data);
 ChipUnselect();   
}
//-------------------------------
/* AD9833 SET PHASE *
 * Устанавливаем фазу в в один из двух фазовых регистров
 * Фаза должна быть в градусах: от 0 .. до 360 с точностью в 1 градус
 * Чтобы установить фазу с точностью до 0.1 градус
 * следует поменять значение макроса PHASE_RESOLUTION с 1 на 10 
 * после чего устанавливать фазу*10,
 * тоесть если хотим установить 22.5 градусов следует записать:
 * AD9833_setPhase(WRITE_TO_PHASE0_REG, 225);
------------------------------- */
void AD9833_setPhase(UINT16 REG, unsigned long Phase)
{/* Phase должна быть в градусах: от 0 до 360 */
 UINT16 PHASE = (Phase*4096)/(360*PHASE_RESOLUTION); /* 2п = 360 градусов */

 AD9833_write((PHASE & 0x0FFF) | REG); // WRITE_TO_PHASEx_REG

}

//-------------------------------
/* AD9833 SET FREQVENCE 
 * Формула по расчету выходной частоты:
 * FREG = (Fout*2^28)/Mclk, где Fout - желаемая частота
 * Частота используемого мной тактового генератора равна Mclk = 8.192 МГц,
 * В следующей функции, коэффициент 2237/100 получился из 
 * деления 2^28/12000000 = 22.37
 * К примеру если ваш тактовый генератор будет Mclk = 25.0 МГц
 * то коэффициент в формуле следует заменить на 2^28/25000000 = 1073/100
 * 2^28/8192000=32.768 ==3277/100
-------------------------------*/
void AD9833_setFreq(UINT16 REG, unsigned long Freq)
{/* WRITE 28-BIT FREQVENCE */
 DWORD FREQ = (Freq*32768)/1000; /* 2^28/MCLK = 2237/100 */
 
 
 AD9833_write((UINT16)(FREQ & 0x3FFF) | REG); /* 14 LSBs */
 AD9833_write(((FREQ >> 14) & 0x3FFF) | REG ); /* 14 MSBs */

}
//-------------------------------
/* AD9833, 
 * CHANGE USED FREQVENCY REGISTER
 * В AD9833 имеются 2 частотных регистра. 
 * Пока в одном регистре записана текущая частота,
 * можно загнать во второй регистр следующую частоту 
 * и в нужный момент переключится на нее.
 * Следующая функция как раз и используется для 
 * переключения между этими двумя регистрами
 * при помощи соответстующих макросов  
//-------------------------------*/
void AD9833_usedFreqReg(unsigned char REG)
{/* SELECT ONLY BETWEEN FREQ0 and FREQ1 REGISTERS */
 switch(REG)
 {
  case USE_FREQ1_REG : CONTROL_REGISTER.Control_bits.FSELECT=1; break; // ENABLE USE_FREQ1 select Freq1 as working register
  case USE_FREQ0_REG : CONTROL_REGISTER.Control_bits.FSELECT=0; break; // DISABLE USE_FREQ0 select Freq0 as working register
  default	     : break;
 }

 AD9833_write(CONTROL_REGISTER.REG); // change working register

}

//-------------------------------
/* AD9833, 
 * CHANGE USED PHASE REGISTER 
 * Функция переключения фазовых регистров,
 * аналогична функции переключения между частотными регистрами
//-------------------------------*/
void AD9833_usedPhaseReg(unsigned char REG)
{/* SELECT ONLY BETWEEN PHASE0 and PHASE1 REGISTERS */
 switch(REG)
 {
  case USE_PHASE1_REG : CONTROL_REGISTER.Control_bits.PSELECT=1; break; // ENABLE USE_PHASE1 select Phase1 as working register
  case USE_PHASE0_REG : 
  default	      : CONTROL_REGISTER.Control_bits.PSELECT=0; break; // DISABLE USE_PHASE0 select Phase0 as working register
 }

 AD9833_write(CONTROL_REGISTER.REG); // change working register
 
}

//-------------------------------
/* AD9833 Mode Select 
 * Функция для изменения формы выходного сигнала:
 * синус (SINUS), треугольник (TRIANGLE), меандр (SQUARE)
//-------------------------------*/
void AD9833_mode(unsigned char mode)
{// Start AD9833
 CONTROL_REGISTER.Control_bits.SLEEP12=0; // DISABLE STOP_DAC run DAC
 CONTROL_REGISTER.Control_bits.SLEEP1=0; // DISABLE STOP_MCLK enable Mclk of AD9833
 switch(mode)
 {
//-------------------------------
/* USE AD9833 AS TRIANGLE WAVE GENERATOR
 * 
//-------------------------------*/
  case TRIANGLE : 
		  CONTROL_REGISTER.Control_bits.Mode=1; // BYPASS_SINROM bypass SINROM to obtine SAWTOOTH WAVE
		  CONTROL_REGISTER.Control_bits.OPBITEN=0; // DISCONNECT_DAC connect DAC to output
		  break;
//-------------------------------
/* USE AD9833 AS SQUARE WAVE GENERATOR */
//-------------------------------
  case SQUARE   : 
  	   	  CONTROL_REGISTER.Control_bits.Mode=0; // BYPASS_SINROM connect SINROM
		  CONTROL_REGISTER.Control_bits.OPBITEN=1; // DISCONNECT_DAC disconnect DAC from output
  	   	  break;
//-------------------------------
/* USE AD9833 AS SIN WAVE GENERATOR */
//-------------------------------
  case SINUS	: 
  default 	: 
		  CONTROL_REGISTER.Control_bits.Mode=0; // BYPASS_SINROM connect SINROM to obtine SIN WAVE
		  CONTROL_REGISTER.Control_bits.OPBITEN=0; // DISCONNECT_DAC connect DAC to output
		  break;
 }
 AD9833_write(CONTROL_REGISTER.REG); // Send selected MODE to AD9833
}

//-------------------------------
/* AD9833, USED AS SIMPLE DAC */
//-------------------------------
void AD9833_DAC(unsigned long millivolts)
{/* USE THIS FUNCTION, ONLY AFTER SET - 
	DCLevel MODE */
 unsigned long volt = (millivolts*180)/VSUPPLY;
 CONTROL_REGISTER.Control_bits.Reset=1; // Reset all registers to 0 - midscale
 AD9833_write(CONTROL_REGISTER.REG);
 // NOP();
 AD9833_setFreq(WRITE_TO_FREQ0_REG, 0); /* Set 0.0 Hz */
 AD9833_setPhase(WRITE_TO_PHASE0_REG, (volt<90)? volt + 270 : volt - 90);
 CONTROL_REGISTER.Control_bits.Reset=0;  // Activate AD9833, as simple DAC
 AD9833_mode(TRIANGLE);
}

//-------------------------------
/* AD9833 - MCLK and DAC power supply */
//-------------------------------
void AD9833_power(unsigned char mode)
{
 switch(mode)
 {
  case POWER_OFF :
  	   			  CONTROL_REGISTER.Control_bits.SLEEP12=1; // STOP_DAC DAC power supply down
 				  CONTROL_REGISTER.Control_bits.SLEEP1=1; // STOP_MCLK stop AD9833 MCLK clock
				  break;
  case POWER_ON  :
  	   			  CONTROL_REGISTER.Control_bits.SLEEP12=0; // STOP_DAC DAC power supply up
 				  CONTROL_REGISTER.Control_bits.SLEEP1=0; // STOP_MCLK start AD9833 MCLK clock
				  break;
 }
 AD9833_write(CONTROL_REGISTER.REG); // AD9833 power up/down
}
//-------------------------------
/* AD9833 initialization */
//-------------------------------
void AD9833_init(unsigned char mode, Ust SetParam)
{
 SPI_Init();
 CONTROL_REGISTER.REG=0;
 CONTROL_REGISTER.Control_bits.Reset=1;
 CONTROL_REGISTER.Control_bits.DIV2=1;  /* USE SINUS MODE BY DEFAULT, USE FREQ0 & PHASE0 REGISTERS */
 AD9833_write(CONTROL_REGISTER.REG);
 //Nop();
 CONTROL_REGISTER.Control_bits.B28=1;
 AD9833_write(CONTROL_REGISTER.REG); /* RESET AD9833, USE 28-BIT PACKEDs, and NOT DIVIDE SQUARE WAVE */
 //Nop();
 AD9833_setFreq(WRITE_TO_FREQ0_REG, (unsigned long) SetParam.SetDat.SetFreq0); /* Hz */
 //AD9833_setFreq(WRITE_TO_FREQ0_REG, Freq);
 AD9833_setFreq(WRITE_TO_FREQ1_REG, (unsigned long) SetParam.SetDat.SetFreq1); /* Hz */
 //AD9833_setFreq(WRITE_TO_FREQ1_REG, Freq); /* Hz */
 AD9833_setPhase(WRITE_TO_PHASE0_REG, (unsigned long) SetParam.SetDat.SetPhase0);   /* */
 //AD9833_setPhase(WRITE_TO_PHASE0_REG, 180); /* SHIFT WITH 270 DEGREEs */
 AD9833_setPhase(WRITE_TO_PHASE1_REG, (unsigned long) SetParam.SetDat.SetPhase1);   /* */
 //AD9833_setPhase(WRITE_TO_PHASE1_REG, 0); /* SHIFT WITH 180 DEGREEs */
 CONTROL_REGISTER.Control_bits.Reset=0;

 AD9833_mode(mode);
 //Nop();
 //AD9833_write(0x0000);
}

UINT16  GET_STATAD9833(void)
{
    return CONTROL_REGISTER.REG;
}


