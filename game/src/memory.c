#include "memory.h"

volatile const void * memoryCopySourceAddress;
volatile void * memoryCopyDestinationAddress;
volatile GBUInt8 memoryCopyLength;

void memoryCopy() {
    __asm
    
    push af
    push bc
    push de
    
    ld hl, #_memoryCopyLength
    ld c, (hl)
    
    ld hl, #_memoryCopyDestinationAddress
    ld e, (hl)
    inc hl
    ld d, (hl)
    
    ld hl, #_memoryCopySourceAddress
    ld a, (hl)
    inc hl
    ld h, (hl)
    ld l, a
    
.loop:
    ld a, c
    or a
    jr z, .endLoop
    
    ld a, (hl+)
    ld (de), a
    inc de
    dec c
    
    jr .loop
    
.endLoop:
    pop de
    pop bc
    pop af
    
    __endasm;
}
