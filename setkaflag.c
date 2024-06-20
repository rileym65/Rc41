#include "header.h"

void SetKaFlag(byte flag, byte set) {
  int i;
  int f;
  int b;
  int o;
  i = 0;
  while (keys[i].keycode != 0xff && keys[i].keycode != flag) i++;
  if (keys[i].keycode == 0xff) return;
  f = keys[i].bit - 1;
  b = 6 - (f >> 3);
  o = 7 - (f & 0x07);
  i = flag & 0x0f;
  if (i >= 1 && i <= 8) {                 /* unshifted */
    if (set) ram[REG_R+b] |= (1 << o);
      else ram[REG_R+b] &= (0xff ^ (1 << o));
    }
  else {                                  /* shifted */
    if (set) ram[REG_E+b] |= (1 << o);
      else ram[REG_E+b] &= (0xff ^ (1 << o));
    }
  }

