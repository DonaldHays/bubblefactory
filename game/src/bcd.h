#ifndef bcd_h
#define bcd_h

#include "gb.h"

/**
 * Fills `buffer` with a one-digit-per-byte BCD representation of `value`.
 * The buffer must be 4 bytes long. Results are undefined if `value` > 9,999.
 */
void bcdMake(GBUInt8 * buffer, GBUInt16 value);

#endif
