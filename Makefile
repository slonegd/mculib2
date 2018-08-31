##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [2.24.1] date: [Fri Aug 18 13:20:33 MSK 2017]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET_F4 = STM32F4_DISCOVERY
TARGET_F0 = STM32F0_DISCOVERY
TARGET_F1 = STM32F1_DISCOVERY

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Os
CPPSTD =-std=c++17

# Build path
BUILD_DIR = build

######################################
# source
######################################
CPP_SOURCES_F4 = test_F4/main_F4.cpp
CPP_SOURCES_F0 = test_F0/main_F0.cpp
CPP_SOURCES_F1 = test_F1/main_F1.cpp

ASM_SOURCES_F4 = STM32F4_files/startup_stm32f405xx.s
ASM_SOURCES_F0 = STM32F0_files/startup_stm32f030x6.s
ASM_SOURCES_F1 = STM32F1_files/startup_stm32f103xb.s

# C includes
C_INCLUDES =  
C_INCLUDES += -I.
C_INCLUDES += -Ihal
C_INCLUDES += -Ihal/ral

C_INCLUDES_F4 =
C_INCLUDES_F4 += -Itest_F4
C_INCLUDES_F4 += -ISTM32F4_files 
C_INCLUDES_F4 += -ISTM32F4_files/CMSIS 

C_INCLUDES_F0 =
C_INCLUDES_F0 += -Itest_F0
C_INCLUDES_F0 += -ISTM32F0_files 
C_INCLUDES_F0 += -ISTM32F0_files/CMSIS 

C_INCLUDES_F1 = 
C_INCLUDES_F1 += -Itest_F1
C_INCLUDES_F1 += -ISTM32F1_files
C_INCLUDES_F1 += -ISTM32F1_files/CMSIS

# C defines
C_DEFS_F4 = -DSTM32F405xx
C_DEFS_F0 = -DSTM32F030x6
C_DEFS_F1 = -DSTM32F103xB


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
#PREFIX = /home/slonegd/Code/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi-
#PREFIX = /home/dvk/code/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-
# PREFIX = /home/peltikhin/code/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-

CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
CPU_F4 = -mcpu=cortex-m4
CPU_F0 = -mcpu=cortex-m0
CPU_F1 = -mcpu=cortex-m3

# NONE for Cortex-M0/M0+/M3
FPU_F4 = -mfpu=fpv4-sp-d16
FPU_F0 =
FPU_F1 =

FLOAT-ABI_F4 = -mfloat-abi=hard
FLOAT-ABI_F0 =
FLOAT-ABI_F1 =

# mcu
MCU_F4 = $(CPU_F4) -mthumb $(FPU_F4) $(FLOAT-ABI_F4)
MCU_F0 = $(CPU_F0) -mthumb $(FPU_F0) $(FLOAT-ABI_F0)
MCU_F1 = $(CPU_F1) -mthumb $(FPU_F1) $(FLOAT-ABI_F1)

# compile gcc flags
ASFLAGS_F4 = $(MCU_F4) $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS_F0 = $(MCU_F0) $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS_F1 = $(MCU_F1) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = -Wall -Wno-register -fdata-sections -ffunction-sections -fno-exceptions -fno-strict-volatile-bitfields
CFLAGS_F4 = $(MCU_F4) $(C_DEFS_F4) $(C_INCLUDES) $(C_INCLUDES_F4) $(OPT) $(CFLAGS)
CFLAGS_F0 = $(MCU_F0) $(C_DEFS_F0) $(C_INCLUDES) $(C_INCLUDES_F0) $(OPT) $(CFLAGS)
CFLAGS_F1 = $(MCU_F1) $(C_DEFS_F1) $(C_INCLUDES) $(C_INCLUDES_F1) $(OPT) $(CFLAGS)

CFLAGS_F4 += -g -gdwarf-2 
CFLAGS_F0 += -g -gdwarf-2 
CFLAGS_F1 += -g -gdwarf-2 


# Generate dependency information
CFLAGS_F4 += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
CFLAGS_F0 += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
CFLAGS_F1 += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
LDSCRIPT_F4 = STM32F4_files/STM32F405RGTx_FLASH.ld
LDSCRIPT_F0 = STM32F0_files/STM32F030K6Tx_FLASH.ld
LDSCRIPT_F1 = STM32F1_files/STM32F103RBTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys

