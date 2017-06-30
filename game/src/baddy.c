#include "baddy.h"
#include "sprites.h"
#include "map.h"
#include "rand.h"
#include "sound.h"
#include "game.h"
#include "hero.h"

// ===
// Definitions
// ===
#define baddyCount 8

#define baddyStateIdle 1
#define baddyStateWarmup 2
#define baddyStateMarching 3
#define baddyStateCooldown 4
#define baddyStateBux 5

#define doorOpenTime 20
#define minSpawnTime 25

// ===
// Constant Data
// ===
const SpriteFrameAttributes baddySpriteFrames[][4] = {
    // Running to the right
    {{0xA0, spritesAttributesMake(0, 0, 0, 1)}, {0xA1, spritesAttributesMake(0, 0, 0, 1)}, {0xB0, spritesAttributesMake(0, 0, 0, 1)}, {0xB1, spritesAttributesMake(0, 0, 0, 1)}},
    {{0xA2, spritesAttributesMake(0, 0, 0, 1)}, {0xA3, spritesAttributesMake(0, 0, 0, 1)}, {0xB2, spritesAttributesMake(0, 0, 0, 1)}, {0xB3, spritesAttributesMake(0, 0, 0, 1)}},
    {{0xA4, spritesAttributesMake(0, 0, 0, 1)}, {0xA5, spritesAttributesMake(0, 0, 0, 1)}, {0xB4, spritesAttributesMake(0, 0, 0, 1)}, {0xB5, spritesAttributesMake(0, 0, 0, 1)}},
    {{0xA2, spritesAttributesMake(0, 0, 0, 1)}, {0xA3, spritesAttributesMake(0, 0, 0, 1)}, {0xB2, spritesAttributesMake(0, 0, 0, 1)}, {0xB3, spritesAttributesMake(0, 0, 0, 1)}},
    
    // Running to the left
    {{0xA1, spritesAttributesMake(0, 1, 0, 1)}, {0xA0, spritesAttributesMake(0, 1, 0, 1)}, {0xB1, spritesAttributesMake(0, 1, 0, 1)}, {0xB0, spritesAttributesMake(0, 1, 0, 1)}},
    {{0xA3, spritesAttributesMake(0, 1, 0, 1)}, {0xA2, spritesAttributesMake(0, 1, 0, 1)}, {0xB3, spritesAttributesMake(0, 1, 0, 1)}, {0xB2, spritesAttributesMake(0, 1, 0, 1)}},
    {{0xA5, spritesAttributesMake(0, 1, 0, 1)}, {0xA4, spritesAttributesMake(0, 1, 0, 1)}, {0xB5, spritesAttributesMake(0, 1, 0, 1)}, {0xB4, spritesAttributesMake(0, 1, 0, 1)}},
    {{0xA3, spritesAttributesMake(0, 1, 0, 1)}, {0xA2, spritesAttributesMake(0, 1, 0, 1)}, {0xB3, spritesAttributesMake(0, 1, 0, 1)}, {0xB2, spritesAttributesMake(0, 1, 0, 1)}},
    
    // Lecture to the right
    {{0xA6, spritesAttributesMake(0, 0, 0, 1)}, {0xA7, spritesAttributesMake(0, 0, 0, 1)}, {0xB6, spritesAttributesMake(0, 0, 0, 1)}, {0xB7, spritesAttributesMake(0, 0, 0, 1)}},
    {{0xA8, spritesAttributesMake(0, 0, 0, 1)}, {0xA9, spritesAttributesMake(0, 0, 0, 1)}, {0xB8, spritesAttributesMake(0, 0, 0, 1)}, {0xB9, spritesAttributesMake(0, 0, 0, 1)}},
    
    // Lecture to the left
    {{0xA7, spritesAttributesMake(0, 1, 0, 1)}, {0xA6, spritesAttributesMake(0, 1, 0, 1)}, {0xB7, spritesAttributesMake(0, 1, 0, 1)}, {0xB6, spritesAttributesMake(0, 1, 0, 1)}},
    {{0xA9, spritesAttributesMake(0, 1, 0, 1)}, {0xA8, spritesAttributesMake(0, 1, 0, 1)}, {0xB9, spritesAttributesMake(0, 1, 0, 1)}, {0xB8, spritesAttributesMake(0, 1, 0, 1)}},
    
    // Bux
    {{0xAE, spritesAttributesMake(0, 0, 0, 1)}, {0xAF, spritesAttributesMake(0, 0, 0, 1)}, {0xBE, spritesAttributesMake(0, 0, 0, 1)}, {0xBF, spritesAttributesMake(0, 0, 0, 1)}},
    
    // Heart
    {{0xAC, spritesAttributesMake(0, 0, 0, 0)}, {0xAD, spritesAttributesMake(0, 0, 0, 0)}, {0xBC, spritesAttributesMake(0, 0, 0, 0)}, {0xBD, spritesAttributesMake(0, 0, 0, 0)}},
};

