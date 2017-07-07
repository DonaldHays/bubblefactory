"use strict";

const fs = require("fs");
const path = require("path");
const formatter = require("./formatter");

function processHeader(filePath, bytes, options) {
  let output = [];
  output.push("// IMPORTANT: Tool-generated file. Do not modify.");
  output.push("");
  
  output.push(`#ifndef image_${options["name"]}_h`);
  output.push(`#define image_${options["name"]}_h`);
  output.push("");
  
  if(options["bank"] !== undefined) {
    output.push(`#define ${options["name"]}Bank ${options["bank"]}`);
    output.push("");
  }
  
  output.push(`/** Game Boy-format tile data. */`);
  output.push(`extern const unsigned char ${options["name"]}[];`);
  output.push("");
  
  output.push(`/** The number of tiles in \`${options["name"]}\`. */`);
  output.push(`#define ${options["name"]}Count ${bytes.length / 16 }`);
  output.push("");
  
  output.push(`/** The number of bytes in \`${options["name"]}\`. */`);
  output.push(`#define ${options["name"]}Length ${bytes.length }`);
  output.push("");
  
  output.push("#endif");
  output.push("");
  
  output = output.join("\n");
  fs.writeFileSync(filePath, output);
}

function processImplementation(filePath, bytes, options) {
  let output = [];
  output.push("// IMPORTANT: Tool-generated file. Do not modify.");
  output.push("");
  
  const fileName = path.basename(filePath);
  output.push(`#include "${fileName.substr(0, fileName.length - path.extname(fileName).length) + ".h"}"`);
  output.push("");
  
  if(options["bank"] !== undefined) {
    output.push(`#pragma bank ${options["bank"]}`);
    output.push("");
  }
  
  output.push(`const unsigned char ${options["name"]}[] = {`);
  let index = 0;
  while(index < bytes.length) {
    let elements = [];
    for(let counter=0; counter<16 && index < bytes.length; counter++, index++) {
      elements.push("0x" + formatter.toHex(bytes[index]));
    }
    output.push(`  ${elements.join(",")}${index == bytes.length ? "" : ","}`);
  }
  output.push("};");
  output.push("");
  
  output = output.join("\n");
  fs.writeFileSync(filePath, output);
}

function process(filePath, bytes, options) {
  const headerFilePath = filePath.substr(0, filePath.length - path.extname(filePath).length) + ".h";
  
  processHeader(headerFilePath, bytes, options);
  processImplementation(filePath, bytes, options);
}

module.exports = process;
