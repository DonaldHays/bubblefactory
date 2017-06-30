#include "gb.h"
#include "sound.h"

void soundInit() {
    *gbAudioTerminalRegister = 0xFF;
}

void soundPlayHeroMove() {
    *gbTone1SweepRegister        = 0b00110110;
    *gbTone1PatternRegister      = 0b10001110;
    *gbTone1VolumeRegister       = 0b11110001;
    *gbTone1FrequencyLowRegister = 0b00001010;
    *gbTone1TriggerRegister      = 0b11000110;
}

void soundPlayHeroWallBonk() {
    *gbTone1SweepRegister        = 0b00111110;
    *gbTone1PatternRegister      = 0b10001110;
    *gbTone1VolumeRegister       = 0b11110001;
    *gbTone1FrequencyLowRegister = 0b00001010;
    *gbTone1TriggerRegister      = 0b11000100;
}

void soundPlayDoorOpen() {
    *gbTone2PatternRegister      = 0b10001110;
    *gbTone2VolumeRegister       = 0b11010001;
    *gbTone2FrequencyLowRegister = 0b00001010;
    *gbTone2TriggerRegister      = 0b11000010;
}

void soundPlayWarning() {
    *gbTone2PatternRegister      = 0b10001110;
    *gbTone2VolumeRegister       = 0b11110001;
    *gbTone2FrequencyLowRegister = 0b00001010;
    *gbTone2TriggerRegister      = 0b11000111;
}

void soundPlayBubblePop() {
    *gbNoiseLengthRegister       = 0b00000001;
    *gbNoiseVolumeRegister       = 0b11110001;
    *gbNoisePolynomialRegister   = 0b01011111;
    *gbNoiseTriggerRegister      = 0b11000000;
}

void soundPlayMiss() {
    *gbTone1SweepRegister        = 0b00111000;
    *gbTone1PatternRegister      = 0b01000010;
    *gbTone1VolumeRegister       = 0b11110000;
    *gbTone1FrequencyLowRegister = 0b00001010;
    *gbTone1TriggerRegister      = 0b11000110;
}

void soundPlayBux() {
    *gbTone1SweepRegister        = 0b00110110;
    *gbTone1PatternRegister      = 0b10001110;
    *gbTone1VolumeRegister       = 0b11110001;
    *gbTone1FrequencyLowRegister = 0b00001010;
    *gbTone1TriggerRegister      = 0b11000111;
}
