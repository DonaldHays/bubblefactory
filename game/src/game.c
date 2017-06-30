#include "game.h"
#include "rand.h"
#include "baddy.h"
#include "bubbles.h"
#include "hero.h"
#include "map.h"
#include "sprites.h"
#include "sound.h"
#include "gb.h"
#include "main.h"
#include "palette.h"
#include "save.h"

// ===
// Variables
// ===
#define gameStatePlaying 1
#define gameStateMiss 2
#define gameStatePaused 3

GBUInt8 gameState;
GBBool gameIsHardMode;
GBUInt16 gameScore;
GBUInt8 gameBeltMovementSpeed;
GBUInt16 gameMinimumBubbleSpawnTime;
GBUInt8 gameBubbleRandomSpawnRange;
GBUInt8 gameBaddyRandomSpawnRange;
GBUInt8 gameMinimumBaddySpawnTime;
GBUInt8 gameMissStateTimer;
GBUInt8 heartSpawnCount;
GBUInt8 fadeIn;

// ===
// API
// ===
void gameInit() {
    fadeIn = 0;
    gameState = gameStatePlaying;
    gameScore = 0;
    gameBeltMovementSpeed = 8;
    gameMinimumBubbleSpawnTime = 100;
    gameBubbleRandomSpawnRange = 200;
    gameBaddyRandomSpawnRange = 90;
    gameMinimumBaddySpawnTime = 40;
    heartSpawnCount = 0;
    
    mapInit();
    spritesInit();
    baddyInit();
    bubblesInit();
    heroInit();
}

void gameUpdate() {
    if(gbJoypadPressedSinceLastUpdate != 0) {
        random();
    }
    
    if(gbJoypadPressedSinceLastUpdate & gbJoypadStart) {
        if(gameState == gameStatePlaying) {
            gameState = gameStatePaused;
        }else if(gameState == gameStatePaused) {
            gameState = gameStatePlaying;
        }
    }
    
    if(gameState == gameStatePaused) {
        paletteSetPaused();
        return;
    }
    
    paletteSetLevel(fadeIn);
    if(fadeIn != 3) {
        fadeIn++;
    }
    
    if(gameState == gameStatePlaying) {
        baddyUpdate();
        
        if(gameState != gameStateMiss) {
            bubblesUpdate();
            
            if(gameState != gameStateMiss) {
                heroUpdate();
                mapUpdateLogic();
            }
        }
    } else if(gameState == gameStateMiss) {
        if(gameMissStateTimer == 180 || gameMissStateTimer == 120 || gameMissStateTimer == 60) {
            soundPlayMiss();
        }
        
        baddyUpdateMiss((gameMissStateTimer >> 5) & 1);
        heroUpdateMiss((gameMissStateTimer >> 5) & 1);
        
        gameMissStateTimer--;
        
        if(mapMissCount == 3) {
            if(gameMissStateTimer <= 4 && gameMissStateTimer > 0) {
                paletteSetLevel(gameMissStateTimer - 1);
            } else if(gameMissStateTimer == 0) {
                saveRead();
                if(gameIsHardMode) {
                    if(gameScore > saveHardHighScore) {
                        saveHardHighScore = gameScore;
                    }
                } else {
                    if(gameScore > saveNormalHighScore) {
                        saveNormalHighScore = gameScore;
                    }
                }
                saveWrite();
                
                paletteSetLevel(0);
                mainBeginMenu();
                return;
            }
        }
        
        if(gameMissStateTimer == 0) {
            baddyInit();
            bubblesInit();
            heroInit();
            
            mapCloseDoor(0, 0);
            mapCloseDoor(1, 0);
            mapCloseDoor(2, 0);
            mapCloseDoor(3, 0);
            mapCloseDoor(0, 1);
            mapCloseDoor(1, 1);
            mapCloseDoor(2, 1);
            mapCloseDoor(3, 1);
            
            gameState = gameStatePlaying;
        }
    }
}

void gameIncrementScore(GBUInt8 points) {
    GBUInt8 majorPart;
    GBUInt8 minorPart;
    GBUInt8 difficulty;
    
    gameScore += points;
    
    if(gameScore > 9999) {
        gameScore = 9999;
    } else if(gameScore == 9999) {
        return;
    }
    
    mapSetScore(gameScore);
    
    majorPart = gameScore / 100;
    minorPart = (gameScore % 100) / 20;
    difficulty = majorPart + minorPart + (gameIsHardMode ? 2 : 0);
    if(difficulty > 8) {
        difficulty = 8;
    }
    gameMinimumBubbleSpawnTime = 100 - difficulty * 10;
    gameBubbleRandomSpawnRange = 200 - difficulty * 10;
    gameBaddyRandomSpawnRange = 90 - difficulty * 10;
    
    if(difficulty > (gameIsHardMode ? 4 : 3)) {
        difficulty = (gameIsHardMode ? 4 : 3);
    }
    gameMinimumBaddySpawnTime = 40 - difficulty * 10;
    
    if(difficulty > 3) {
        difficulty = 3;
    }
    gameBeltMovementSpeed = 8 - difficulty;
    
    if((gameScore >= 200 && heartSpawnCount == 0) || (gameScore >= 500 && heartSpawnCount == 1) || (gameScore >= 900 && heartSpawnCount == 2)) {
        heartSpawnCount++;
        baddySpawnHeart();
    }
}

void gameGainMiss() {
    mapGainMiss();
    gameState = gameStateMiss;
    gameMissStateTimer = 180;
}
