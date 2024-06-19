#include "header.h"

void Wprg(char* filename) {
  int i;
  int file;
  int address;
  int end;
  int len;
  char card[7];
  address = (ram[REG_B+1] << 8) | ram[REG_B+0];
  address = FromPtr(address);
  address = FindStart(address);
  end = FindEnd(address);
printf("%x -> %x\n",address,end);
  file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
  if (file >= 0) {
    end -= 2;
    len = (address - end) / 7;
    card[0] = 'P';
    card[1] = 0x00;
    card[2] = 0x01;
    i = ((len+15) / 16);
    card[3] = (i >> 8) & 0xff;
    card[4] = i & 0xff;
    len = (address - end) + 1;
    card[5] = (len >> 8) & 0xff;
    card[6] = (len & 0xff);
    write(file, card, 7);
    while (len > 0) {
      write(file, ram+address, 1);
      address--;
      len--;
      }
    close(file);
    }
  else {
    Message("CARD ERR");
    Error();
    }
  }

