SDCCBIN = 
CC = $(SDCCBIN)sdcc
AS = $(SDCCBIN)sdasgb
MKROM = $(SDCCBIN)makebin
# https://github.com/LIJI32/SameBoy or any other emulator
EMU = sameboy
# https://github.com/bbbbbr/romusage
ROMUSE = romusage
NODE = node
CFLAGS = -c -mgbz80
ASFLAGS = -plosgffjw
LDFLAGS = -mgbz80 --no-std-crt0 --data-loc 0xc0a0

GFXS = $(notdir $(shell find data/gfx -name '*.png'))
GFXSRC = $(patsubst %.png,data_gfx_%.c,$(GFXS))
ASMS = crt0.s
SRCS := $(notdir $(shell find src -name '*.c')) $(GFXSRC) data_strings.c
OBJS = $(SRCS:.c=.o)

SRCFILES = $(patsubst %.c,src/%.c,$(SRCS))
OBJFILES = $(patsubst %.s,obj/%.rel,$(ASMS)) $(patsubst %.c,obj/%.rel,$(SRCS))

ROM = BubbleFactory

.PHONY: build debug run clean spaceleft statistics

build: obj/dependencies bin/$(ROM).gb

debug: CFLAGS += -DDEBUG --debug
debug: LDFLAGS += -Wl-y
debug: build

src/data_strings.c: data/strings.json 
	$(NODE) ../stringc data/stringsMap.json $< $@

src/data_gfx_%.c: data/gfx/%.png
	$(NODE) ../img2gb -n $(notdir $(basename $<)) $< $@

obj/dependencies: $(SRCFILES) | obj/
	@echo "regenerate dependency file"
	@$(RM) -f obj/dependencies
	@for srcFile in $(SRCFILES) ; do \
		{ printf "obj/"; $(CC) -MM $$srcFile; } >> obj/dependencies ; \
	done

-include obj/dependencies

bin/$(ROM).gb: obj/game.ihx | bin/
	$(MKROM) -Z -yn BUBBLEFACT -yk DH -yt 0x1B -ya 1 -yS -yp0x014C=1 $< $@
	cp obj/game.sym bin/$(ROM).sym
	cp obj/game.noi bin/$(ROM).noi
	test -e obj/game.cdb && cp obj/game.cdb bin/$(ROM).cdb

obj/game.ihx: $(OBJFILES) | obj/
	$(CC) $(LDFLAGS) $^ -o $@

obj/%.rel: src/%.c | obj/
	$(CC) $(CFLAGS) $< -o $@

obj/%.rel: src/%.s | obj/
	$(AS) $(ASFLAGS) $@ $<

%/:
	@mkdir -p $@

spaceleft: build
	$(ROMUSE) bin/$(ROM).noi -g -E

statistics: build
	test -e bin/$(ROM).cdb && $(ROMUSE) bin/$(ROM).cdb -g
	$(ROMUSE) bin/$(ROM).noi -G -E -sH -a

run: build
	$(EMU) $(ROM)

clean:
	$(RM) -rf src/data_*
	$(RM) -rf obj
	$(RM) -rf bin
