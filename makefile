.PHONY: build debug tools run clean

build: tools
	$(MAKE) -C game/ $@

debug: tools
	$(MAKE) -C game/ $@

run: tools
	$(MAKE) -C game/ $@

clean:
	$(MAKE) -C game/ $@
	$(RM) -rf img2gb/node_modules stringc/node_modules

tools: img2gb/node_modules stringc/node_modules

%/node_modules:
	cd $* && npm install