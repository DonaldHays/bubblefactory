#include "sprites.h"
#include "data_gfx_sprites.h"
#include <string.h>

volatile SpriteAttributes * spriteAttributes;

volatile GBUInt8 spritesWriteFirstOAMIndex;
volatile GBUInt8 spritesWriteX;
volatile GBUInt8 spritesWriteY;
volatile const SpriteFrameAttributes * spritesWriteAttributes;

GBUInt8 tempAnimationPhase;
GBUInt8 tempAnimationCount;

// ===
// Public API
// ===
void spritesInit() {
    GBUInt8 index;
    
    spriteAttributes = (SpriteAttributes *)0xC000;
    
    for(index = 0; index != 40; index++) {
        spriteAttributes[index].y = 0;
        spriteAttributes[index].x = 0;
        spriteAttributes[index].tileIndex = 0;
        spriteAttributes[index].attributes = spritesAttributesMake(0, 0, 0, 0);
    }
    
    memcpy(gbTileMemory + 128 * 16, sprites, spritesLength);
    
    tempAnimationCount = 25;
    tempAnimationPhase = 0;
}

void spritesWriteToOAM() {
    __asm
    call #0xFF80
    __endasm;
}

void spritesWrite2x2() {
    GBUInt8 * ptr;
    
    ptr = (GBUInt8 *)&(spriteAttributes[spritesWriteFirstOAMIndex]);
    
    *(ptr++) = spritesWriteY;
    *(ptr++) = spritesWriteX;
    *(ptr++) = spritesWriteAttributes->tileIndex;
    *(ptr++) = spritesWriteAttributes->attributes;

    spritesWriteAttributes++;
    
    *(ptr++) = spritesWriteY;
    *(ptr++) = spritesWriteX + 8;
    *(ptr++) = spritesWriteAttributes->tileIndex;
    *(ptr++) = spritesWriteAttributes->attributes;
    
    spritesWriteAttributes++;
    
    *(ptr++) = spritesWriteY + 8;
    *(ptr++) = spritesWriteX;
    *(ptr++) = spritesWriteAttributes->tileIndex;
    *(ptr++) = spritesWriteAttributes->attributes;
    
    spritesWriteAttributes++;
    
    *(ptr++) = spritesWriteY + 8;
    *(ptr++) = spritesWriteX + 8;
    *(ptr++) = spritesWriteAttributes->tileIndex;
    *(ptr) = spritesWriteAttributes->attributes;
}

void spritesWrite1x1() {
    GBUInt8 * ptr;
    
    ptr = (GBUInt8 *)&(spriteAttributes[spritesWriteFirstOAMIndex]);
    
    *(ptr++) = spritesWriteY;
    *(ptr++) = spritesWriteX;
    *(ptr++) = spritesWriteAttributes->tileIndex;
    *(ptr) = spritesWriteAttributes->attributes;
}
