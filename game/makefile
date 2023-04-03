CC = sdcc
ASMC = sdasgb
MAKEBIN = makebin

CFLAGS = -c -msm83
ASMFLAGS = -plosgffjw
LINKFLAGS = -msm83 --no-std-crt0 --data-loc 0xc0a0

MAKEBINFLAGS = -Z -ya 1 -yt 0x1B -yk DH -yn BUBBLEFACT -yS -yj -yp 0x014C=2

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

src/data_gfx_%.c: data/gfx/%.png
	node ../img2gb -n $(notdir $(basename $<)) $< $@

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
	$(MAKEBIN) $(MAKEBINFLAGS) $< $@
	cp obj/game.sym bin/BubbleFactory.sym

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
	rm -rf src/data_*
	rm -rf obj
	rm -rf bin
