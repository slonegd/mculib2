INCLUDES  = -I.
INCLUDES += -I..
INCLUDES += -I../loki
INCLUDES += -I../hal
INCLUDES += -I../hal/ral

INCLUDES_F4  = -I../STM32F4_files
INCLUDES_F4 += -I../STM32F4_files/CMSIS

INCLUDES_F0  = -I../STM32F0_files
INCLUDES_F0 += -I../STM32F0_files/CMSIS

CPP_FLAGS = -std=c++17 -Wall -DTEST -g $(INCLUDES) -Wno-register -Wno-int-to-pointer-cast
CPP_FLAGS_F4 += $(CPP_FLAGS) $(INCLUDES_F4)
CPP_FLAGS_F0 += $(CPP_FLAGS) $(INCLUDES_F0)

BUILD_DIR = build

all: $(BUILD_DIR)
	g++-7 adc_f0_t.cpp   $(CPP_FLAGS_F0) -o ./$(BUILD_DIR)/adc_f0 -pthread
	g++-7 adc_f4_t.cpp   $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/adc_f4
	g++-7 flash_f0_t.cpp $(CPP_FLAGS_F0) -o ./$(BUILD_DIR)/flash_f0 -pthread
	g++-7 flash_f4_t.cpp $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/flash_f4 -pthread
	g++-7 flash_t.cpp    $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/flash
	g++-7 tim_f0_t.cpp   $(CPP_FLAGS_F0) -o ./$(BUILD_DIR)/tim_f0_t
	g++-7 tim_f4_t.cpp   $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/tim_f4_t

	./$(BUILD_DIR)/adc_f0
	./$(BUILD_DIR)/adc_f4
	./$(BUILD_DIR)/flash_f0
	./$(BUILD_DIR)/flash_f4
	./$(BUILD_DIR)/flash
	./$(BUILD_DIR)/tim_f0
	./$(BUILD_DIR)/tim_f4


$(BUILD_DIR):
	mkdir $(BUILD_DIR)

current: $(BUILD_DIR)
	g++-7 tim_f4_t.cpp    $(CPP_FLAGS_F4) -o ./$(BUILD_DIR)/tim_f4
	./$(BUILD_DIR)/tim_f4