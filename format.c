#include "header.h"

char* Format(NUMBER a, char* dest) {
  int i;
  int d;
  int e;
  int mode;
  int decimals;
  char *start;
  
  start = dest;

  if (a.sign >= 0xf) {
    if (a.mantissa[0] > 0) *dest++ = ((a.mantissa[1] << 4) | (a.mantissa[2]));
    if (a.mantissa[0] > 1) *dest++ = ((a.mantissa[3] << 4) | (a.mantissa[4]));
    if (a.mantissa[0] > 2) *dest++ = ((a.mantissa[5] << 4) | (a.mantissa[6]));
    if (a.mantissa[0] > 3) *dest++ = ((a.mantissa[7] << 4) | (a.mantissa[8]));
    if (a.mantissa[0] > 4) *dest++ = ((a.mantissa[9] << 4) | (a.esign));
    if (a.mantissa[0] > 5) *dest++ = ((a.exponent[0] << 4) | (a.exponent[1]));
    *dest = 0;
    return start;
    }

  if (a.sign) *dest++ = '-'; else *dest++ = ' ';
  decimals = 0;
  if (FlagSet(36)) decimals |= 8;
  if (FlagSet(37)) decimals |= 4;
  if (FlagSet(38)) decimals |= 2;
  if (FlagSet(39)) decimals |= 1;

  if ((FlagSet(40) == 0) && (FlagSet(41) == 0)) mode = 0;
  if ((FlagSet(40) == 0) && (FlagSet(41) != 0)) mode = 1;
  if ((FlagSet(40) != 0) && (FlagSet(41) == 0)) mode = 2;

  if (mode == 2 && a.exponent[0] > 0) mode = 0;

  if (mode == 2) {                                               /* FIX */
    if (a.esign != 0) {
      *dest++ = '0';
      if (decimals != 0) {
        if (FlagSet(28)) *dest++ = '.'; else *dest++ = ',';
        }
      d = 0;
      for (i=1; i<a.exponent[1]; i++) {
        if (d < decimals) {
          *dest++ = '0';
          d++;
          }
        }
      for (i=0; i<10; i++) {
        if (d < decimals) {
          *dest++ = a.mantissa[i] + '0';
          d++;
          }
        }
      }
    else {
      d = 0;
      *dest++ = a.mantissa[0] + '0';
      d++;
      for (i=0; i<a.exponent[1]; i++) {
        *dest++ = a.mantissa[i+1] + '0';
        d++;
        }
      if (decimals != 0) {
        if (FlagSet(28)) *dest++ = '.'; else *dest++ = ',';
        }
      for (i=0; i<decimals; i++) {
        if (d < 10) {
          if (d+a.exponent[1] >= 10) *dest++ = '0';
            else *dest++ = a.mantissa[d] + '0';
          d++;
          }
        }
      }
    }

  if (mode == 0) {                                               /* SCI */
    *dest++ = a.mantissa[0] + '0';
    if (decimals != 0) {
      if (FlagSet(28)) *dest++ = '.'; else *dest++ = ',';
      }
    for (i=0; i<7; i++)
      if (i < decimals) *dest++ = a.mantissa[i+1] + '0';
    for (i=0; i<7-decimals; i++)
      *dest++ = ' ';
    if (a.esign) *dest++ = '-'; else *dest++ = ' ';
    *dest++ = a.exponent[0] + '0';
    *dest++ = a.exponent[1] + '0';
    }

  if (mode == 1) {                                               /* ENG */
    e = a.exponent[0] * 10 + a.exponent[1];
    *dest++ = a.mantissa[0] + '0';
    d = 1;
    while ((e % 3) != 0) {
      *dest++ = a.mantissa[d] + '0';
      if (a.esign) e++; else e--;
      d++;
      }
    if (decimals != 0) {
      if (FlagSet(28)) *dest++ = '.'; else *dest++ = ',';
      }
    for (i=0; i<decimals; i++) {
      if (d < 9) {
        *dest++ = a.mantissa[d] + '0';
        d++;
        }
      }
    while (d < 9) { *dest++ = ' '; d++; }
    if (a.esign) *dest++ = '-'; else *dest++ = ' ';
    *dest++ = (e / 10) + '0';
    *dest++ = (e % 10) + '0';
    }

  *dest = 0;

  return start;
  }

