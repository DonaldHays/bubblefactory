CC = ../sdcc/bin/sdcc
ASMC = ../sdcc/bin/sdasgb
CFLAGS = -c -mgbz80
ASMFLAGS = -plosgff
LINKFLAGS = -mgbz80 --no-std-crt0 --data-loc 0xc0a0

GFXS = tiles.png sprites.png
ASMS = crt0.s
SRCS = data_strings.c data_gfx_tiles.c data_gfx_font.c data_gfx_sprites.c data_gfx_logo.c main.c palette.c text.c menu_title.c menu_game.c map.c bcd.c gb.c sprites.c hero.c memory.c baddy.c rand.c bubbles.c game.c sound.c save.c
OBJS = $(SRCS:.c=.o)

SRCFILES = $(patsubst %.c,src/%.c,$(SRCS))
OBJFILES = $(patsubst %.s,obj/%.rel,$(ASMS)) $(patsubst %.c,obj/%.rel,$(SRCS))

build: obj/dependencies bin/BubbleFactory.gb

debug: CFLAGS += -DDEBUG
debug: build

src/data_strings.c: data/strings.json 
	node ../stringc data/stringsMap.json $< $@

src/data_gfx_tiles.c: data/gfx/tiles.png
	node ../img2gb $< $@
	
src/data_gfx_font.c: data/gfx/font.png
	node ../img2gb -n font $< $@
	
src/data_gfx_sprites.c: data/gfx/sprites.png
	node ../img2gb -n sprites $< $@
	
src/data_gfx_logo.c: data/gfx/logo.png
	node ../img2gb -n logo $< $@

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
	node ../ihx2gb --name BUBBLEFACT --licensee DH --cartridge 9 --ram 1 $< $@

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
