#ifndef game_h
#define game_h

#include "gb.h"

extern GBBool gameIsHardMode;
extern GBUInt16 gameScore;
extern GBUInt8 gameBeltMovementSpeed;
extern GBUInt16 gameMinimumBubbleSpawnTime;
extern GBUInt8 gameBubbleRandomSpawnRange;
extern GBUInt8 gameBaddyRandomSpawnRange;
extern GBUInt8 gameMinimumBaddySpawnTime;

void gameInit();
void gameUpdate();
void gameIncrementScore(GBUInt8 points);
void gameGainMiss();

#endif
