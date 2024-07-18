#include "header.h"

int FsQc(byte n) {
  NUMBER a;
  int    flag;
  if (n >= 0x80 && n <= 0xef) {
    a = Rcl(n & 0x7f);
    if (a.sign != 9 && a.sign != 0) {
      Message("ALPHA DATA");
      Error();
      return 0;
      }
    n = ToInteger(a);
    }
  else if (n >= 0xf0) {
    a = RecallNumber(n & 0x0f);
    n = ToInteger(a);
    }
  if (n >= 30) {
    Message("NONEXISTENT");
    Error();
    return 0;
    }
  flag = FlagSet(n);
  ClearFlag(n);
  return flag;
  }

