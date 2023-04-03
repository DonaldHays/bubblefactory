#include <string.h>
#include "menu_game.h"
#include "gb.h"
#include "text.h"
#include "data_strings.h"
#include "main.h"
#include "palette.h"
#include "rand.h"
#include "save.h"
#include "bcd.h"
#include "sprites.h"
#include "game.h"

// ===
// Definitions
// ===
#define menuGameStateLoading 1
#define menuGameStateActive 2
#define menuGameStateExiting 3

#define menuGameExitDestinationTitle 1
#define menuGameExitDestinationGame 2

// ===
// Constant Data
// ===
const SpriteFrameAttributes _menuPointerAttributes = { 0xD0, spritesAttributesMake(0, 0, 0, 0) };

// ===
// Private Variables
// ===
GBUInt8 _menuGameState;
GBUInt8 _menuGameStateTimer;
GBUInt8 _menuGameExitDestination;
GBUInt8 _menuGameSelectedIndex;

// ===
// Private API
// ===
void _menuGameWriteStars(GBUInt16 score, GBUInt8 y) {
    GBUInt8 numberOfStarsWritten;
    
    numberOfStarsWritten = 0;
    
    while(numberOfStarsWritten != 5) {
        score -= 200;
        *(gbTileMap0 + 14 + numberOfStarsWritten + (y * 32)) = (score <= 0x7FFF ? 0x3F : 0x3E);
        numberOfStarsWritten++;
    }
}

// ===
// Public API
// ===
void menuGameInit() {
    GBUInt8 bcdBuffer[4];
    
    _menuGameState = menuGameStateLoading;
    _menuGameStateTimer = 0;
    _menuGameSelectedIndex = 0;
    
    textLoadFont();
    textClearScreen();
    textDrawString(stringNormalDifficulty, stringNormalDifficultyLength, 2, 5);
    textDrawString(stringHighScore, stringHighScoreLength, 2, 6);
    textDrawString(stringHardDifficulty, stringHardDifficultyLength, 2, 10);
    textDrawString(stringHighScore, stringHighScoreLength, 2, 11);
    
    saveRead();
    
    bcdMake(bcdBuffer, saveNormalHighScore);
    bcdBuffer[0] += 15;
    bcdBuffer[1] += 15;
    bcdBuffer[2] += 15;
    bcdBuffer[3] += 15;
    memcpy(gbTileMap0 + 14 + (6 * 32), bcdBuffer, 4);
    
    bcdMake(bcdBuffer, saveHardHighScore);
    bcdBuffer[0] += 15;
    bcdBuffer[1] += 15;
    bcdBuffer[2] += 15;
    bcdBuffer[3] += 15;
    memcpy(gbTileMap0 + 14 + (11 * 32), bcdBuffer, 4);
    
    _menuGameWriteStars(saveNormalHighScore, 5);
    _menuGameWriteStars(saveHardHighScore, 10);
}

void menuGameUpdate() {
    spritesWriteFirstOAMIndex = 0;
    spritesWriteX = 12;
    spritesWriteY = 56 + _menuGameSelectedIndex * 40;
    spritesWriteAttributes = &_menuPointerAttributes;
    spritesWrite1x1();
    
    switch(_menuGameState) {
    case menuGameStateLoading:
        paletteSetLevel(_menuGameStateTimer);
        _menuGameStateTimer++;
        if(_menuGameStateTimer == 3) {
            _menuGameState = menuGameStateActive;
        }
        
        break;
    case menuGameStateActive:
        random();
        paletteSetLevel(3);
        if(gbJoypadPressedSinceLastUpdate & gbJoypadB) {
            _menuGameState = menuGameStateExiting;
            _menuGameExitDestination = menuGameExitDestinationTitle;
        } else if(gbJoypadPressedSinceLastUpdate & (gbJoypadStart | gbJoypadA)) {
            _menuGameState = menuGameStateExiting;
            _menuGameExitDestination = menuGameExitDestinationGame;
        } else if(gbJoypadPressedSinceLastUpdate & (gbJoypadUp | gbJoypadDown | gbJoypadSelect)) {
            _menuGameSelectedIndex = !_menuGameSelectedIndex;
        }
        
        break;
    case menuGameStateExiting:
        paletteSetLevel(_menuGameStateTimer);
        _menuGameStateTimer--;
        if(_menuGameStateTimer == 0) {
            if(_menuGameExitDestination == menuGameExitDestinationTitle) {
                mainBeginMenu();
            } else if(_menuGameExitDestination == menuGameExitDestinationGame) {
                if(_menuGameSelectedIndex == 0) {
                    gameIsHardMode = false;
                } else {
                    gameIsHardMode = true;
                }
                mainBeginGame();
            } else {
                gbLogUInt8(_menuGameExitDestination);
                gbFatalError("unrecognized exit destination");
            }
        }
        
        break;
    default:
        gbLogUInt8(_menuGameState);
        gbFatalError("unrecognized state");
    }
}
