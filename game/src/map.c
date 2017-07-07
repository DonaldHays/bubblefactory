#include <string.h>
#include "map.h"
#include "data_gfx_tiles.h"
#include "bcd.h"
#include "memory.h"
#include "bubbles.h"
#include "game.h"
#include "sound.h"
#include "save.h"

// ===
// Constant Data
// ===
const GBUInt8 mapCollisionData[] = {
    1,1,1,2,2,1,2,2,1,1,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    1,1,1,2,2,1,2,2,1,1,1,0,0,0,0,0
};

const GBUInt8 initialMap[] = {
    0x20,0x20,0x20,0x20,0x06,0x07,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x08,0x09,0x0a,0x20,0x20,0x20,0x20,
    0x30,0x30,0x30,0x30,0x08,0x09,0x0a,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x30,0x30,0x30,0x30,
    0x01,0x01,0x02,0x46,0x47,0x60,0x61,0x62,0x63,0x4a,0x4b,0x60,0x61,0x62,0x63,0x4a,0x4b,0x00,0x01,0x01,
    0x03,0x11,0x12,0x56,0x57,0x70,0x71,0x72,0x73,0x5a,0x5b,0x70,0x71,0x72,0x73,0x5a,0x5b,0x10,0x11,0x04,
    0x41,0x15,0x17,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x16,0x15,0x18,0x40,
    0x51,0x1d,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x45,0x55,0x05,0x15,0x05,0x15,0x05,0x15,0x50,
    0x41,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x1c,0x40,
    0x51,0x19,0x15,0x1b,0x15,0x1a,0x15,0x1a,0x15,0x1b,0x15,0x1a,0x15,0x1a,0x15,0x1b,0x15,0x1a,0x15,0x50,
    0x13,0x01,0x02,0x15,0x1c,0x00,0x01,0x01,0x02,0x15,0x1c,0x00,0x01,0x01,0x02,0x15,0x1c,0x00,0x01,0x14,
    0x03,0x11,0x12,0x1d,0x15,0x10,0x11,0x0d,0x12,0x1d,0x15,0x10,0x11,0x11,0x12,0x1d,0x15,0x10,0x11,0x04,
    0x41,0x15,0x17,0x15,0x16,0x15,0x44,0x15,0x17,0x15,0x16,0x15,0x17,0x15,0x17,0x15,0x16,0x15,0x18,0x40,
    0x51,0x1d,0x15,0x05,0x15,0x05,0x54,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x50,
    0x41,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x1c,0x40,
    0x51,0x19,0x15,0x1b,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x05,0x15,0x1a,0x15,0x50,
    0x13,0x01,0x02,0x4a,0x4b,0x60,0x61,0x62,0x63,0x4a,0x4b,0x60,0x61,0x62,0x63,0x46,0x47,0x00,0x01,0x14,
    0x11,0x11,0x12,0x5a,0x5b,0x70,0x71,0x72,0x73,0x5a,0x5b,0x70,0x71,0x72,0x73,0x56,0x57,0x10,0x11,0x11,
    0x0e,0x0f,0x0e,0x0f,0x0e,0x0f,0x0b,0x0c,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
    0x1e,0x1f,0x1e,0x1f,0x1e,0x1f,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05
};

const GBUInt8 tileAnimations1[4][16] = {
    {0x46,0x47,0x60,0x61,0x62,0x63,0x4c,0x4d,0x60,0x61,0x62,0x63,0x4a,0x4b,0x00,0x00},
    {0x48,0x49,0x6C,0x6D,0x6E,0x6F,0x4a,0x4b,0x6C,0x6D,0x6E,0x6F,0x4c,0x4d,0x00,0x00},
    {0x46,0x47,0x68,0x69,0x6A,0x6B,0x4c,0x4d,0x68,0x69,0x6A,0x6B,0x4a,0x4b,0x00,0x00},
    {0x48,0x49,0x64,0x65,0x66,0x67,0x4a,0x4b,0x64,0x65,0x66,0x67,0x4c,0x4d,0x00,0x00},
};

const GBUInt8 tileAnimations2[4][16] = {
    {0x56,0x57,0x70,0x71,0x72,0x73,0x5c,0x5d,0x70,0x71,0x72,0x73,0x5a,0x5b,0x00,0x00},
    {0x58,0x59,0x7C,0x7D,0x7E,0x7F,0x5a,0x5b,0x7C,0x7D,0x7E,0x7F,0x5c,0x5d,0x00,0x00},
    {0x56,0x57,0x78,0x79,0x7A,0x7B,0x5c,0x5d,0x78,0x79,0x7A,0x7B,0x5a,0x5b,0x00,0x00},
    {0x58,0x59,0x74,0x75,0x76,0x77,0x5a,0x5b,0x74,0x75,0x76,0x77,0x5c,0x5d,0x00,0x00},
};

