#ifndef memory_h
#define memory_h

#include "gb.h"

extern volatile GBUInt8 memoryCopyLength;

void memoryCopy(void * dest, const void * src);

#endif
