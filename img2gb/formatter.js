"use strict";

exports.toHex = function(number) {
  var string = number.toString(16).toUpperCase();
  if(string.length == 1) {
    return "0" + string;
  } else {
    return string;
  }
}

exports.toBinary = function(number) {
  var string = number.toString(2);
  while(string.length < 8) {
    string = "0" + string;
  }
  return string;
}
