#include "gb.h"
#include "bubbles.h"
#include "sprites.h"
#include "rand.h"
#include "game.h"

// ===
// Constant Data
// ===
const SpriteFrameAttributes bubbleSpriteFrames[] = {
    {0xC0, spritesAttributesMake(0, 0, 0, 0)},
    {0xC1, spritesAttributesMake(0, 0, 0, 0)},
    {0xC2, spritesAttributesMake(0, 0, 0, 0)},
    {0xC3, spritesAttributesMake(0, 0, 0, 0)}
};

// ===
// Variables
// ===
#define bubbleCount 4

#define bubbleStateIdle 1
#define bubbleStateActive 2
#define bubbleStatePopping 3

GBUInt8 numberOfActiveBubbles;

GBUInt8 bubbleStates[bubbleCount];
GBUInt8 bubblePositions[bubbleCount];
GBUInt8 bubblePositionTimers[bubbleCount];
GBUInt8 bubbleAnimationTimers[bubbleCount];
GBUInt8 bubbleAnimationFrames[bubbleCount];
GBUInt16 bubbleSpawnTimer;

// ===
// Private API
// ===
void _attemptToSpawnBubble() {
    GBUInt8 indexToActivate;
    
    if(numberOfActiveBubbles == bubbleCount) {
        return;
    }
    
    indexToActivate = random() & (bubbleCount - 1);
    while(bubbleStates[indexToActivate] != bubbleStateIdle) {
        indexToActivate = (indexToActivate + 1) & (bubbleCount - 1);
    }
    
    numberOfActiveBubbles++;
    bubbleStates[indexToActivate] = bubbleStateActive;
    bubblePositions[indexToActivate] = 0;
    bubblePositionTimers[indexToActivate] = gameBeltMovementSpeed;
    bubbleAnimationTimers[indexToActivate] = 30;
}

void _updateBubbles() {
    GBUInt8 index;
    
    for(index = 0; index != bubbleCount; index++) {
        if(bubbleStates[index] == bubbleStateIdle) {
            continue;
        }
        
        if(bubbleStates[index] == bubbleStatePopping) {
            bubbleAnimationTimers[index]--;
            spritesWriteFirstOAMIndex = spritesBubblesIndex + index;
            
            if(bubbleAnimationTimers[index] == 0) {
                bubbleStates[index] = bubbleStateIdle;
                bubblePositions[index] = 0;
                numberOfActiveBubbles--;
                
                spritesWriteX = 0;
            } else {
                if((index >> 1) & 1) {
                    spritesWriteX = 44 + bubblePositions[index];
                } else {
                    spritesWriteX = 124 - bubblePositions[index];
                }
                
                if(bubblePositions[index] > 32 && bubblePositions[index] < 48) {
                    spritesWriteX = 0;
                }
                
                spritesWriteY = 33 + (index >> 1) * 96;
                
                spritesWriteAttributes = &bubbleSpriteFrames[bubbleAnimationTimers[index] > 5 ? 2 : 3];
            }
            
            spritesWrite1x1();
            
            continue;
        }
        
        bubblePositionTimers[index]--;
        if(bubblePositionTimers[index] == 0) {
            bubblePositionTimers[index] = gameBeltMovementSpeed;
            bubblePositions[index]++;
        }
        
        spritesWriteFirstOAMIndex = spritesBubblesIndex + index;
            
        if(bubblePositions[index] == 82) {
            bubbleStates[index] = bubbleStateIdle;
            bubblePositions[index] = 0;
            numberOfActiveBubbles--;
            
            spritesWriteX = 0;
            spritesWriteY = 0;
            spritesWriteAttributes = &bubbleSpriteFrames[0];
            spritesWrite1x1();
            gameGainMiss();
            
            return;
        } else {
            bubbleAnimationTimers[index]--;
            if(bubbleAnimationTimers[index] == 0) {
                bubbleAnimationTimers[index] = 30;
                bubbleAnimationFrames[index] = (bubbleAnimationFrames[index] + 1) & 1;
            }
            
            if((index >> 1) & 1) {
                spritesWriteX = 44 + bubblePositions[index];
            } else {
                spritesWriteX = 124 - bubblePositions[index];
            }
            
            if(bubblePositions[index] > 32 && bubblePositions[index] < 48) {
                spritesWriteX = 0;
            }
            
            spritesWriteY = 33 + (index >> 1) * 96;
            
            spritesWriteAttributes = &bubbleSpriteFrames[bubbleAnimationFrames[index]];
        }
        
        spritesWrite1x1();
    }
}

