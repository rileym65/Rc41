#include "header.h"

void Resize(int old_r00, int new_r00) {
  int btm;
  int ofs;
  int end;
  int src;
  int dst;
  if (old_r00 == new_r00) return;
  if (old_r00 > new_r00) {
    btm = 0x0c0 * 7;
    while (ram[btm+6] == 0xf0) btm += 7;
    btm /= 7;
    ofs = old_r00 - new_r00;
    end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
    if ((end - ofs) < btm) {
      Message("NO ROOM");
      Error();
      return;
      }
    dst = (end-ofs) * 7;
    src = end * 7;
    while (dst < 0xe00) {
      ram[dst] = (src < 0xe00) ? ram[src] : 0x00;
      dst++;
      src++;
      }
    ofs = -ofs;
    }
  else {
    ofs = new_r00 - old_r00;
    src = ((0x1ff - ofs) * 7) + 6;
    dst = (0x1ff * 7) + 6;
    end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
    end *= 7;
    while (src >= end) {
      ram[dst--] = ram[src--];
      }
    end = 0x0c0 * 7;
    while (ram[end + 6] == 0xf0) end += 7;
    while (src >= end) ram[src--] = 0x00;
    }
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  end += ofs;
  ram[REG_C+1] &= 0xf0;
  ram[REG_C+1] |= ((end >> 8) & 0x0f);
  ram[REG_C+0] = end & 0xff;
  ram[REG_C+2] = new_r00 >> 4;
  ram[REG_C+1] &= 0x0f;
  ram[REG_C+1] |= ((new_r00 & 0x0f) << 4);
  end = ((ram[REG_B+1] & 0x0f) << 8) | ram[REG_B+0];
  end += ofs;
  ram[REG_B+1] &= 0xf0;
  ram[REG_B+1] |= ((end >> 8) & 0x0f);
  ram[REG_B+0] = end & 0xff;
  }

