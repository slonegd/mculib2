#pragma once

#include "registr.h"

#if defined(STM32F0)
#include "flash_f0.h"
#elif defined(STM32F4)
#include "flash_f4.h"
#endif
