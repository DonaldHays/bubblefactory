#include "text.h"
#include <string.h>
#include "data_gfx_font.h"

void textLoadFont() {
    memcpy(gbTileMemory, font, fontLength);
}

void textClearScreen() {
    memset(gbTileMap0, 0x3A, 32 * 32);
}

void textDrawString(unsigned char *stringAddress, GBUInt8 length, GBUInt8 x, GBUInt8 y) {
    while(length != 0) {
        gbTileMap0[y * 32 + x] = *stringAddress;
        
        stringAddress++;
        x += 1;
        length -= 1;
    }
}
