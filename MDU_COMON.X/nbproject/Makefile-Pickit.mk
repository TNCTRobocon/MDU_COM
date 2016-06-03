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
ifeq "$(wildcard nbproject/Makefile-local-Pickit.mk)" "nbproject/Makefile-local-Pickit.mk"
include nbproject/Makefile-local-Pickit.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Pickit
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Driver/driver.c Driver/eeprom.c Driver/encoder.c Driver/ports.c Driver/pwm.c Driver/uart.c Task/motor.c Setting/configuration.c Driver/io.c Task/system.c Task/task.c Helper/print.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Driver/driver.o ${OBJECTDIR}/Driver/eeprom.o ${OBJECTDIR}/Driver/encoder.o ${OBJECTDIR}/Driver/ports.o ${OBJECTDIR}/Driver/pwm.o ${OBJECTDIR}/Driver/uart.o ${OBJECTDIR}/Task/motor.o ${OBJECTDIR}/Setting/configuration.o ${OBJECTDIR}/Driver/io.o ${OBJECTDIR}/Task/system.o ${OBJECTDIR}/Task/task.o ${OBJECTDIR}/Helper/print.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Driver/driver.o.d ${OBJECTDIR}/Driver/eeprom.o.d ${OBJECTDIR}/Driver/encoder.o.d ${OBJECTDIR}/Driver/ports.o.d ${OBJECTDIR}/Driver/pwm.o.d ${OBJECTDIR}/Driver/uart.o.d ${OBJECTDIR}/Task/motor.o.d ${OBJECTDIR}/Setting/configuration.o.d ${OBJECTDIR}/Driver/io.o.d ${OBJECTDIR}/Task/system.o.d ${OBJECTDIR}/Task/task.o.d ${OBJECTDIR}/Helper/print.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Driver/driver.o ${OBJECTDIR}/Driver/eeprom.o ${OBJECTDIR}/Driver/encoder.o ${OBJECTDIR}/Driver/ports.o ${OBJECTDIR}/Driver/pwm.o ${OBJECTDIR}/Driver/uart.o ${OBJECTDIR}/Task/motor.o ${OBJECTDIR}/Setting/configuration.o ${OBJECTDIR}/Driver/io.o ${OBJECTDIR}/Task/system.o ${OBJECTDIR}/Task/task.o ${OBJECTDIR}/Helper/print.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=Driver/driver.c Driver/eeprom.c Driver/encoder.c Driver/ports.c Driver/pwm.c Driver/uart.c Task/motor.c Setting/configuration.c Driver/io.c Task/system.c Task/task.c Helper/print.c main.c


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
	${MAKE}  -f nbproject/Makefile-Pickit.mk dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4012
