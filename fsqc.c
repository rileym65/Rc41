#include "header.h"

int FsQc(byte n) {
  int    flag;
  n = GetPost(n);
  if (errFlag) return 0;
  if (n >= 30) {
    Message("NONEXISTENT");
    Error();
    return 0;
    }
  flag = FlagSet(n);
  ClearFlag(n);
  return flag;
  }

