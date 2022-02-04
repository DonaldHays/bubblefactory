SDCCBIN = 
CC = $(SDCCBIN)sdcc
ASMC = $(SDCCBIN)sdasgb
MKROM = $(SDCCBIN)makebin
EMU = sameboy
NODE = node
CFLAGS = -c -msm83
ASMFLAGS = -plosgffjw
LINKFLAGS = -msm83 --no-std-crt0 --data-loc 0xc0a0

GFXS = $(notdir $(shell find data/gfx -name '*.png'))
GFXSRC = $(patsubst %.png,data_gfx_%.c,$(GFXS))
ASMS = crt0.s
SRCS := $(notdir $(shell find src -name '*.c')) $(GFXSRC) data_strings.c
OBJS = $(SRCS:.c=.o)

SRCFILES = $(patsubst %.c,src/%.c,$(SRCS))
OBJFILES = $(patsubst %.s,obj/%.rel,$(ASMS)) $(patsubst %.c,obj/%.rel,$(SRCS))

.PHONY: build debug run clean

build: obj/dependencies bin/BubbleFactory.gb

debug: CFLAGS += -DDEBUG
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

bin/BubbleFactory.gb: obj/game.ihx | bin/
	$(MKROM) -Z -yn BUBBLEFACT -yk DH -yt 0x1B -ya 1 -yS -yp0x014C=1 $< $@

obj/game.ihx: $(OBJFILES) | obj/
	$(CC) $(LINKFLAGS) $^ -o $@

obj/%.rel: src/%.c | obj/
	$(CC) $(CFLAGS) $< -o $@

obj/%.rel: src/%.s | obj/
	$(ASMC) $(ASMFLAGS) $@ $<

%/:
	@mkdir -p $@

run: build
	$(EMU) bin/BubbleFactory.gb

clean:
	$(RM) -rf src/data_*
	$(RM) -rf obj
	$(RM) -rf bin
