#include "hero.h"
#include "sprites.h"
#include "gb.h"
#include "map.h"
#include "bubbles.h"
#include "sound.h"

// ===
// Constant Data
// ===
const SpriteFrameAttributes heroSpriteFrames[][4] = {
    {{0x80, 0x00}, {0x81, 0x00}, {0x90, 0x00}, {0x91, 0x00}},
    {{0x81, spritesAttributesMake(0, 1, 0, 0)}, {0x80, spritesAttributesMake(0, 1, 0, 0)}, {0x91, spritesAttributesMake(0, 1, 0, 0)}, {0x90, spritesAttributesMake(0, 1, 0, 0)}},
    
    // Run Down
    {{0x82, spritesAttributesMake(0, 0, 0, 0)}, {0x83, spritesAttributesMake(0, 0, 0, 0)}, {0x92, spritesAttributesMake(0, 0, 0, 0)}, {0x93, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x84, spritesAttributesMake(0, 0, 0, 0)}, {0x85, spritesAttributesMake(0, 0, 0, 0)}, {0x94, spritesAttributesMake(0, 0, 0, 0)}, {0x95, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x83, spritesAttributesMake(0, 1, 0, 0)}, {0x82, spritesAttributesMake(0, 1, 0, 0)}, {0x93, spritesAttributesMake(0, 1, 0, 0)}, {0x92, spritesAttributesMake(0, 1, 0, 0)}},
    {{0x85, spritesAttributesMake(0, 1, 0, 0)}, {0x84, spritesAttributesMake(0, 1, 0, 0)}, {0x95, spritesAttributesMake(0, 1, 0, 0)}, {0x94, spritesAttributesMake(0, 1, 0, 0)}},
    
    // Run Up
    {{0x86, spritesAttributesMake(0, 0, 0, 0)}, {0x87, spritesAttributesMake(0, 0, 0, 0)}, {0x96, spritesAttributesMake(0, 0, 0, 0)}, {0x97, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x88, spritesAttributesMake(0, 0, 0, 0)}, {0x89, spritesAttributesMake(0, 0, 0, 0)}, {0x98, spritesAttributesMake(0, 0, 0, 0)}, {0x99, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x87, spritesAttributesMake(0, 1, 0, 0)}, {0x86, spritesAttributesMake(0, 1, 0, 0)}, {0x97, spritesAttributesMake(0, 1, 0, 0)}, {0x96, spritesAttributesMake(0, 1, 0, 0)}},
    {{0x89, spritesAttributesMake(0, 1, 0, 0)}, {0x88, spritesAttributesMake(0, 1, 0, 0)}, {0x99, spritesAttributesMake(0, 1, 0, 0)}, {0x98, spritesAttributesMake(0, 1, 0, 0)}},
    
    // Run Right
    {{0x8A, spritesAttributesMake(0, 0, 0, 0)}, {0x8B, spritesAttributesMake(0, 0, 0, 0)}, {0x9A, spritesAttributesMake(0, 0, 0, 0)}, {0x9B, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x8C, spritesAttributesMake(0, 0, 0, 0)}, {0x8D, spritesAttributesMake(0, 0, 0, 0)}, {0x9C, spritesAttributesMake(0, 0, 0, 0)}, {0x9D, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x8E, spritesAttributesMake(0, 0, 0, 0)}, {0x8F, spritesAttributesMake(0, 0, 0, 0)}, {0x9E, spritesAttributesMake(0, 0, 0, 0)}, {0x9F, spritesAttributesMake(0, 0, 0, 0)}},
    {{0x8C, spritesAttributesMake(0, 0, 0, 0)}, {0x8D, spritesAttributesMake(0, 0, 0, 0)}, {0x9C, spritesAttributesMake(0, 0, 0, 0)}, {0x9D, spritesAttributesMake(0, 0, 0, 0)}},
    
    // Run Left
    {{0x8B, spritesAttributesMake(0, 1, 0, 0)}, {0x8A, spritesAttributesMake(0, 1, 0, 0)}, {0x9B, spritesAttributesMake(0, 1, 0, 0)}, {0x9A, spritesAttributesMake(0, 1, 0, 0)}},
    {{0x8D, spritesAttributesMake(0, 1, 0, 0)}, {0x8C, spritesAttributesMake(0, 1, 0, 0)}, {0x9D, spritesAttributesMake(0, 1, 0, 0)}, {0x9C, spritesAttributesMake(0, 1, 0, 0)}},
    {{0x8F, spritesAttributesMake(0, 1, 0, 0)}, {0x8E, spritesAttributesMake(0, 1, 0, 0)}, {0x9F, spritesAttributesMake(0, 1, 0, 0)}, {0x9E, spritesAttributesMake(0, 1, 0, 0)}},
    {{0x8D, spritesAttributesMake(0, 1, 0, 0)}, {0x8C, spritesAttributesMake(0, 1, 0, 0)}, {0x9D, spritesAttributesMake(0, 1, 0, 0)}, {0x9C, spritesAttributesMake(0, 1, 0, 0)}},
    
    // Pop Up
    {{0xC4, spritesAttributesMake(0, 0, 0, 0)}, {0xC5, spritesAttributesMake(0, 0, 0, 0)}, {0xD4, spritesAttributesMake(0, 0, 0, 0)}, {0xD5, spritesAttributesMake(0, 0, 0, 0)}},
    
    // Pop Down
    {{0xC6, spritesAttributesMake(0, 0, 0, 0)}, {0xC7, spritesAttributesMake(0, 0, 0, 0)}, {0xD6, spritesAttributesMake(0, 0, 0, 0)}, {0xD7, spritesAttributesMake(0, 0, 0, 0)}},
    
    // Cry
    {{0xC8, spritesAttributesMake(0, 0, 0, 0)}, {0xC9, spritesAttributesMake(0, 0, 0, 0)}, {0xD8, spritesAttributesMake(0, 0, 0, 0)}, {0xD9, spritesAttributesMake(0, 0, 0, 0)}},
    {{0xCA, spritesAttributesMake(0, 0, 0, 0)}, {0xCB, spritesAttributesMake(0, 0, 0, 0)}, {0xDA, spritesAttributesMake(0, 0, 0, 0)}, {0xDB, spritesAttributesMake(0, 0, 0, 0)}},
};