// ===
// API
// ===
void bubblesInit() {
    GBUInt8 index;
    
    numberOfActiveBubbles = 0;
    bubbleSpawnTimer = 127;
    
    for(index = 0; index != bubbleCount; index++) {
        bubbleStates[index] = bubbleStateIdle;
        bubblePositions[index] = 0;
        bubbleAnimationTimers[index] = 30;
        bubbleAnimationFrames[index] = 0;
        bubblePositionTimers[index] = gameBeltMovementSpeed;
        
        spritesWriteFirstOAMIndex = spritesBubblesIndex + index;
        spritesWriteX = 0;
        spritesWriteY = 0;
        spritesWriteAttributes = &bubbleSpriteFrames[0];
        spritesWrite1x1();
    }
}

void bubblesUpdate() {
    bubbleSpawnTimer--;
    if(bubbleSpawnTimer == 0) {
        _attemptToSpawnBubble();
        bubbleSpawnTimer = gameMinimumBubbleSpawnTime + (random() % gameBubbleRandomSpawnRange);
    }
    
    _updateBubbles();
}

GBBool bubblesIsTopInDanger() {
    GBUInt8 index;
    
    for(index = 0; index != 2; index++) {
        if(bubbleStates[index] != bubbleStateActive) {
            continue;
        }
        
        if(bubblePositions[index] > 64) {
            return true;
        }
    }
    
    return false;
}

GBBool bubblesIsBottomInDanger() {
    GBUInt8 index;
    
    for(index = 2; index != 4; index++) {
        if(bubbleStates[index] != bubbleStateActive) {
            continue;
        }
        
        if(bubblePositions[index] > 64) {
            return true;
        }
    }
    
    return false;
}

GBBool bubblesPop(GBUInt8 row, GBUInt8 column) {
    GBUInt8 index;
    GBUInt8 start;
    GBUInt8 end;
    GBUInt8 minPosition;
    GBUInt8 maxPosition;
    
    // `bestPosition`, `bestIndex`, and `setBest` refer to finding the "best"
    // bubble to pop, in case there are multiple pop-able bubbles. The best
    // bubble is the one that's furthest down the track. This provides a
    // better player experience because when there are two bubbles near the
    // end of the track, if the player starts attacking and the bubble further
    // from the end pops first, the more at-risk bubble may fall into the
    // death trigger before the player can pop it.
    GBUInt8 bestPosition;
    GBUInt8 bestIndex;
    GBBool setBest;
    
    bestPosition = 0;
    bestIndex = 0;
    setBest = false;
    
    if(row < 5) {
        start = 0;
        end = 2;
        
        minPosition = ((3 + (7 - column)) - 3) * 16;
        maxPosition = ((3 + (7 - column)) - 2) * 16 + 2;
    } else {
        start = 2;
        end = 4;
        
        minPosition = (column - 3) * 16;
        maxPosition = (column - 2) * 16 + 3;
    }
    
    for(index = start; index != end; index++) {
        if(bubbleStates[index] != bubbleStateActive) {
            continue;
        }
        
        if(bubblePositions[index] > 32 && bubblePositions[index] < 48) {
            continue;
        }
        
        if(bubblePositions[index] < minPosition || bubblePositions[index] > maxPosition) {
            continue;
        }
        
        if(bubblePositions[index] >= bestPosition) {
            bestPosition = bubblePositions[index];
            bestIndex = index;
            setBest = true;
        }
    }
    
    if(setBest) {
        bubbleStates[bestIndex] = bubbleStatePopping;
        bubbleAnimationTimers[bestIndex] = 10;
        
        gameIncrementScore(1);
        
        return true;
    }
    
    return false;
}
