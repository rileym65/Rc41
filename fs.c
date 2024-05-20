#include "header.h"

int Fs(byte n) {
  NUMBER a;
  int    flag;
  if (n >= 0x80 && n <= 0xef) {
    a = Rcl(n & 0x7f);
    n = ToInteger(a);
    }
  else if (n >= 0xf0) {
    a = RecallNumber(n & 0x0f);
    n = ToInteger(a);
    }
  if (n >= 56) {
    Message("NONEXISTENT");
    return 0;
    }
  flag = FlagSet(n);
  return flag;
  }

