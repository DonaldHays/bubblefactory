#include "gb.h"

// ===
// Public Variables
// ===
volatile void (*vblankInterruptHandler)();
volatile void (*lcdInterruptHandler)();
volatile void (*timerInterruptHandler)();
volatile void (*serialInterruptHandler)();
volatile void (*joypadInterruptHandler)();

GBJoypadState gbJoypadState;
GBJoypadState gbJoypadPressedSinceLastUpdate;
GBJoypadState gbJoypadReleasedSinceLastUpdate;

// ===
// Public API
// ===
void gbLCDDisable() {
    __asm
    
    push af
    
    ; busy wait for vblank
.lcdDisableLoop:
    ldh a, (#0xff44)
    cp a, #144
    jr nz, .lcdDisableLoop
    
    ; perform the disable
    ld hl, #0xff40
    res #7, (hl)
    
    pop af
    
    __endasm;
}

void gbLCDEnable() {
    __asm
    ld hl, #0xff40
    set #7, (hl)
    __endasm;
}

void gbSpritesDisable() {
    __asm
    ld hl, #0xff40
    res #1, (hl)
    __endasm;
}

void gbSpritesEnable() {
    __asm
    ld hl, #0xff40
    set #1, (hl)
    __endasm;
}

void gbJoypadStateUpdate() {
    GBUInt8 lastValue;
    
    lastValue = gbJoypadState;
    
    __asm
    ; Procedure from http://www.emulatronia.com/doctec/consolas/gameboy/gameboy.txt
    ; though we swapped which set of 4 bits are high vs low to match the values from
    ; the `joypad` function from GBDK.
    
    push af
    push bc
    ld c, #0
    
    ; Read first part of joypad state
    ld a, #0x20
    ldh (c), a
    
    ; Read several times to burn cycles waiting for register to update
    ; `ldh a, (c); ldh a, (c)` same amount of clocks
    ; as `ld a, (#0xff00)` but one byte less
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    cpl ; Invert so 1=on and 0=off
    and #0x0f ; Only want 4 least significant bits
    ld b, a ; Store in b
    
    ; Read second part of joypad state
    ld a, #0x10
    ldh (c), a
    
    ; Read several times to burn cycles waiting for register to update
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    ldh a, (c)
    
    cpl ; invert
    and #0x0f ; only 4 least significant bits
    swap a  ; Swap nibbles
    or b ; Merge with b
    
    ld (_gbJoypadState), a
    
    pop bc
    pop af
    
    __endasm;
    
    gbJoypadPressedSinceLastUpdate = (gbJoypadState ^ lastValue) & gbJoypadState;
    gbJoypadReleasedSinceLastUpdate = (gbJoypadState ^ lastValue) & lastValue;
}

// 8bit in a
void gbLogUInt8(GBUInt8 value) {
    (void)(value); // Suppresses unused variable warning
    
    __asm
    ld d, d
    jr .gbLogUInt8End
    .dw 0x6464
    .dw 0x0000
    .strz "0x%a%"
.gbLogUInt8End:
    __endasm;
}

// 16bit in de
void gbLogUInt16(GBUInt16 value) {
    (void)(value); // Suppresses unused variable warning
    
    __asm
    ld d, d
    jr .gbLogUInt16End
    .dw 0x6464
    .dw 0x0000
    .strz "0x%de%"
.gbLogUInt16End:
    __endasm;
}
