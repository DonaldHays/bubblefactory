SDCCBIN=../sdcc/bin/
RGBDSDIR=../rgbds/
CC = $(SDCCBIN)sdcc
ASMC = $(SDCCBIN)sdasgb
MKROM = $(SDCCBIN)makebin
RGBGFX = $(RGBDSDIR)rgbgfx
RGBFIX = $(RGBDSDIR)rgbfix
XXD = xxd
CFLAGS = -c -mgbz80
ASMFLAGS = -plosgffjw
LINKFLAGS = -mgbz80 --no-std-crt0 --data-loc 0xc0a0

GFXS = $(notdir $(shell find data/gfx -name '*.png'))
GFXSRC = $(patsubst %.png,data_gfx_%.c,$(GFXS))
ASMS = crt0.s
SRCS := $(notdir $(shell find src -name '*.c')) $(GFXSRC) data_strings.c
OBJS = $(SRCS:.c=.o)

SRCFILES = $(patsubst %.c,src/%.c,$(SRCS))
OBJFILES = $(patsubst %.s,obj/%.rel,$(ASMS)) $(patsubst %.c,obj/%.rel,$(SRCS))

build: obj/dependencies bin/BubbleFactory.gb

debug: CFLAGS += -DDEBUG
debug: build

src/data_strings.c: data/strings.json 
	node ../stringc data/stringsMap.json $< $@

data/gfx/%.2bpp: data/gfx/%.png
	$(RGBGFX) $^ -o $@

src/data_gfx_%.h: data/gfx/%.2bpp
	@echo "Generate $@"
	@echo "#ifndef image_$*_h" > $@
	@echo "#define image_$*_h" >> $@
	@echo "extern const unsigned char $*[];" >> $@
	@echo "#define $*Count ($$(($$(stat --printf="%s" "$^")/16)))" >> $@
	@echo "#define $*Length ($$(stat --printf="%s" "$^"))" >> $@
	@echo "#endif" >> $@

src/data_gfx_%.c: data/gfx/%.2bpp src/data_gfx_%.h
	@echo '#include "data_gfx_$*.h"' > $@
	@echo "const unsigned char $*[] = {" >> $@
	${XXD} -i < $< >> $@
	@echo "};" >> $@

obj/dependencies: $(SRCFILES)
	@echo "regenerate dependency file"
	@mkdir -p obj
	@rm -f obj/dependencies
	@for srcFile in $(SRCFILES) ; do \
		{ printf "obj/"; $(CC) -MM $$srcFile; } >> obj/dependencies ; \
	done

-include obj/dependencies

bin/BubbleFactory.gb: obj/game.ihx
	@mkdir -p bin
	#node ../ihx2gb --name BUBBLEFACT --licensee DH --cartridge 9 --ram 1 $< $@
	# .sym should be available in sdcc 4.1.0 with -yS
	$(MKROM) -Z -yn BUBBLEFACT -yt 9 -ya 1 $< $@
	# should be available in sdcc 4.1.0 with -yk
	$(RGBFIX) -k DH $@

obj/game.ihx: $(OBJFILES)
	@mkdir -p obj
	$(CC) $(LINKFLAGS) $^ -o $@

obj/%.rel: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

obj/%.rel: src/%.s
	@mkdir -p obj
	$(ASMC) $(ASMFLAGS) $@ $<

clean:
	rm -rf src/data_* data/gfx/*.2bpp obj bin
