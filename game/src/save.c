#include <string.h>
#include "save.h"

// ===
// SRAM
// ===
__at (0xA000) char sramMagicIdentifier[];
__at (0xA004) GBUInt16 sramNormalHighScore;
__at (0xA006) GBUInt16 sramHardHighScore;

// ===
// Public Variables
// ===
GBUInt16 saveNormalHighScore;
GBUInt16 saveHardHighScore;

// ===
// Public API
// ===
void saveInit() {
    gbSRAMEnable();
    if(memcmp(sramMagicIdentifier, "save", 4) != 0) {
        // gbLog("battery corrupt, writing initial save ...");
        
        memcpy(sramMagicIdentifier, "save", 4);
        sramNormalHighScore = 0;
        sramHardHighScore = 0;
    }
    gbSRAMDisable();
    
    saveRead();
}

void saveRead() {
    gbSRAMEnable();
    saveNormalHighScore = sramNormalHighScore;
    saveHardHighScore = sramHardHighScore;
    gbSRAMDisable();
}

void saveWrite() {
    gbSRAMEnable();
    sramNormalHighScore = saveNormalHighScore;
    sramHardHighScore = saveHardHighScore;
    gbSRAMDisable();
}
