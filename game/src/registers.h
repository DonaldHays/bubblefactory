#ifndef registers_h
#define registers_h

#include "types.h"

/** A pointer to a `GBUInt8` in memory. */
#define GBRegister volatile GBUInt8 *

#define gbTileMemory ((GBRegister)0x8000)
#define gbTileMap0 ((GBRegister)0x9800)
#define gbTileMap1 ((GBRegister)0x9C00)
#define gbSRAM ((GBRegister)0xA000)

#define gbSRAMEnableRegister ((GBRegister)0x0000)
#define gbROMSelectRegister ((GBRegister)0x2000)
#define gbLCDControlRegister ((GBRegister)0xFF40)
#define gbLCDStatusRegister ((GBRegister)0xFF41)
#define gbBackgroundScrollYRegister ((GBRegister)0xFF42)
#define gbBackgroundScrollXRegister ((GBRegister)0xFF43)
#define gbLCDYCoordinateRegister ((GBRegister)0xFF44)
#define gbLCDYCoordinateCompareRegister ((GBRegister)0xFF45)
#define gbWindowScrollYRegister ((GBRegister)0xFF4A)
#define gbWindowScrollXRegister ((GBRegister)0xFF4B)
#define gbBackgroundPaletteRegister ((GBRegister)0xFF47)
#define gbObject0PaletteRegister ((GBRegister)0xFF48)
#define gbObject1PaletteRegister ((GBRegister)0xFF49)
#define gbInterruptFlagRegister ((GBRegister)0xFF0F)
#define gbTone1SweepRegister ((GBRegister)0xFF10)
#define gbTone1PatternRegister ((GBRegister)0xFF11)
#define gbTone1VolumeRegister ((GBRegister)0xFF12)
#define gbTone1FrequencyLowRegister ((GBRegister)0xFF13)
#define gbTone1TriggerRegister ((GBRegister)0xFF14)
#define gbTone2PatternRegister ((GBRegister)0xFF16)
#define gbTone2VolumeRegister ((GBRegister)0xFF17)
#define gbTone2FrequencyLowRegister ((GBRegister)0xFF18)
#define gbTone2TriggerRegister ((GBRegister)0xFF19)
#define gbNoiseLengthRegister ((GBRegister)0xFF20)
#define gbNoiseVolumeRegister ((GBRegister)0xFF21)
#define gbNoisePolynomialRegister ((GBRegister)0xFF22)
#define gbNoiseTriggerRegister ((GBRegister)0xFF23)
#define gbVolumeRegister ((GBRegister)0xFF24)
#define gbAudioTerminalRegister ((GBRegister)0xFF25)
#define gbActiveInterruptsRegister ((GBRegister)0xFFFF)

#endif