const GBUInt8 tileAnimations3[4][16] = {
    {0x4c,0x4d,0x64,0x65,0x66,0x67,0x4a,0x4b,0x64,0x65,0x66,0x67,0x48,0x49,0x00,0x00},
    {0x4a,0x4b,0x68,0x69,0x6A,0x6B,0x4c,0x4d,0x68,0x69,0x6A,0x6B,0x46,0x47,0x00,0x00},
    {0x4c,0x4d,0x6C,0x6D,0x6E,0x6F,0x4a,0x4b,0x6C,0x6D,0x6E,0x6F,0x48,0x49,0x00,0x00},
    {0x4a,0x4b,0x60,0x61,0x62,0x63,0x4c,0x4d,0x60,0x61,0x62,0x63,0x46,0x47,0x00,0x00},
};

const GBUInt8 tileAnimations4[4][16] = {
    {0x58,0x59,0x74,0x75,0x76,0x77,0x5a,0x5b,0x74,0x75,0x76,0x77,0x58,0x59,0x00,0x00},
    {0x56,0x57,0x78,0x79,0x7A,0x7B,0x5c,0x5d,0x78,0x79,0x7A,0x7B,0x56,0x57,0x00,0x00},
    {0x58,0x59,0x7C,0x7D,0x7E,0x7F,0x5a,0x5b,0x7C,0x7D,0x7E,0x7F,0x58,0x59,0x00,0x00},
    {0x56,0x57,0x70,0x71,0x72,0x73,0x5c,0x5d,0x70,0x71,0x72,0x73,0x56,0x57,0x00,0x00},
};

// ===
// Private Variables
// ===
#define _mapAnimationTickInterval 8
#define _door0_left 1
#define _door0_right 2
#define _door1_left 4
#define _door1_right 8
#define _door2_left 16
#define _door2_right 32
#define _door3_left 64
#define _door3_right 128

GBUInt8 _mapAnimationCycle;
GBUInt8 _mapAnimationTickTime;

GBUInt16 _highScore;
GBUInt16 _score;
GBUInt8 _highScoreMap[2][4];
GBUInt8 _scoreMap[2][4];
GBBool _needsToRedrawHighScore;
GBBool _needsToRedrawScore;
GBBool _needsToRedrawMiss;
GBBool _needsToEraseMiss;
GBUInt8 *_drawMapMissStartAddress;
GBUInt8 *_eraseMapMissStartAddress;
GBUInt8 _drawnDoorState;
GBUInt8 _currentDoorState;

// ===
// Variables
// ===
GBUInt8 mapMissCount;

// ===
// Private API
// ===
void _updateNumber(GBUInt16 number, GBUInt8 map[2][4]) {
    GBUInt8 buffer[4];
    GBBool drawZero;
    int i;
    
    drawZero = false;
    bcdMake(buffer, number);
    for(i = 0; i != 4; i++) {
        if(drawZero == true || buffer[i] != 0 || i == 3) {
            drawZero = true;
            
            map[0][i] = 33 + buffer[i];
            map[1][i] = 49 + buffer[i];
        } else {
            map[0][i] = 32;
            map[1][i] = 48;
        }
    }
}

GBUInt8 _doorFlag(GBUInt8 row, GBUInt8 column) {
    GBUInt8 flag;
    
    if(column) {
        flag = 2;
    } else {
        flag = 1;
    }
    
    flag <<= (row << 1);
    
    return flag;
}

// ===
// Public API
// ===
void mapInit() {
    GBUInt8 rowIndex;
    GBUInt8 *tileMap0Address;
    const GBUInt8 *initialMapTileAddress;
    
    _mapAnimationTickTime = gameBeltMovementSpeed;
    _mapAnimationCycle = 0;
    
    _needsToRedrawMiss = false;
    _needsToEraseMiss = false;
    mapMissCount = 0;
    
    _drawnDoorState = 0;
    _currentDoorState = 0;
    
    _needsToRedrawHighScore = false;
    _needsToRedrawScore = false;
    
    mapSetScore(0);
    
    if(gameIsHardMode) {
        mapSetHighScore(saveHardHighScore);
    } else {
        mapSetHighScore(saveNormalHighScore);
    }
    
    gbROMBankSet(tilesBank);
    memcpy(gbTileMemory, tiles, tilesLength);
    
    tileMap0Address = gbTileMap0;
    initialMapTileAddress = initialMap;
    for(rowIndex = 0; rowIndex != 18; rowIndex++) {
        memcpy(tileMap0Address, initialMapTileAddress, 20);
        tileMap0Address += 32;
        initialMapTileAddress += 20;
    }
}