// ===
// Variables
// ===
GBUInt8 buxProtectionCounter;
GBBool hasSpawnedBux;
GBUInt8 numberOfActiveBaddies;
GBUInt8 baddyStates[baddyCount];
GBUInt8 baddyStateTimers[baddyCount];
GBUInt8 baddyAnimationFrames[baddyCount];
GBUInt8 baddyAnimationTimers[baddyCount];
GBUInt8 baddyPositions[baddyCount];
GBUInt8 baddyLaneProtectionTimers[baddyCount];
GBBool baddyIsHeart[baddyCount];
GBBool baddyIsBux[baddyCount];
GBUInt8 baddySpawnTimer;
GBBool needsToSpawnHeart;
GBBool moveHeartThisFrame;

// ===
// Private API
// ===
GBBool _canSpawnBaddy() {
    GBUInt8 index;
    
    for(index = 0; index != baddyCount; index++) {
        if(baddyStates[index] == baddyStateIdle && baddyLaneProtectionTimers[index] == 0) {
            return true;
        }
    }
    
    return false;
}

void _attemptToSpawnBaddy() {
    GBUInt8 indexToActivate;
    
    if(_canSpawnBaddy() == false) {
        return;
    }
    
    indexToActivate = random() & (baddyCount - 1);
    while(baddyStates[indexToActivate] != baddyStateIdle || baddyLaneProtectionTimers[indexToActivate] != 0) {
        indexToActivate = (indexToActivate + 1) & (baddyCount - 1);
    }
    
    numberOfActiveBaddies++;
    
    if(buxProtectionCounter == 0 && (hasSpawnedBux == false) && ((random() & 0x07) == 1)) {
        buxProtectionCounter = 12;
        hasSpawnedBux = true;
        baddyIsBux[indexToActivate] = true;
        
        baddyStates[indexToActivate] = baddyStateBux;
        baddyStateTimers[indexToActivate] = 250;
        baddyPositions[indexToActivate] = 8 + (random() % 8) * 16;
    } else {
        if(buxProtectionCounter > 0) {
            buxProtectionCounter--;
        }
        
        baddyIsBux[indexToActivate] = false;
        
        baddyIsHeart[indexToActivate] = needsToSpawnHeart;
        baddyStates[indexToActivate] = baddyStateWarmup;
        baddyStateTimers[indexToActivate] = doorOpenTime;
        needsToSpawnHeart = false;
        
        // This lane can't spawn for a bit of time.
        // The bitwise operations calculate the lane indices.
        baddyLaneProtectionTimers[indexToActivate & 0xFE] = 60;
        baddyLaneProtectionTimers[indexToActivate | 0x01] = 60;
        
        mapOpenDoor(indexToActivate >> 1, (indexToActivate >> 1) & 1);
        soundPlayDoorOpen();
    }
}

