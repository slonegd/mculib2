INCLUDES  = -I.
INCLUDES += -I..
INCLUDES += -I../loki
INCLUDES += -I../hal
INCLUDES += -I../hal/ral

INCLUDES_F4  = -I../STM32F4_files
INCLUDES_F4 += -I../STM32F4_files/CMSIS

CPP_FLAGS = -std=c++17 -Wall -DTEST -g $(INCLUDES) -Wno-register -Wno-int-to-pointer-cast
CPP_FLAGS_F4 += $(CPP_FLAGS) $(INCLUDES_F4)

BUILD_DIR = build

all: $(BUILD_DIR)
	g++-7 ADC_F4.cpp $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/ADC_F4
	./$(BUILD_DIR)/ADC_F4


$(BUILD_DIR):
	mkdir $@