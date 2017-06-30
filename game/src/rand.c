#include "rand.h"

// ===
// Properties
// ===
GBUInt16 state;

// ===
// Public API
// ===
void randomInit() {
    state = 50;
}

GBUInt8 random() {
    // GBUInt8 index;
    
    // index = 0;
    // while(index != 8) {
        if(state & 0x8000) {
            state <<= 1;
            state ^= 0x8DE7;
        } else {
            state <<= 1;
        }
        
        // index++;
    // }
    
    return state & 0xFF;
}
