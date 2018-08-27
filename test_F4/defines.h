#pragma once

#include <stdint.h>

#define F_OSC   8000000UL
#define F_CPU   168000000UL

const uint32_t fCPU = F_CPU;
constexpr uint32_t FCPU() { return F_CPU; }

