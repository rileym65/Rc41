#include "header.h"

void View(byte post) {
  char   tmp[16];
  NUMBER a;
  a = Rcl(post);
  Format(a, tmp);
  Message(tmp);
  SetFlag(50);
  }

