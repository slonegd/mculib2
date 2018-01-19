#pragma once

#include <stdint.h>

#define F_OSC   8000000UL
#define F_CPU   168000000UL

const uint32_t fCPU = 168000000;
constexpr uint32_t FCPU() { return 168000000; }

