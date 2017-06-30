"use strict";

const PNG = require("pngjs").PNG;

function process(png, tileX, tileY, bytes) {
  for(let y = tileY * 8; y < tileY * 8 + 8; y++) {
    let byteA = 0;
    let byteB = 0;
    for(let x = tileX * 8; x < tileX * 8 + 8; x++) {
      const index = (x + y * png.width) * 4;
      
      const average = (png.data[index] + png.data[index + 1] + png.data[index + 2]) / 3;
      const bucket = 3 - Math.floor(average / 64);

      if(bucket == 1) {
        byteA |= 1 << (7 - (x - tileX * 8));
      } else if(bucket == 2) {
        byteB |= 1 << (7 - (x - tileX * 8));
      } else if(bucket == 3) {
        byteA |= 1 << (7 - (x - tileX * 8));
        byteB |= 1 << (7 - (x - tileX * 8));
      }
    }
    
    bytes.push(byteA);
    bytes.push(byteB);
  }
}

function parse(data) {
  const sourcePNG = PNG.sync.read(data);
  
  const tilesWide = sourcePNG.width / 8;
  const tilesHigh = sourcePNG.height / 8;
  const bytes = [];
  for(let tileY = 0; tileY < tilesHigh; tileY++) {
    for(let tileX = 0; tileX < tilesWide; tileX++) {
      process(sourcePNG, tileX, tileY, bytes);
    }
  }
  
  return bytes;
}

module.exports = parse;
