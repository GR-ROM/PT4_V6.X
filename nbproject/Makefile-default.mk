#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=DRV/i2c_DRV.c DRV/UC1601_DRV.c GRAPHICS/BarHor.c GRAPHICS/Primitive.c GRAPHICS/SCREEN_DRV.c KEY/Key.c CRC8.c PT4_V6.c Timer.c Calibri_13pixels.c Menu.c EEPR24C16.c ProgPRM.c Arial_23pix_20_3F.c PWM.c Transmit.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/DRV/i2c_DRV.o ${OBJECTDIR}/DRV/UC1601_DRV.o ${OBJECTDIR}/GRAPHICS/BarHor.o ${OBJECTDIR}/GRAPHICS/Primitive.o ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o ${OBJECTDIR}/KEY/Key.o ${OBJECTDIR}/CRC8.o ${OBJECTDIR}/PT4_V6.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/Calibri_13pixels.o ${OBJECTDIR}/Menu.o ${OBJECTDIR}/EEPR24C16.o ${OBJECTDIR}/ProgPRM.o ${OBJECTDIR}/Arial_23pix_20_3F.o ${OBJECTDIR}/PWM.o ${OBJECTDIR}/Transmit.o
POSSIBLE_DEPFILES=${OBJECTDIR}/DRV/i2c_DRV.o.d ${OBJECTDIR}/DRV/UC1601_DRV.o.d ${OBJECTDIR}/GRAPHICS/BarHor.o.d ${OBJECTDIR}/GRAPHICS/Primitive.o.d ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d ${OBJECTDIR}/KEY/Key.o.d ${OBJECTDIR}/CRC8.o.d ${OBJECTDIR}/PT4_V6.o.d ${OBJECTDIR}/Timer.o.d ${OBJECTDIR}/Calibri_13pixels.o.d ${OBJECTDIR}/Menu.o.d ${OBJECTDIR}/EEPR24C16.o.d ${OBJECTDIR}/ProgPRM.o.d ${OBJECTDIR}/Arial_23pix_20_3F.o.d ${OBJECTDIR}/PWM.o.d ${OBJECTDIR}/Transmit.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/DRV/i2c_DRV.o ${OBJECTDIR}/DRV/UC1601_DRV.o ${OBJECTDIR}/GRAPHICS/BarHor.o ${OBJECTDIR}/GRAPHICS/Primitive.o ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o ${OBJECTDIR}/KEY/Key.o ${OBJECTDIR}/CRC8.o ${OBJECTDIR}/PT4_V6.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/Calibri_13pixels.o ${OBJECTDIR}/Menu.o ${OBJECTDIR}/EEPR24C16.o ${OBJECTDIR}/ProgPRM.o ${OBJECTDIR}/Arial_23pix_20_3F.o ${OBJECTDIR}/PWM.o ${OBJECTDIR}/Transmit.o

