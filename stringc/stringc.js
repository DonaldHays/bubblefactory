"use strict";

const path = require("path");
const fs = require("fs");
const commander = require("commander");
const formatter = require("./formatter");

commander
  .usage("[options] <map_file> <in_file> <out_file>")
  .parse(process.argv);

if(commander.args.length != 3) {
  console.error("must provide a map, input, and output file");
  process.exit(1);
}

const mapFilePath = path.resolve(commander.args[0]);
const inputFilePath = path.resolve(commander.args[1]);
const outputFilePath = path.resolve(commander.args[2]);
const outputHeaderPath = outputFilePath.substr(0, outputFilePath.length - path.extname(outputFilePath).length) + ".h";

const mapData = JSON.parse(fs.readFileSync(mapFilePath));
const inputData = JSON.parse(fs.readFileSync(inputFilePath));

const generated = {};

for (let key in inputData) {
  if (inputData.hasOwnProperty(key)) {
    const inputString = inputData[key];
    const buffer = Buffer.alloc(inputString.length + 1, 0xff);
    for (let index = 0; index < inputString.length; index++) {
      const character = inputString[index];
      if(mapData["characters"][character] !== undefined) {
        buffer[index] = mapData["characters"][character];
      } else {
        buffer[index] = mapData["unknown"];
      }
    }
    generated[key] = buffer;
  }
}

function buildHeader() {
  let output = [];
  
  output.push("// IMPORTANT: Tool-generated file. Do not modify.");
  output.push("");
  
  output.push(`#ifndef strings_h`);
  output.push(`#define strings_h`);
  output.push("");
  
  for (let key in generated) {
    if (generated.hasOwnProperty(key)) {
      const element = generated[key];
      output.push(`extern const unsigned char ${key}[];`);
      output.push(`#define ${key}Length ${element.length - 1}`);
      output.push("");
    }
  }
  
  output.push("#endif");
  output.push("");
  
  output = output.join("\n");
  
  fs.writeFileSync(outputHeaderPath, output);
}

function buildImplementation() {
  let output = [];
  
  output.push("// IMPORTANT: Tool-generated file. Do not modify.");
  output.push("");
  
  output.push(`#include "${path.basename(outputHeaderPath)}"`);
  output.push("");
  
  for (let key in generated) {
    if (generated.hasOwnProperty(key)) {
      const element = generated[key];
      const hex = [];
      for(let index = 0; index < element.length; index++) {
        hex.push("0x" + formatter.toHex(element[index]));
      }
      output.push(`const unsigned char ${key}[] = { ${hex.join(",")} };`);
      output.push("");
    }
  }
  
  output = output.join("\n");
  
  fs.writeFileSync(outputFilePath, output);
}

buildHeader();
buildImplementation();
