//#ifndef BITWISE_HACK_H
//#define BITWISE_HACK_H
#include <stdint.h>

inline uint32_t RoundDownToPowerOfTwo(uint32_t value)
{
    if (value > 0)
    {
       value = value | (value >> 1);
	   value = value | (value >> 2);
	   value = value | (value >> 4);
	   value = value | (value >> 8);
	   value = value | (value >> 16);
	   
	   return value - (value >> 1);
    }
    else
    {
        return 0;
    }
}

inline uint32_t Log2OfPowerOfTwo(uint32_t powerOfTwo)
{
    uint32_t log2 = (powerOfTwo & 0xAAAAAAAAu) != 0;
    log2 |= ((powerOfTwo & 0xFFFF0000u) != 0) << 4;
    log2 |= ((powerOfTwo & 0xFF00FF00u) != 0) << 3;
    log2 |= ((powerOfTwo & 0xF0F0F0F0u) != 0) << 2;
    log2 |= ((powerOfTwo & 0xCCCCCCCCu) != 0) << 1;
    return log2;
}
//#endif