// ===
// Variables
// ===
#define heroMovementNone 0x00
#define heroMovementLeft 0x01
#define heroMovementRight 0x02
#define heroMovementUp 0x04
#define heroMovementDown 0x08

#define heroSpriteFramesRunDownStart 2
#define heroSpriteFramesRunUpStart 6
#define heroSpriteFramesRunRightStart 10
#define heroSpriteFramesRunLeftStart 14
#define heroSpriteFramesPopUp 18
#define heroSpriteFramesPopDown 19
#define heroSpriteFramesCryStart 20

GBUInt8 heroState;
GBUInt8 heroTimer;
GBUInt8 heroTileX;
GBUInt8 heroTileY;
GBUInt8 heroX;
GBUInt8 heroY;
GBUInt8 movementDirection;
GBUInt8 movementSteps;
GBUInt8 bufferedMovementDirection;
GBBool bufferedPop;

// ===
// Private API
// ===
void _updateHeroState() {
    if(movementDirection == heroMovementNone) {
        heroTimer--;
        
        if(heroTimer == 0) {
            heroTimer = 20;
            if(heroState) {
                heroState = 0;
            } else {
                heroState = 1;
            }
        }
    } else if(movementDirection == heroMovementDown) {
        heroState = heroSpriteFramesRunDownStart + (4 - ((movementSteps + 1) >> 1));
    } else if(movementDirection == heroMovementRight) {
        heroState = heroSpriteFramesRunRightStart + (4 - ((movementSteps + 1) >> 1));
    } else if(movementDirection == heroMovementLeft) {
        heroState = heroSpriteFramesRunLeftStart + (4 - ((movementSteps + 1) >> 1));
    } else if(movementDirection == heroMovementUp) {
        heroState = heroSpriteFramesRunUpStart + (4 - ((movementSteps + 1) >> 1));
    }
}

// ===
// Public API
// ===
void heroInit() {
    heroState = 0;
    heroTimer = 20;
    heroX = 80;
    heroY = 78;
    heroTileX = 5;
    heroTileY = 3;
    movementDirection = heroMovementNone;
    movementSteps = 0;
    bufferedPop = false;
    bufferedMovementDirection = heroMovementNone;
}

