#include "header.h"

NUMBER AtoN(char* number) {
  int    i;
  int    p;
  int    e;
  int    dp;
  int    x;
  int    sx;
  NUMBER ret;
  ret.sign = 0;
  ret.esign = 0;
  for (i=0; i<10; i++) ret.mantissa[i] = 0;
  for (i=0; i<2; i++) ret.exponent[i] = 0;
  while (*number == ' ') number++;
  if (*number == '+') {
    ret.sign = 0;
    number++;
    }
  else if (*number == '-') {
    ret.sign = 9;
    number++;
    }
  while (*number == '0') number++;
  if (*number == '.') {
    p = 0;
    e = -1;
    number++;
    while (*number == '0') {
      e--;
      number++;
      }
    while (*number >= '0' && *number <= '9') {
      if (p < 10) {
        ret.mantissa[p++] = *number - '0';
        }
      number++;
      }
    }
  else {
    dp = 0;
    e = -1;
    p = 0;
    while ((*number >= '0' && *number <= '9') || *number == '.') {
      if (*number != '.') if (p < 10) ret.mantissa[p++] = *number - '0';
      if (*number == '.') dp = 1;
      if (dp == 0) e++;
      number++;
      }
    }
  if (*number == 'E' || *number == 'e') {
    number++;
    if (*number == '+') {
      sx = 1;
      number++;
      }
    if (*number == '-') {
      sx = -1;
      number++;
      }
    x = 0;
    while (*number >= '0' && *number <= '9') {
      x = (x * 10) + (*number - '0');
      number++;
      }
    x *= sx;
    e += x;
    }
  if (e >= 0) ret.esign = 0; else ret.esign = 9;
  if (e < 0) e = -e;
  ret.exponent[0] = e / 10;
  ret.exponent[1] = e % 10;
  return ret;
  }

