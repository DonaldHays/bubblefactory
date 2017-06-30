#include <string.h>

#include "gb.h"
#include "main.h"
#include "map.h"
#include "sprites.h"
#include "baddy.h"
#include "hero.h"
#include "rand.h"
#include "bubbles.h"
#include "game.h"
#include "sound.h"
#include "menu_title.h"
#include "menu_game.h"
#include "palette.h"
#include "save.h"

#define mainStateTitleMenu 0
#define mainStateGameMenu 1
#define mainStateGame 2

volatile GBBool hasEnteredVBlank;
GBUInt8 mainState;

void vblank();
void updateLogic();
void updateGraphics();

void main() {
    hasEnteredVBlank = false;
    
    vblankInterruptHandler = &vblank;
    
    *gbActiveInterruptsRegister = gbActiveInterruptFlagVBlank;
    
    soundInit();
    randomInit();
    saveInit();
    
    gbLCDDisable();
    spritesInit();
    gbLCDEnable();
    
    mainBeginMenu();
    
    gbSpritesEnable();
    gbInterruptsEnable();
    
    paletteSetLevel(3);
    
    while(true) {
        hasEnteredVBlank = false;
        gbHalt();
        if(hasEnteredVBlank == false) {
            continue;
        }
        
        updateGraphics();
        updateLogic();
    }
}

void mainBeginMenu() {
    mainState = mainStateTitleMenu;
    
    gbLCDDisable();
    spritesInit();
    menuTitleInit();
    gbLCDEnable();
}

void mainBeginGameMenu() {
    mainState = mainStateGameMenu;
    
    gbLCDDisable();
    spritesInit();
    menuGameInit();
    gbLCDEnable();
}

void mainBeginGame() {
    mainState = mainStateGame;
    
    gbLCDDisable();
    spritesInit();
    gameInit();
    gbLCDEnable();
}

void updateLogic() {
    gbJoypadStateUpdate();
    
    if(mainState == mainStateTitleMenu) {
        menuTitleUpdate();
    } else if(mainState == mainStateGameMenu) {
        menuGameUpdate();
    } else if(mainState == mainStateGame) {
        gameUpdate();
    }
}

void updateGraphics() {
    spritesWriteToOAM();
    if(mainState == mainStateGame) {
        mapUpdateGraphics();
    }
}

void vblank() {
    hasEnteredVBlank = true;
}