void _updateBaddies() {
    GBUInt8 index;
    
    moveHeartThisFrame = !moveHeartThisFrame;
    
    for(index = 0; index != baddyCount; index++) {
        if(baddyLaneProtectionTimers[index] != 0) {
            baddyLaneProtectionTimers[index]--;
        }
        
        if(baddyStates[index] == baddyStateIdle) {
            continue;
        }
        
        if(baddyStates[index] == baddyStateBux) {
            spritesWriteFirstOAMIndex = spritesBaddiesIndex + index * 4;
            
            baddyStateTimers[index]--;
            if(baddyStateTimers[index] == 0) {
                hasSpawnedBux = false;
                baddyStates[index] = baddyStateIdle;
                numberOfActiveBaddies--;
                
                spritesWriteX = 0;
                spritesWriteY = 0;
                spritesWriteAttributes = baddySpriteFrames[0];
                spritesWrite2x2();
                continue;
            }
            
            if((index >> 1) & 1) {
                spritesWriteX = 160 - (8 + baddyPositions[index]);
            } else {
                spritesWriteX = 8 + baddyPositions[index];
            }
            spritesWriteY = 46 + (index >> 1) * 16 + (index > 3 ? 16 : 0);
            
            if(heroY + 3 >= spritesWriteY && heroY - 3 <= spritesWriteY && heroX + 4 >= spritesWriteX && heroX - 4 <= spritesWriteX) {
                hasSpawnedBux = false;
                baddyStates[index] = baddyStateIdle;
                numberOfActiveBaddies--;
            
                spritesWriteX = 0;
                spritesWriteY = 0;
                gameIncrementScore(10);
                soundPlayBux();
            } else if(baddyStateTimers[index] < 60 && baddyStateTimers[index] & 0x01) {
                // Flicker in the last second
                spritesWriteX = 0;
                spritesWriteY = 0;
            }
            
            spritesWriteAttributes = baddySpriteFrames[12];
            spritesWrite2x2();
            
            continue;
        }
        
        if(baddyStateTimers[index] != 0) {
            baddyStateTimers[index]--;
        } else if(baddyStates[index] == baddyStateWarmup) {
            mapCloseDoor(index >> 1, (index >> 1) & 1);
            baddyStates[index] = baddyStateMarching;
            baddyPositions[index] = 0;
            baddyAnimationTimers[index] = 15;
        } else if(baddyStates[index] == baddyStateMarching) {
            if(baddyIsHeart[index] == false || moveHeartThisFrame) {
                baddyPositions[index]++;
            }
            
            spritesWriteFirstOAMIndex = spritesBaddiesIndex + index * 4;
            
            if(baddyPositions[index] == 144) {
                mapOpenDoor(index >> 1, ((index >> 1) & 1) ^ 1);
                baddyStates[index] = baddyStateCooldown;
                baddyPositions[index] = 0;
                baddyStateTimers[index] = doorOpenTime;
                
                spritesWriteX = 0;
                spritesWriteY = 0;
                spritesWriteAttributes = baddySpriteFrames[0];
            } else {
                baddyAnimationTimers[index]--;
                if(baddyAnimationTimers[index] == 0) {
                    baddyAnimationTimers[index] = 15;
                    baddyAnimationFrames[index] = (baddyAnimationFrames[index] + 1) & 3;
                }
                
                if((index >> 1) & 1) {
                    spritesWriteX = 160 - (8 + baddyPositions[index]);
                } else {
                    spritesWriteX = 8 + baddyPositions[index];
                }
                spritesWriteY = 46 + (index >> 1) * 16 + (index > 3 ? 16 : 0);
                spritesWriteAttributes = baddySpriteFrames[baddyAnimationFrames[index] + (((index >> 1) & 1) ? 4 : 0)];
                
                if(baddyIsHeart[index]) {
                    spritesWriteAttributes = baddySpriteFrames[13];
                }
                
                if(heroY + 3 >= spritesWriteY && heroY - 3 <= spritesWriteY) {
                    if(heroX + 4 >= spritesWriteX && heroX - 4 <= spritesWriteX) {
                        if(baddyIsHeart[index]) {
                            baddyStates[index] = baddyStateCooldown;
                            baddyPositions[index] = 0;
                            baddyStateTimers[index] = doorOpenTime;
                            
                            spritesWriteX = 0;
                            spritesWriteY = 0;
                            spritesWriteAttributes = baddySpriteFrames[0];
                            
                            gameIncrementScore(20);
                            mapLoseMiss();
                            soundPlayBux();
                        } else {
                            if(baddyPositions[index] <= 8) {
                                baddyPositions[index] = 0;
                            } else {
                                baddyPositions[index] -= 8;
                            }
                            
                            spritesWrite2x2();
                            gameGainMiss();
                            return;
                        }
                    }
                }
            }
            
            spritesWrite2x2();
        } else if(baddyStates[index] == baddyStateCooldown) {
            mapCloseDoor(index >> 1, ((index >> 1) & 1) ^ 1);
            baddyStates[index] = baddyStateIdle;
            numberOfActiveBaddies--;
        }
    }
}

// ===
// API
// ===
void baddyInit() {
    GBUInt8 index;
    
    moveHeartThisFrame = false;
    numberOfActiveBaddies = 0;
    baddySpawnTimer = 255;
    hasSpawnedBux = false;
    buxProtectionCounter = 16;
    needsToSpawnHeart = false;
    
    for(index = 0; index != baddyCount; index++) {
        baddyStates[index] = baddyStateIdle;
        baddyStateTimers[index] = 0;
        baddyAnimationTimers[index] = 0;
        baddyPositions[index] = 0;
        baddyAnimationFrames[index] = 0;
        baddyIsHeart[index] = false;
        baddyIsBux[index] = false;
        baddyLaneProtectionTimers[index] = 0;
        
        spritesWriteFirstOAMIndex = spritesBaddiesIndex + index * 4;
        spritesWriteX = 0;
        spritesWriteY = 0;
        spritesWriteAttributes = baddySpriteFrames[0];
        spritesWrite2x2();
    }
}

void baddyUpdate() {
    baddySpawnTimer--;
    if(baddySpawnTimer == 0) {
        _attemptToSpawnBaddy();
        baddySpawnTimer = minSpawnTime + gameMinimumBaddySpawnTime + (random() % gameBaddyRandomSpawnRange);
    }
    
    _updateBaddies();
}

void baddyUpdateMiss(GBUInt8 state) {
    GBUInt8 index;
    
    for(index = 0; index != baddyCount; index++) {
        if(baddyStates[index] == baddyStateIdle) {
            continue;
        }
        
        if(baddyStates[index] == baddyStateMarching && baddyIsHeart[index] == false) {
            spritesWriteFirstOAMIndex = spritesBaddiesIndex + index * 4;
            if((index >> 1) & 1) {
                spritesWriteX = 160 - (8 + baddyPositions[index]);
            } else {
                spritesWriteX = 8 + baddyPositions[index];
            }
            spritesWriteY = 46 + (index >> 1) * 16 + (index > 3 ? 16 : 0);
            spritesWriteAttributes = baddySpriteFrames[state + 8 + (((index >> 1) & 1) ? 2 : 0)];
            
            spritesWrite2x2();
        }
    }
}

void baddySpawnHeart() {
    needsToSpawnHeart = true;
}
