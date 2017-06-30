#ifndef hero_h
#define hero_h

#include "gb.h"

extern GBUInt8 heroX;
extern GBUInt8 heroY;

void heroInit();
void heroUpdate();
void heroUpdateMiss(GBUInt8 state);

#endif
