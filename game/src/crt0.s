    .globl _main
    .globl _joypadInterruptHandler
    .globl _serialInterruptHandler
    .globl _timerInterruptHandler
    .globl _lcdInterruptHandler
    .globl _vblankInterruptHandler
    .globl _gbJoypadState

    .area _HEADER (ABS)

    ; Reset Vector
    .org 0x0000
.resetVector:
    nop
    jp .main

    ; VBlank Vector
    .org 0x0040
.vblankInterrupt:
    push hl
    ld hl, #_vblankInterruptHandler
    jp .universalInterruptHandler

    ; LCD Vector
    .org 0x0048
.lcdInterrupt:
    push hl
    ld hl, #_lcdInterruptHandler
    jp .universalInterruptHandler

    ; Timer Vector
    .org 0x0050
.timerInterrupt:
    push hl
    ld hl, #_timerInterruptHandler
    jp .universalInterruptHandler

    ; Serial Vector
    .org 0x0058
.serialInterrupt:
    push hl
    ld hl, #_serialInterruptHandler
    jp .universalInterruptHandler

    ; Joypad Vector
    .org 0x0060
.joypadInterrupt:
    push hl
    ld hl, #_joypadInterruptHandler
    jp .universalInterruptHandler

    ; Start Vector
    .org 0x0100
    nop
    jp .main

    ; System Main
    .org 0x0150
.main:
    di
    ld sp, #0xE000
    
    ; initialize gamepad to 0
    ld a, #0
    ld (_gbJoypadState), a
    
    ; install dma handler
    ld c, #(.endOAMDMA - .oamDMA)
    ld de, #0xFF80
    ld hl, #.oamDMA
.installOAMDMALoop:
    ld a, c
    or a
    jr z, .endInstallOAMDMALoop
    
    ld a, (hl+)
    ld (de), a
    inc de
    
    dec c
    jr .installOAMDMALoop
.endInstallOAMDMALoop:
    
    call _main
.exit:
    halt
    jr .exit

    .area _HOME

.oamDMA:
    ld a, #0xc0
    ldh (#0xff46), a
    ld a, #0x28
.oamDMAWait:
    dec a
    jr nz, .oamDMAWait
    ret
.endOAMDMA:

.universalInterruptHandler:
    push af
    push bc
    push de

    ; if *hl == 0, no handler installed, so exit handler
    ld a, (hl+)
    or (hl)
    jr z, .universalInterruptHandlerEnd

    ; hl = *hl
    ld a, (hl-)
    ld l, (hl)
    ld h, a

    ; call hl
    call .universalInterruptHandlerCall

.universalInterruptHandlerEnd:
    pop de
    pop bc
    pop af
    pop hl
    reti

.universalInterruptHandlerCall:
    jp (hl)
