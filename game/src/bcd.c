#include "bcd.h"

void bcdMake(GBUInt8 * buffer, GBUInt16 value) {
    // A series of loops might seem slower than using / and %, but the Game
    // Boy doesn't natively support those operators, so they have to be
    // implemented in software, making this algorithm substantially faster in
    // the worst case, and nearly free for low values.
    
    buffer[0] = 0;
    while(value >= 1000) {
        value -= 1000;
        buffer[0]++;
    }
    
    buffer[1] = 0;
    while(value >= 100) {
        value -= 100;
        buffer[1]++;
    }
    
    buffer[2] = 0;
    while(value >= 10) {
        value -= 10;
        buffer[2]++;
    }
    
    buffer[3] = value;
}
