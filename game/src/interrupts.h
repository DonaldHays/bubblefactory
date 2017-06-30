#ifndef interrupts_h
#define interrupts_h

extern volatile void (*vblankInterruptHandler)();
extern volatile void (*lcdInterruptHandler)();
extern volatile void (*timerInterruptHandler)();
extern volatile void (*serialInterruptHandler)();
extern volatile void (*joypadInterruptHandler)();

#endif