LDFLAGS_F4 = $(MCU_F4) -specs=nano.specs -T$(LDSCRIPT_F4) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET_F4).map,--cref -Wl,--gc-sections
LDFLAGS_F0 = $(MCU_F0) -specs=nano.specs -T$(LDSCRIPT_F0) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET_F0).map,--cref -Wl,--gc-sections
LDFLAGS_F1 = $(MCU_F1) -specs=nano.specs -T$(LDSCRIPT_F1) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET_F1).map,--cref -Wl,--gc-sections


# default action: build all
all: clean \
$(BUILD_DIR)/$(TARGET_F4).elf $(BUILD_DIR)/$(TARGET_F4).hex $(BUILD_DIR)/$(TARGET_F4).bin \
$(BUILD_DIR)/$(TARGET_F0).elf $(BUILD_DIR)/$(TARGET_F0).hex $(BUILD_DIR)/$(TARGET_F0).bin \
$(BUILD_DIR)/$(TARGET_F1).elf $(BUILD_DIR)/$(TARGET_F1).hex $(BUILD_DIR)/$(TARGET_F1).bin
	


#######################################
# build the application
#######################################
# list of objects

OBJECTS_F4 += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES_F4:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES_F4)))
# list of ASM program objects
OBJECTS_F4 += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES_F4:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES_F4)))

OBJECTS_F0 += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES_F0:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES_F0)))
# list of ASM program objects
OBJECTS_F0 += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES_F0:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES_F0)))

OBJECTS_F1 += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES_F1:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES_F1)))
# list of ASM program objects
OBJECTS_F1 += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES_F1:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES_F1)))


$(BUILD_DIR)/main_F4.o: $(CPP_SOURCES_F4) Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CFLAGS_F4) $(CPPSTD) -fno-rtti -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/startup_stm32f405xx.o: $(ASM_SOURCES_F4) Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS_F4) $< -o $@

$(BUILD_DIR)/main_F0.o:$(CPP_SOURCES_F0) Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CFLAGS_F0) $(CPPSTD) -fno-rtti -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/startup_stm32f030x6.o: $(ASM_SOURCES_F0) Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS_F0) $< -o $@

$(BUILD_DIR)/main_F1.o:$(CPP_SOURCES_F1) Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CFLAGS_F1) $(CPPSTD) -fno-rtti -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/startup_stm32f103xb.o: $(ASM_SOURCES_F1) Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS_F1) $< -o $@

$(BUILD_DIR)/$(TARGET_F4).elf: $(OBJECTS_F4) Makefile
	$(CC) $(OBJECTS_F4) $(LDFLAGS_F4) -o $@
	$(SZ) $@

$(BUILD_DIR)/$(TARGET_F0).elf: $(OBJECTS_F0) Makefile
	$(CC) $(OBJECTS_F0) $(LDFLAGS_F0) -o $@
	$(SZ) $@

$(BUILD_DIR)/$(TARGET_F1).elf: $(OBJECTS_F1) Makefile
	$(CC) $(OBJECTS_F1) $(LDFLAGS_F1) -o $@
	$(SZ) $@	

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

f4_flash:
	#/home/dvk/code/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
	#/home/slonegd/Code/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
	st-flash write $(BUILD_DIR)/$(TARGET_F4).bin 0x8000000
	#/home/peltikhin/code/EmbeddedArm/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET_F4).bin 0x8000000

f0_flash:
	#/home/peltikhin/code/EmbeddedArm/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET_F0).bin 0x8000000
	st-flash write $(BUILD_DIR)/$(TARGET_F0).bin 0x8000000

f1_flash:
	#/home/peltikhin/code/EmbeddedArm/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET_F1).bin 0x8000000
	st-flash write $(BUILD_DIR)/$(TARGET_F1).bin 0x8000000


util:
	#/home/dvk/code/stlink/build/Release/src/gdbserver/st-util
	#/home/slonegd/Code/stlink/build/Release/src/gdbserver/st-util
	#/home/peltikhin/code/EmbeddedArm/stlink/build/Release/src/gdbserver/st-util
	st-util
debug: clean all flash_stlink util
  
#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***