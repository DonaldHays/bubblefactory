# Bubble Factory

A Game & Watch-inspired game for Game Boy. Binary download and browser-playable version available [on my website](http://donaldhays.com/projects/bubble-factory/).

## Building

I built this project on macOS. The instructions should be pretty easy to follow from most UNIX-y operating systems. Windows users may have some troubles with the build scripts.

The build pipeline has dependencies on [node.js](http://nodejs.org) and [SDCC](http://sdcc.sourceforge.net). You'll need to install them.

### Dependencies
`cd` into `img2gb/` and run `npm install`.

`cd` into `stringc/` and run `npm install`.

### Building the Game
`cd` into `game/` and run `make` or `make debug`.

### Building the Game and Dependencies
Just run `make`, `make debug` or `make run` in the root folder.

### Building with an SDCC Snapshot
*This is for versions of SDCC that aren't installed*
```
SDCC_HOME=/path/to/sdcc/share/sdcc/
make SDCCBIN=${SDCC_HOME}../../bin/
```