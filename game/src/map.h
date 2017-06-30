#ifndef map_h
#define map_h

#include "gb.h"

#define mapCollisionOpen 0
#define mapCollisionSolid 1
#define mapCollisionBelt 2

// A 16x7 array of collision data.
extern const GBUInt8 mapCollisionData[];

#define mapCollisionAt(x, y) (mapCollisionData[((y) << 4) | (x)])

extern GBUInt8 mapMissCount;

void mapInit();
void mapUpdateLogic();
void mapUpdateGraphics();
void mapSetHighScore(GBUInt16 highScore);
void mapSetScore(GBUInt16 score);
void mapGainMiss();
void mapLoseMiss();
void mapOpenDoor(GBUInt8 row, GBUInt8 column);
void mapCloseDoor(GBUInt8 row, GBUInt8 column);

#endif
