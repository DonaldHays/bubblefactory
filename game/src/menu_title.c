#include <string.h>
#include "menu_title.h"
#include "gb.h"
#include "text.h"
#include "data_gfx_logo.h"
#include "data_strings.h"
#include "main.h"
#include "palette.h"
#include "rand.h"
#include "save.h"

// ===
// Definitions
// ===
#define menuTitleStateLoading 1
#define menuTitleStateActive 2
#define menuTitleStateExiting 3

// ===
// Private Variables
// ===
GBUInt8 _menuTitleState;
GBUInt8 _menuTitleStateTimer;

// ===
// Public API
// ===
void menuTitleInit() {
    GBUInt8 x, y;
    
    _menuTitleState = menuTitleStateLoading;
    _menuTitleStateTimer = 0;
    
    textLoadFont();
    textClearScreen();
    textDrawString(stringPressStart, stringPressStartLength, 5, 12);
    textDrawString(stringWebAddress, stringWebAddressLength, 3, 15);
    textDrawString(stringTwitterHandle, stringTwitterHandleLength, 2, 16);
    
    memcpy(gbTileMemory + 64 * 16, logo, logoLength);
    
    for(y = 0; y != 8; y++) {
        for(x = 0; x != 16; x++) {
            gbTileMap0[(x + 2) + (y + 2) * 32] = x + (y + 4) * 16;
        }
    }
    
    saveRead();
    if(saveNormalHighScore >= 1000 && saveHardHighScore >= 1000) {
        *(gbTileMap0 + 6 + (1 * 32)) = 0x3F;
        *(gbTileMap0 + 8 + (1 * 32)) = 0x3F;
        *(gbTileMap0 + 10 + (1 * 32)) = 0x3F;
        *(gbTileMap0 + 12 + (1 * 32)) = 0x3F;
        *(gbTileMap0 + 14 + (1 * 32)) = 0x3F;
        
        *(gbTileMap0 + 6 + (10 * 32)) = 0x3F;
        *(gbTileMap0 + 8 + (10 * 32)) = 0x3F;
        *(gbTileMap0 + 10 + (10 * 32)) = 0x3F;
        *(gbTileMap0 + 12 + (10 * 32)) = 0x3F;
        *(gbTileMap0 + 14 + (10 * 32)) = 0x3F;
    }
}

void menuTitleUpdate() {
    switch(_menuTitleState) {
    case menuTitleStateLoading:
        paletteSetLevel(_menuTitleStateTimer);
        _menuTitleStateTimer++;
        if(_menuTitleStateTimer == 3) {
            _menuTitleState = menuTitleStateActive;
        }
        
        break;
    case menuTitleStateActive:
        random();
        paletteSetLevel(3);
        if(gbJoypadPressedSinceLastUpdate & (gbJoypadStart | gbJoypadA)) {
            _menuTitleState = menuTitleStateExiting;
        }
        
        break;
    case menuTitleStateExiting:
        paletteSetLevel(_menuTitleStateTimer);
        _menuTitleStateTimer--;
        if(_menuTitleStateTimer == 0) {
            mainBeginGameMenu();
        }
        
        break;
    default:
        gbLogUInt8(_menuTitleState);
        gbFatalError("unrecognized state");
    }
}
