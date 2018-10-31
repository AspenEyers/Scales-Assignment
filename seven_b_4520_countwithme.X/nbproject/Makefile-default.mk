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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c basic_lcd.c basic_serial.c UI.c mode_controller.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/basic_lcd.o ${OBJECTDIR}/basic_serial.o ${OBJECTDIR}/UI.o ${OBJECTDIR}/mode_controller.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/basic_lcd.o.d ${OBJECTDIR}/basic_serial.o.d ${OBJECTDIR}/UI.o.d ${OBJECTDIR}/mode_controller.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/basic_lcd.o ${OBJECTDIR}/basic_serial.o ${OBJECTDIR}/UI.o ${OBJECTDIR}/mode_controller.o

# Source Files
SOURCEFILES=main.c basic_lcd.c basic_serial.c UI.c mode_controller.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4520
MP_PROCESSOR_OPTION_LD=18f4520
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7d30 -u_DEBUGCODELEN=0x2d0 -u_DEBUGDATASTART=0x5ef -u_DEBUGDATALEN=0x10
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/basic_lcd.o: basic_lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basic_lcd.o.d 
	@${RM} ${OBJECTDIR}/basic_lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/basic_lcd.o   basic_lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/basic_lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/basic_lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/basic_serial.o: basic_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basic_serial.o.d 
	@${RM} ${OBJECTDIR}/basic_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/basic_serial.o   basic_serial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/basic_serial.o 
	@${FIXDEPS} "${OBJECTDIR}/basic_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UI.o: UI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UI.o.d 
	@${RM} ${OBJECTDIR}/UI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UI.o   UI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UI.o 
	@${FIXDEPS} "${OBJECTDIR}/UI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/mode_controller.o: mode_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mode_controller.o.d 
	@${RM} ${OBJECTDIR}/mode_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/mode_controller.o   mode_controller.c 
	@${DEP_GEN} -d ${OBJECTDIR}/mode_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/mode_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/basic_lcd.o: basic_lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basic_lcd.o.d 
	@${RM} ${OBJECTDIR}/basic_lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/basic_lcd.o   basic_lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/basic_lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/basic_lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/basic_serial.o: basic_serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/basic_serial.o.d 
	@${RM} ${OBJECTDIR}/basic_serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/basic_serial.o   basic_serial.c 
	@${DEP_GEN} -d ${OBJECTDIR}/basic_serial.o 
	@${FIXDEPS} "${OBJECTDIR}/basic_serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UI.o: UI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UI.o.d 
	@${RM} ${OBJECTDIR}/UI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UI.o   UI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UI.o 
	@${FIXDEPS} "${OBJECTDIR}/UI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/mode_controller.o: mode_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mode_controller.o.d 
	@${RM} ${OBJECTDIR}/mode_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/mode_controller.o   mode_controller.c 
	@${DEP_GEN} -d ${OBJECTDIR}/mode_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/mode_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/seven_b_4520_countwithme.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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