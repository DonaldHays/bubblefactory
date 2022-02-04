#ifndef memory_h
#define memory_h

#include "gb.h"

extern volatile const void * memoryCopySourceAddress;
extern volatile void * memoryCopyDestinationAddress;
extern volatile GBUInt8 memoryCopyLength;

void memoryCopy() __sdcccall(0);

#endif
