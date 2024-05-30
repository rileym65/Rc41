#include "header.h"

void Pack() {
  int i;
  int end;
  int cur;
  int addr;
  int next;
  int last;
  int total;
  int count;
  int pack;
  int start;
  int bytes;
  int prg;
  printf("PACKING\n");
  prg = FromPtr((ram[REG_B+1] << 8) | ram[REG_B+0]);
  end = (((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0]) * 7 + 2;
  last = ((ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f));
  last = last * 7;
  cur = end;
  pack = 0;
  while (cur < last) {
    next = ((ram[cur] << 8) | ram[cur-1]) & 0xfff;
    if (next == 0x000) {
      next = last - 1;
      }
    else
      next = cur + (((next & 0x1ff) * 7) + ((next >> 9) & 0x7)) - 1;
    if (ram[cur-2] < 0xf0) {
      if ((ram[cur-2] & 0x0f) == 0x0d) pack = -1; else pack = 0;
      if ((ram[cur-2] & 0xf0) == 0x20) pack = -1;
      if (pack) {
        ram[cur-2] &= 0xf0;
        ram[cur-2] |= 0x09;
        }
      }

    if (pack) {
      addr = next;
      total = 0;
      count = 0;
      while (addr > cur) {
        addr -= isize(addr);
        start = addr;
        if (ram[addr] >= 0xb0 && ram[addr] <= 0xbf) {
          ram[addr-1] = 0;
          }
        if (ram[addr] >= 0xd0 && ram[addr] <= 0xef) {
          ram[addr] &= 0xf0;
          ram[addr-1] = 0x00;
          ram[addr-2] &= 0x7f;
          }
        while (ram[addr] == 0) {
          addr--;
          count++;
          }
        if (count > 0) {
          total += count;
          bytes = (addr-end)+3;
          for (i=0; i<bytes; i++)
            ram[start-i] = ram[addr--];
          if (start >= prg) prg += count;
          addr = start;
          end += count;
          cur += count;
          for (i=0; i < count+3; i++) ram[end-3-i] = 0;
          }
        count = 0;
        }
      if (total > 0) {
        i = ((ram[cur] & 0x0f) << 8) | ram[cur-1];
        i = ((i & 0x1ff) * 7) + ((i >> 9) & 0x07);
        i -= total;
        i = ((i / 7) & 0x1ff) | ((i % 7) << 9);
        ram[cur] = ((i >> 8) & 0xff) | 0xc0;
        ram[cur-1] = i & 0xff;
        }
      }

    cur = next;
    if (cur == last-1) cur = last;
    }
  count = 0;
  while ((end % 7) != 2) {
    count++;
    ram[end-3] = ram[end-2];
    ram[end-2] = ram[end-1];
    ram[end-1] = ram[end-0];
    ram[end-0] = 0;
    end--;
    }
  i = ((ram[end] & 0x0f) << 8) | ram[end-1];
  i = ((i & 0x1ff) * 7) + ((i >> 9) & 0x07);
  i += count;
  i = ((i / 7) & 0x1ff) | ((i % 7) << 9);
  ram[end] = ((i >> 8) & 0xff) | 0xc0;
  ram[end-1] = i & 0xff;
  end /= 7;
  ram[REG_C+1] &= 0xf0;
  ram[REG_C+1] |= ((end >> 8) & 0x0f);
  ram[REG_C+0] = end & 0xff;
  prg = ToPtr(prg);
  ram[REG_B+1] = (prg >> 8) & 0xff;
  ram[REG_B+0] = (prg & 0xff);
  }

