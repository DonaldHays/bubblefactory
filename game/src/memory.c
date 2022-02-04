#include "memory.h"

volatile GBUInt8 memoryCopyLength;

void memoryCopy(void * dest, const void * src) {
    // Suppresses unused variable warning
    (void)(dest); // in de
    (void)(src); // in bc
    __asm

    push af
    ld hl, #_memoryCopyLength
    ld a, (hl)

    ld h, b
    ld l, c

    ld c, a

    or a
    jr z, .endLoop
.loop:
    
    ld a, (hl+)
    ld (de), a
    inc de

    dec c
    jr nz, .loop
    
.endLoop:
    pop af
    
    __endasm;
}
