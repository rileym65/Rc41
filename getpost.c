#include "header.h"

byte GetPost(byte n) {
  NUMBER a;
  if (n >= 0x80 && n <= 0xef) {
    a = Rcl(n & 0x7f);
    if (a.sign != 9 && a.sign != 0) {
      Message("ALPHA DATA");
      Error();
      return n;
      }
    n = ToInteger(a);
    }
  else if (n >= 0xf0) {
    a = RecallNumber(n & 0x0f);
    n = ToInteger(a);
    }
  return n;
  }