MP_LINKER_FILE_OPTION=,--script=p30F4012.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Driver/driver.o: Driver/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/driver.o.d 
	@${RM} ${OBJECTDIR}/Driver/driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/driver.c  -o ${OBJECTDIR}/Driver/driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/eeprom.o: Driver/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/eeprom.o.d 
	@${RM} ${OBJECTDIR}/Driver/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/eeprom.c  -o ${OBJECTDIR}/Driver/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/encoder.o: Driver/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/encoder.o.d 
	@${RM} ${OBJECTDIR}/Driver/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/encoder.c  -o ${OBJECTDIR}/Driver/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/encoder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/ports.o: Driver/ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/ports.o.d 
	@${RM} ${OBJECTDIR}/Driver/ports.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/ports.c  -o ${OBJECTDIR}/Driver/ports.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/ports.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/ports.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/pwm.o: Driver/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/pwm.o.d 
	@${RM} ${OBJECTDIR}/Driver/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/pwm.c  -o ${OBJECTDIR}/Driver/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/uart.o: Driver/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/uart.o.d 
	@${RM} ${OBJECTDIR}/Driver/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/uart.c  -o ${OBJECTDIR}/Driver/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/motor.o: Task/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/motor.o.d 
	@${RM} ${OBJECTDIR}/Task/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/motor.c  -o ${OBJECTDIR}/Task/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Setting/configuration.o: Setting/configuration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Setting" 
	@${RM} ${OBJECTDIR}/Setting/configuration.o.d 
	@${RM} ${OBJECTDIR}/Setting/configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Setting/configuration.c  -o ${OBJECTDIR}/Setting/configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Setting/configuration.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Setting/configuration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/io.o: Driver/io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/io.o.d 
	@${RM} ${OBJECTDIR}/Driver/io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/io.c  -o ${OBJECTDIR}/Driver/io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/system.o: Task/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/system.o.d 
	@${RM} ${OBJECTDIR}/Task/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/system.c  -o ${OBJECTDIR}/Task/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/task.o: Task/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/task.o.d 
	@${RM} ${OBJECTDIR}/Task/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/task.c  -o ${OBJECTDIR}/Task/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Helper/print.o: Helper/print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Helper" 
	@${RM} ${OBJECTDIR}/Helper/print.o.d 
	@${RM} ${OBJECTDIR}/Helper/print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Helper/print.c  -o ${OBJECTDIR}/Helper/print.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Helper/print.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Helper/print.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Driver/driver.o: Driver/driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/driver.o.d 
	@${RM} ${OBJECTDIR}/Driver/driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/driver.c  -o ${OBJECTDIR}/Driver/driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/driver.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/eeprom.o: Driver/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/eeprom.o.d 
	@${RM} ${OBJECTDIR}/Driver/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/eeprom.c  -o ${OBJECTDIR}/Driver/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/eeprom.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/encoder.o: Driver/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/encoder.o.d 
	@${RM} ${OBJECTDIR}/Driver/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/encoder.c  -o ${OBJECTDIR}/Driver/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/encoder.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/ports.o: Driver/ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/ports.o.d 
	@${RM} ${OBJECTDIR}/Driver/ports.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/ports.c  -o ${OBJECTDIR}/Driver/ports.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/ports.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/ports.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/pwm.o: Driver/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/pwm.o.d 
	@${RM} ${OBJECTDIR}/Driver/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/pwm.c  -o ${OBJECTDIR}/Driver/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/pwm.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/uart.o: Driver/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/uart.o.d 
	@${RM} ${OBJECTDIR}/Driver/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/uart.c  -o ${OBJECTDIR}/Driver/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/uart.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/motor.o: Task/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/motor.o.d 
	@${RM} ${OBJECTDIR}/Task/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/motor.c  -o ${OBJECTDIR}/Task/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/motor.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Setting/configuration.o: Setting/configuration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Setting" 
	@${RM} ${OBJECTDIR}/Setting/configuration.o.d 
	@${RM} ${OBJECTDIR}/Setting/configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Setting/configuration.c  -o ${OBJECTDIR}/Setting/configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Setting/configuration.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Setting/configuration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Driver/io.o: Driver/io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Driver" 
	@${RM} ${OBJECTDIR}/Driver/io.o.d 
	@${RM} ${OBJECTDIR}/Driver/io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Driver/io.c  -o ${OBJECTDIR}/Driver/io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Driver/io.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Driver/io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/system.o: Task/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/system.o.d 
	@${RM} ${OBJECTDIR}/Task/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/system.c  -o ${OBJECTDIR}/Task/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/system.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Task/task.o: Task/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Task" 
	@${RM} ${OBJECTDIR}/Task/task.o.d 
	@${RM} ${OBJECTDIR}/Task/task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Task/task.c  -o ${OBJECTDIR}/Task/task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Task/task.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Task/task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Helper/print.o: Helper/print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Helper" 
	@${RM} ${OBJECTDIR}/Helper/print.o.d 
	@${RM} ${OBJECTDIR}/Helper/print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Helper/print.c  -o ${OBJECTDIR}/Helper/print.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Helper/print.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Helper/print.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -no-legacy-libc  -O1 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -no-legacy-libc      -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=64,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -no-legacy-libc  -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=64,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MDU_COMON.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Pickit
	${RM} -r dist/Pickit

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
