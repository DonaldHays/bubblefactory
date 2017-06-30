#ifndef text_h
#define text_h

#include "gb.h"

void textLoadFont();
void textClearScreen();
void textDrawString(unsigned char *stringAddress, GBUInt8 length, GBUInt8 x, GBUInt8 y);

#endif