void mapUpdateLogic() {
    _mapAnimationTickTime--;
    
    if(_mapAnimationTickTime == 0) {
        _mapAnimationTickTime = gameBeltMovementSpeed;
        _mapAnimationCycle = (_mapAnimationCycle + 1) & 3;
    }
}

void mapUpdateGraphics() {
    // Throughout this function you'll find copious return statements. They
    // cause the function to return even before all possible dirtied tiles
    // have been updated. This is in order to ensure we finish writing tiles
    // before vblank ends. Updates to the map may take several frames to fully
    // be written to tile memory.
    
    GBUInt8 deltaDoorState;
    
    if(_needsToRedrawMiss) {
        _needsToRedrawMiss = false;
        
        *_drawMapMissStartAddress = 78;
        *(_drawMapMissStartAddress + 1) = 79;
        *(_drawMapMissStartAddress + 32) = 94;
        *(_drawMapMissStartAddress + 33) = 95;
        
        return;
    }
    
    if(_needsToEraseMiss) {
        _needsToEraseMiss = false;
        
        *_eraseMapMissStartAddress = 14;
        *(_eraseMapMissStartAddress + 1) = 15;
        *(_eraseMapMissStartAddress + 32) = 30;
        *(_eraseMapMissStartAddress + 33) = 31;
        
        return;
    }
    
    if(_needsToRedrawHighScore) {
        _needsToRedrawHighScore = false;
        
        memoryCopyLength = 4;
        memoryCopyDestinationAddress = gbTileMap0;
        memoryCopySourceAddress = _highScoreMap[0];
        memoryCopy();
        
        memoryCopyDestinationAddress = gbTileMap0 + 32;
        memoryCopySourceAddress = _highScoreMap[1];
        memoryCopy();
        
        return;
    }
    
    if(_needsToRedrawScore) {
        _needsToRedrawScore = false;
        
        memoryCopyLength = 4;
        memoryCopyDestinationAddress = gbTileMap0 + 16;
        memoryCopySourceAddress = _scoreMap[0];
        memoryCopy();
        
        memoryCopyDestinationAddress = gbTileMap0 + 48;
        memoryCopySourceAddress = _scoreMap[1];
        memoryCopy();
        
        return;
    }
    
    if(_drawnDoorState != _currentDoorState) {
        deltaDoorState = _drawnDoorState ^ _currentDoorState;
        
        if(deltaDoorState & _door0_left) {
            *(gbTileMap0 + (4 * 32) + 0) = ((_currentDoorState & _door0_left) ? 67 : 65);
            *(gbTileMap0 + (5 * 32) + 0) = ((_currentDoorState & _door0_left) ? 83 : 81);
        }
        
        if(deltaDoorState & _door0_right) {
            *(gbTileMap0 + (4 * 32) + 19) = (_currentDoorState & _door0_right ? 66 : 64);
            *(gbTileMap0 + (5 * 32) + 19) = (_currentDoorState & _door0_right ? 82 : 80);
        }
        
        if(deltaDoorState & _door1_left) {
            *(gbTileMap0 + (6 * 32) + 0) = (_currentDoorState & _door1_left ? 67 : 65);
            *(gbTileMap0 + (7 * 32) + 0) = (_currentDoorState & _door1_left ? 83 : 81);
        }
        
        if(deltaDoorState & _door1_right) {
            *(gbTileMap0 + (6 * 32) + 19) = (_currentDoorState & _door1_right ? 66 : 64);
            *(gbTileMap0 + (7 * 32) + 19) = (_currentDoorState & _door1_right ? 82 : 80);
        }
        
        if(deltaDoorState & _door2_left) {
            *(gbTileMap0 + (10 * 32) + 0) = (_currentDoorState & _door2_left ? 67 : 65);
            *(gbTileMap0 + (11 * 32) + 0) = (_currentDoorState & _door2_left ? 83 : 81);
        }
        
        if(deltaDoorState & _door2_right) {
            *(gbTileMap0 + (10 * 32) + 19) = (_currentDoorState & _door2_right ? 66 : 64);
            *(gbTileMap0 + (11 * 32) + 19) = (_currentDoorState & _door2_right ? 82 : 80);
        }
        
        if(deltaDoorState & _door3_left) {
            *(gbTileMap0 + (12 * 32) + 0) = (_currentDoorState & _door3_left ? 67 : 65);
            *(gbTileMap0 + (13 * 32) + 0) = (_currentDoorState & _door3_left ? 83 : 81);
        }
        
        if(deltaDoorState & _door3_right) {
            *(gbTileMap0 + (12 * 32) + 19) = (_currentDoorState & _door3_right ? 66 : 64);
            *(gbTileMap0 + (13 * 32) + 19) = (_currentDoorState & _door3_right ? 82 : 80);
        }
        
        _drawnDoorState = _currentDoorState;
        
        return;
    }
    
    if(_mapAnimationTickTime & 1) {
        if(_mapAnimationTickTime & 2) {
            // Top Left
            memoryCopyLength = 8;
            memoryCopyDestinationAddress = gbTileMap0 + 67;
            memoryCopySourceAddress = tileAnimations1[_mapAnimationCycle];
            memoryCopy();
            
            memoryCopyDestinationAddress = gbTileMap0 + 99;
            memoryCopySourceAddress = tileAnimations2[_mapAnimationCycle];
            memoryCopy();
            
            if(bubblesIsTopInDanger()) {
                if((_mapAnimationCycle & 1) == 0) {
                    *(gbTileMap0 + 67) = 0x2C;
                    *(gbTileMap0 + 68) = 0x2D;
                    *(gbTileMap0 + 99) = 0x3C;
                    *(gbTileMap0 + 100) = 0x3D;
                    soundPlayWarning();
                } else {
                    *(gbTileMap0 + 67) = 0x2E;
                    *(gbTileMap0 + 68) = 0x2F;
                    *(gbTileMap0 + 99) = 0x3E;
                    *(gbTileMap0 + 100) = 0x3F;
                }
            }
        } else {
            // Top Right
            memoryCopyLength = 6;
            memoryCopyDestinationAddress = gbTileMap0 + 75;
            memoryCopySourceAddress = tileAnimations1[_mapAnimationCycle] + 8;
            memoryCopy();
            
            memoryCopyDestinationAddress = gbTileMap0 + 107;
            memoryCopySourceAddress = tileAnimations2[_mapAnimationCycle] + 8;
            memoryCopy();
        }
    } else {
        if(_mapAnimationTickTime & 2) {
            // Bottom Left
            memoryCopyLength = 8;
            memoryCopyDestinationAddress = gbTileMap0 + 451;
            memoryCopySourceAddress = tileAnimations3[_mapAnimationCycle];
            memoryCopy();
            
            memoryCopyDestinationAddress = gbTileMap0 + 483;
            memoryCopySourceAddress = tileAnimations4[_mapAnimationCycle];
            memoryCopy();
        } else {
            // Bottom Right
            memoryCopyLength = 6;
            memoryCopyDestinationAddress = gbTileMap0 + 459;
            memoryCopySourceAddress = tileAnimations3[_mapAnimationCycle] + 8;
            memoryCopy();
            
            memoryCopyDestinationAddress = gbTileMap0 + 491;
            memoryCopySourceAddress = tileAnimations4[_mapAnimationCycle] + 8;
            memoryCopy();
            
            if(bubblesIsBottomInDanger()) {
                if((_mapAnimationCycle & 1) == 0) {
                    *(gbTileMap0 + 463) = 0x2C;
                    *(gbTileMap0 + 464) = 0x2D;
                    *(gbTileMap0 + 495) = 0x3C;
                    *(gbTileMap0 + 496) = 0x3D;
                    soundPlayWarning();
                } else {
                    *(gbTileMap0 + 463) = 0x2E;
                    *(gbTileMap0 + 464) = 0x2F;
                    *(gbTileMap0 + 495) = 0x3E;
                    *(gbTileMap0 + 496) = 0x3F;
                }
            }
        }
    }
}

void mapSetHighScore(GBUInt16 highScore) {
    _highScore = highScore;
    _needsToRedrawHighScore = true;
    _updateNumber(_highScore, _highScoreMap);
}

void mapSetScore(GBUInt16 score) {
    _score = score;
    _needsToRedrawScore = true;
    _updateNumber(_score, _scoreMap);
}

void mapGainMiss() {
    _needsToRedrawMiss = true;
    mapMissCount++;
    _drawMapMissStartAddress = (gbTileMap0 + 512) + ((mapMissCount - 1) * 2);
}

void mapLoseMiss() {
    if(mapMissCount == 0) {
        return;
    }
    
    _needsToEraseMiss = true;
    _eraseMapMissStartAddress = (gbTileMap0 + 512) + ((mapMissCount - 1) * 2);
    mapMissCount--;
}

void mapOpenDoor(GBUInt8 row, GBUInt8 column) {
    _currentDoorState |= _doorFlag(row, column);
}

void mapCloseDoor(GBUInt8 row, GBUInt8 column) {
    _currentDoorState &= ~_doorFlag(row, column);
}
