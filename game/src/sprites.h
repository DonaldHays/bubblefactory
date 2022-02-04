#ifndef sprites_h
#define sprites_h

#include "gb.h"

typedef struct {
    GBUInt8 y;
    GBUInt8 x;
    GBUInt8 tileIndex;
    GBUInt8 attributes;
} SpriteAttributes;

typedef struct {
    GBUInt8 tileIndex;
    GBUInt8 attributes;
} SpriteFrameAttributes;

extern volatile SpriteAttributes * spriteAttributes;

extern volatile GBUInt8 spritesWriteFirstOAMIndex;
extern volatile GBUInt8 spritesWriteX;
extern volatile GBUInt8 spritesWriteY;
extern volatile const SpriteFrameAttributes * spritesWriteAttributes;

#define spritesHeroIndex 0
#define spritesBubblesIndex 4
#define spritesBaddiesIndex 8

/**
 * Returns a `GBUInt8` that represents attributes assignable to the
 * `attributes` field of a `SpriteAttributes` value.
 *
 * \param priority 0 for above background, 1 for behind background colors 1-3
 * \param flipX 0 for normal, 1 for horizontally mirrored
 * \param flipY 0 for normal, 1 for vertically mirrored
 * \param paletteNumber 0 for sprite palette 0, 1 for sprite palette 1
 */
#define spritesAttributesMake(priority, flipX, flipY, paletteNumber) (((priority) << 7) | ((flipX) << 5) | ((flipY) << 6) | ((paletteNumber) << 4))

void spritesInit();
void spritesWriteToOAM();
void spritesWrite2x2();
void spritesWrite1x1();

#endif
