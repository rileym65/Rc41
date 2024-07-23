#include "header.h"

int Fs(byte n) {
  int    flag;
  n = GetPost(n);
  if (errFlag) return 0;
  if (n >= 56) {
    Message("NONEXISTENT");
    Error();
    return 0;
    }
  flag = FlagSet(n);
  return flag;
  }

