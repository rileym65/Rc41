#include "header.h"

void Rprg(char *filename) {
  int file;
  int address;
  int sadr;
  int nabc;
  int len;
  int regs;
  byte b;
  unsigned char card[7];
  file = open(filename, O_RDONLY);
  if (file >= 0) {
    read(file, card, 7);
    len = (card[5] << 8) | card[6];
    regs = (len + 6) / 7;
    GtoEnd();
    address = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
    address *= 7;
    address += 2;
    sadr = address;
    while (len > 0) {
      nabc = ToPtr(address);
      ram[REG_B+1] = (nabc >> 8) & 0xff;
      ram[REG_B+0] = nabc & 0xff;
      read(file, &b, 1);
      ProgramByte(b);
      address--;
      len--;
      }
    close(file);
    ReLink();

    while (ram[sadr] == 0x00) sadr--;
    while (ram[sadr] < 0xc0 || ram[sadr] > 0xcd || ram[sadr-2] >= 0xf0) {
      if (ram[sadr] >= 0xc0 && ram[sadr] <= 0xcd && ram[sadr-2] >= 0xf0) {
        if (ram[sadr-3] != 0x00) {
          b = ram[sadr-3];
          UnAsn(b, 3);
          ram[sadr-3] = b;
          SetKaFlag(b, 1);
          }
        }
      sadr -= isize(sadr);
      }

    Pack();

    }
  else {
    Message("CARD ERR");
    Error();
    }
  }

