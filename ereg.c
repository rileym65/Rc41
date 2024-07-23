#include "header.h"

void EReg(byte post) {
  int base;
  int e;
  post = GetPost(post);
  if (errFlag) return;
  base = ram[REG_C+2] << 4;
  base |= ((ram[REG_C+1] >> 4) & 0xf);
  e = post;
  if (base+e > 0x1ff-6) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  ram[REG_C+6] = (e >> 4) & 0xff;
  ram[REG_C+5] &= 0x0f;
  ram[REG_C+5] |= ((e & 0xf) << 4);
  }

