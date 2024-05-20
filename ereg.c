#include "header.h"

void EReg(byte post) {
  int base;
  int ofs;
  int e;
  NUMBER x;
  NUMBER y;
  base = ram[REG_C*7+2] << 4;
  base |= ((ram[REG_C*7+1] >> 4) & 0xf);
  e = 0xffff;
  if (post <0x70) e = post;
  if (post >= 0x80 && post <= 0xef) {
    e = ToInteger(RecallNumber(base + (post & 0x7f)));
    }
  if (post >= 0xf0 && post <= 0xff) {
    e = ToInteger(RecallNumber(post & 0x0f));
    }
  if (base+e > 0xfff-6) {
    Message("NONEXISTENT");
    return;
    }
  ram[REG_C*7+6] = (e >> 4) & 0xff;
  ram[REG_C*7+5] &= 0x0f;
  ram[REG_C*7+5] |= ((e & 0xf) << 4);
  }