# Source Files
SOURCEFILES=DRV/i2c_DRV.c DRV/UC1601_DRV.c GRAPHICS/BarHor.c GRAPHICS/Primitive.c GRAPHICS/SCREEN_DRV.c KEY/Key.c CRC8.c PT4_V6.c Timer.c Calibri_13pixels.c Menu.c EEPR24C16.c ProgPRM.c Arial_23pix_20_3F.c PWM.c Transmit.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA006
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA006.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/DRV/i2c_DRV.o: DRV/i2c_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/DRV" 
	@${RM} ${OBJECTDIR}/DRV/i2c_DRV.o.d 
	@${RM} ${OBJECTDIR}/DRV/i2c_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DRV/i2c_DRV.c  -o ${OBJECTDIR}/DRV/i2c_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV/i2c_DRV.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/DRV/i2c_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DRV/UC1601_DRV.o: DRV/UC1601_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/DRV" 
	@${RM} ${OBJECTDIR}/DRV/UC1601_DRV.o.d 
	@${RM} ${OBJECTDIR}/DRV/UC1601_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DRV/UC1601_DRV.c  -o ${OBJECTDIR}/DRV/UC1601_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV/UC1601_DRV.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/DRV/UC1601_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/BarHor.o: GRAPHICS/BarHor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/BarHor.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/BarHor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/BarHor.c  -o ${OBJECTDIR}/GRAPHICS/BarHor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/BarHor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/BarHor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/Primitive.o: GRAPHICS/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/Primitive.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/Primitive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/Primitive.c  -o ${OBJECTDIR}/GRAPHICS/Primitive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/Primitive.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/Primitive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o: GRAPHICS/SCREEN_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/SCREEN_DRV.c  -o ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/KEY/Key.o: KEY/Key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/KEY" 
	@${RM} ${OBJECTDIR}/KEY/Key.o.d 
	@${RM} ${OBJECTDIR}/KEY/Key.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  KEY/Key.c  -o ${OBJECTDIR}/KEY/Key.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/KEY/Key.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/KEY/Key.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CRC8.o: CRC8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CRC8.o.d 
	@${RM} ${OBJECTDIR}/CRC8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CRC8.c  -o ${OBJECTDIR}/CRC8.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CRC8.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/CRC8.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PT4_V6.o: PT4_V6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PT4_V6.o.d 
	@${RM} ${OBJECTDIR}/PT4_V6.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PT4_V6.c  -o ${OBJECTDIR}/PT4_V6.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PT4_V6.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/PT4_V6.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${RM} ${OBJECTDIR}/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer.c  -o ${OBJECTDIR}/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Calibri_13pixels.o: Calibri_13pixels.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Calibri_13pixels.o.d 
	@${RM} ${OBJECTDIR}/Calibri_13pixels.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Calibri_13pixels.c  -o ${OBJECTDIR}/Calibri_13pixels.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Calibri_13pixels.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Calibri_13pixels.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Menu.o: Menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Menu.o.d 
	@${RM} ${OBJECTDIR}/Menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Menu.c  -o ${OBJECTDIR}/Menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Menu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/EEPR24C16.o: EEPR24C16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPR24C16.o.d 
	@${RM} ${OBJECTDIR}/EEPR24C16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  EEPR24C16.c  -o ${OBJECTDIR}/EEPR24C16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/EEPR24C16.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/EEPR24C16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProgPRM.o: ProgPRM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ProgPRM.o.d 
	@${RM} ${OBJECTDIR}/ProgPRM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ProgPRM.c  -o ${OBJECTDIR}/ProgPRM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ProgPRM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ProgPRM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Arial_23pix_20_3F.o: Arial_23pix_20_3F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Arial_23pix_20_3F.o.d 
	@${RM} ${OBJECTDIR}/Arial_23pix_20_3F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Arial_23pix_20_3F.c  -o ${OBJECTDIR}/Arial_23pix_20_3F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Arial_23pix_20_3F.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Arial_23pix_20_3F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PWM.o: PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PWM.o.d 
	@${RM} ${OBJECTDIR}/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PWM.c  -o ${OBJECTDIR}/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Transmit.o: Transmit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Transmit.o.d 
	@${RM} ${OBJECTDIR}/Transmit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Transmit.c  -o ${OBJECTDIR}/Transmit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Transmit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Transmit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/DRV/i2c_DRV.o: DRV/i2c_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/DRV" 
	@${RM} ${OBJECTDIR}/DRV/i2c_DRV.o.d 
	@${RM} ${OBJECTDIR}/DRV/i2c_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DRV/i2c_DRV.c  -o ${OBJECTDIR}/DRV/i2c_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV/i2c_DRV.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/DRV/i2c_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DRV/UC1601_DRV.o: DRV/UC1601_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/DRV" 
	@${RM} ${OBJECTDIR}/DRV/UC1601_DRV.o.d 
	@${RM} ${OBJECTDIR}/DRV/UC1601_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DRV/UC1601_DRV.c  -o ${OBJECTDIR}/DRV/UC1601_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DRV/UC1601_DRV.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/DRV/UC1601_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/BarHor.o: GRAPHICS/BarHor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/BarHor.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/BarHor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/BarHor.c  -o ${OBJECTDIR}/GRAPHICS/BarHor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/BarHor.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/BarHor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/Primitive.o: GRAPHICS/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/Primitive.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/Primitive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/Primitive.c  -o ${OBJECTDIR}/GRAPHICS/Primitive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/Primitive.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/Primitive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o: GRAPHICS/SCREEN_DRV.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/GRAPHICS" 
	@${RM} ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d 
	@${RM} ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GRAPHICS/SCREEN_DRV.c  -o ${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/GRAPHICS/SCREEN_DRV.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/KEY/Key.o: KEY/Key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/KEY" 
	@${RM} ${OBJECTDIR}/KEY/Key.o.d 
	@${RM} ${OBJECTDIR}/KEY/Key.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  KEY/Key.c  -o ${OBJECTDIR}/KEY/Key.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/KEY/Key.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/KEY/Key.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CRC8.o: CRC8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CRC8.o.d 
	@${RM} ${OBJECTDIR}/CRC8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CRC8.c  -o ${OBJECTDIR}/CRC8.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CRC8.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/CRC8.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PT4_V6.o: PT4_V6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PT4_V6.o.d 
	@${RM} ${OBJECTDIR}/PT4_V6.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PT4_V6.c  -o ${OBJECTDIR}/PT4_V6.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PT4_V6.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/PT4_V6.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${RM} ${OBJECTDIR}/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer.c  -o ${OBJECTDIR}/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timer.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Calibri_13pixels.o: Calibri_13pixels.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Calibri_13pixels.o.d 
	@${RM} ${OBJECTDIR}/Calibri_13pixels.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Calibri_13pixels.c  -o ${OBJECTDIR}/Calibri_13pixels.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Calibri_13pixels.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Calibri_13pixels.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Menu.o: Menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Menu.o.d 
	@${RM} ${OBJECTDIR}/Menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Menu.c  -o ${OBJECTDIR}/Menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Menu.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/EEPR24C16.o: EEPR24C16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPR24C16.o.d 
	@${RM} ${OBJECTDIR}/EEPR24C16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  EEPR24C16.c  -o ${OBJECTDIR}/EEPR24C16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/EEPR24C16.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/EEPR24C16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProgPRM.o: ProgPRM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ProgPRM.o.d 
	@${RM} ${OBJECTDIR}/ProgPRM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ProgPRM.c  -o ${OBJECTDIR}/ProgPRM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ProgPRM.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/ProgPRM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Arial_23pix_20_3F.o: Arial_23pix_20_3F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Arial_23pix_20_3F.o.d 
	@${RM} ${OBJECTDIR}/Arial_23pix_20_3F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Arial_23pix_20_3F.c  -o ${OBJECTDIR}/Arial_23pix_20_3F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Arial_23pix_20_3F.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Arial_23pix_20_3F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PWM.o: PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PWM.o.d 
	@${RM} ${OBJECTDIR}/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PWM.c  -o ${OBJECTDIR}/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PWM.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Transmit.o: Transmit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Transmit.o.d 
	@${RM} ${OBJECTDIR}/Transmit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Transmit.c  -o ${OBJECTDIR}/Transmit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Transmit.o.d"        -g -omf=elf   -O0 -I"DRV" -I"FONT" -I"GRAPHICS" -I"KEY" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Transmit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf       -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf   -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PT4_V6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
