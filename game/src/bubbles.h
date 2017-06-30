#ifndef bubbles_h
#define bubbles_h

#include "gb.h"

void bubblesInit();
void bubblesUpdate();

GBBool bubblesIsTopInDanger();
GBBool bubblesIsBottomInDanger();

GBBool bubblesPop(GBUInt8 row, GBUInt8 column);

#endif