void heroUpdate() {
    GBUInt8 mapCollision;
    
    _updateHeroState();
    
    if(movementDirection != heroMovementNone) {
        if(gbJoypadPressedSinceLastUpdate & gbJoypadRight) {
            bufferedMovementDirection = heroMovementRight;
            bufferedPop = false;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadUp) {
            bufferedMovementDirection = heroMovementUp;
            bufferedPop = false;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadLeft) {
            bufferedMovementDirection = heroMovementLeft;
            bufferedPop = false;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadDown) {
            bufferedMovementDirection = heroMovementDown;
            bufferedPop = false;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadA) {
            bufferedMovementDirection = heroMovementNone;
            bufferedPop = true;
        }
    }
    
    switch(movementDirection) {
    case heroMovementNone:
        movementSteps = 8;
        if(bufferedMovementDirection != heroMovementNone) {
            movementDirection = bufferedMovementDirection;
            bufferedMovementDirection = heroMovementNone;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadRight) {
            movementDirection = heroMovementRight;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadUp) {
            movementDirection = heroMovementUp;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadLeft) {
            movementDirection = heroMovementLeft;
        } else if(gbJoypadPressedSinceLastUpdate & gbJoypadDown) {
            movementDirection = heroMovementDown;
        } else if((gbJoypadPressedSinceLastUpdate & gbJoypadA) || bufferedPop) {
            if(mapCollisionAt(heroTileX, heroTileY + 1) == mapCollisionBelt && bubblesPop(heroTileY + 1, heroTileX)) {
                soundPlayBubblePop();
                heroState = heroSpriteFramesPopDown;
                heroTimer = 20;
            } else if(mapCollisionAt(heroTileX, heroTileY - 1) == mapCollisionBelt && bubblesPop(heroTileY - 1, heroTileX)) {
                soundPlayBubblePop();
                heroState = heroSpriteFramesPopUp;
                heroTimer = 20;
            }
            bufferedPop = false;
        }
        
        if(movementDirection == heroMovementUp) {
            mapCollision = mapCollisionAt(heroTileX, heroTileY - 1);
            if(mapCollision) {
                movementDirection = heroMovementNone;
                
                if(mapCollision == mapCollisionBelt && bubblesPop(heroTileY - 1, heroTileX)) {
                    soundPlayBubblePop();
                    heroState = heroSpriteFramesPopUp;
                    heroTimer = 20;
                } else {
                    soundPlayHeroWallBonk();
                }
            } else {
                heroTileY--;
                soundPlayHeroMove();
            }
        } else if(movementDirection == heroMovementDown) {
            mapCollision = mapCollisionAt(heroTileX, heroTileY + 1);
            if(mapCollision) {
                movementDirection = heroMovementNone;
                
                if(mapCollision == mapCollisionBelt && bubblesPop(heroTileY + 1, heroTileX)) {
                    soundPlayBubblePop();
                    heroState = heroSpriteFramesPopDown;
                    heroTimer = 20;
                } else {
                    soundPlayHeroWallBonk();
                }
            } else {
                heroTileY++;
                soundPlayHeroMove();
            }
        } else if(movementDirection == heroMovementLeft) {
            mapCollision = mapCollisionAt(heroTileX - 1, heroTileY);
            if(mapCollision) {
                movementDirection = heroMovementNone;
                soundPlayHeroWallBonk();
            } else {
                heroTileX--;
                soundPlayHeroMove();
            }
        } else if(movementDirection == heroMovementRight) {
            mapCollision = mapCollisionAt(heroTileX + 1, heroTileY);
            if(mapCollision) {
                movementDirection = heroMovementNone;
                soundPlayHeroWallBonk();
            } else {
                heroTileX++;
                soundPlayHeroMove();
            }
        }
        
        break;
    case heroMovementDown:
        movementSteps--;
        heroY+=2;
        break;
    case heroMovementUp:
        movementSteps--;
        heroY-=2;
        break;
    case heroMovementLeft:
        movementSteps--;
        heroX-=2;
        break;
    case heroMovementRight:
        movementSteps--;
        heroX+=2;
        break;
    }
    
    spritesWriteFirstOAMIndex = spritesHeroIndex;
    spritesWriteX = heroX;
    spritesWriteY = heroY;
    
    spritesWriteAttributes = heroSpriteFrames[heroState];
    
    spritesWrite2x2();
    
    if(movementSteps == 0) {
        movementDirection = heroMovementNone;
    }
}

void heroUpdateMiss(GBUInt8 state) {
    spritesWriteFirstOAMIndex = spritesHeroIndex;
    spritesWriteX = heroX;
    spritesWriteY = heroY;
    spritesWriteAttributes = heroSpriteFrames[heroSpriteFramesCryStart + state];
    
    spritesWrite2x2();
}
