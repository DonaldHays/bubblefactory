#ifndef save_h
#define save_h

#include "gb.h"

extern GBUInt16 saveNormalHighScore;
extern GBUInt16 saveHardHighScore;

void saveInit();
void saveRead();
void saveWrite();

#endif