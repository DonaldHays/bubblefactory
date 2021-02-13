# Bubble Factory

A Game & Watch-inspired game for Game Boy. Binary download and browser-playable version available [on my website](http://donaldhays.com/projects/bubble-factory/).

## Building

I built this project on macOS. The instructions should be pretty easy to follow from most UNIX-y operating systems. Windows users may have some troubles with the build scripts.

The build pipeline has a dependency on [node.js](http://nodejs.org). You'll need to install it.

### Dependencies
`cd` into `ihx2gb/` and run `npm install`.

`cd` into `img2gb/` and run `npm install`.

`cd` into `stringc/` and run `npm install`.

Download [SDCC](http://sdcc.sourceforge.net) and place the `sdcc/` folder in the root directory alongside `ihx2gb/` and `img2gb/`, such that from the directory containing `ihx2gb/` you could navigate to `sdcc/bin/sdcc`.
Also download [RGBDS](https://github.com/gbdev/rgbds/) and placeit in the `rgbds/` folder.

Successfully tested with SDCC 4.0.0 and RGBGFX 0.4.2

The makefile also relies on GNU coreutils and xxd being installed.

### Building the Game
`cd` into `game/` and run `make` or `make debug`.

If you have sdcc and rgbds globally installed you can also run `make -C game/ SDCCBIN= RGBDSDIR=`.