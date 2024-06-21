#include "header.h"

int tapefile;
byte sector[256];
int  sectorNumber;
int  sectorPtr;
int  written;
int  file_rec;
int  file_regs;
int  file_reg;
int  file_pos;
int  file_flags;

void ReadSector(int s) {
  if (s >= 0 && s < 512) {
    sectorNumber = s;
    lseek(tapefile, s * 256, SEEK_SET);
    read(tapefile, sector, 256);
    sectorPtr = 0;
    written = 0;
    }
  }

void WriteSector(int s) {
  if (s >= 0 && s < 512) {
    sectorNumber = s;
    lseek(tapefile, sectorNumber * 256, SEEK_SET);
    write(tapefile, sector, 256);
    written = 0;
    }
  }

void Allocate(int l) {
  int sec;
  int ofs;
  sec = l / 256;
  ofs = l & 0xff;
  if (written) WriteSector(sectorNumber);
  ReadSector(sec);
  sector[ofs] = 0xff;
  WriteSector(sec);
  }

void Deallocate(int l) {
  int sec;
  int ofs;
  sec = l / 256;
  ofs = l & 0xff;
  if (written) WriteSector(sectorNumber);
  ReadSector(sec);
  sector[ofs] = 0x00;
  WriteSector(sec);
  }

int FindFile(char* filename) {
  int s;
  int p;
  int d;
  int flag;
  if (written) WriteSector(sectorNumber);
  d = 0;
  p = 0;
  s = 2;
  flag = -1;
  while (flag) {
    ReadSector(s);
    while (p < 256) {
      if (sector[p] != 0x00) {
        if (strcmp(filename, (char*)(sector+p+1)) == 0) return p;
        }
      if (sector[p] == 0xff) flag = 0;
      p += 32;
      d++;
      }
    p = 0;
    s++;
    }
  return -1;
  }

int FindOpenDir() {
  int s;
  int p;
  int d;
  int flag;
  if (written) WriteSector(sectorNumber);
  d = 0;
  p = 0;
  s = 2;
  flag = -1;
  while (flag) {
    ReadSector(s);
    while (p < 256) {
      if (sector[p] == 0x00) return d;
      if (sector[p] == 0xff) flag = 0;
      p += 32;
      d++;
      }
    p = 0;
    s++;
    }
  return -1;
  }

int FindOpenSectors(int count) {
  int s;
  int p;
  int d;
  int c;
  int flag;
  if (written) WriteSector(sectorNumber);
  d = 0;
  p = 0;
  s = 0;
  c = 0;
  flag = -1;
  while (flag) {
    ReadSector(s);
    while (p < 256) {
      if (sector[p] == 0x00) c++;
        else {
          d = (s * 256) + p + 1;
          }
      if (c >= count) return d;
      p++;
      }
    p = 0;
    s++;
    if (s == 2) flag = 0;
    }
  return -1;
  }


int CreateFile(char* filename, int size, char typ) {
  int i;
  int dir;
  int dirsec;
  int dirofs;
  int rec;
  int recs;
  int regs;
  recs = (size + 255) / 256;
  regs = (size + 6) / 7;
  dir = FindOpenDir();
  if (dir < 0) return -1;
  rec = FindOpenSectors(recs);
  if (rec < 0) return -1;
  dirsec = (dir / 8) + 2;
  dirofs = (dir % 8) * 32;
  ReadSector(dirsec);
  sector[dirofs] = typ;
  for (i=0; i<7; i++)
    if (i < strlen(filename)) sector[dirofs+i+1] = filename[i];
      else sector[dirofs+i+1] = 0;
  sector[dirofs+8] = 0x00;
  sector[dirofs+9] = 0x00;
  sector[dirofs+10] = (regs >> 8) & 0xff;
  sector[dirofs+11] = regs & 0xff;
  sector[dirofs+12] = (size >> 8) & 0xff;
  sector[dirofs+13] = size & 0xff;
  sector[dirofs+14] = (rec >> 8) & 0xff;
  sector[dirofs+15] = rec & 0xff;
  sector[dirofs+16] = (recs >> 8) & 0xff;
  sector[dirofs+17] = recs & 0xff;
  WriteSector(sectorNumber);
  for (i=0; i<recs; i++) Allocate(rec + i);
  for (i=0; i<256; i++) sector[i] = 0;
  for (i=0; i<recs; i++)
    WriteSector(rec + i);
  return rec;
  }

void td_newm(int size) {
  int i;
  int e;
  e = (size + 7) / 8;
  for (i=0; i<256; i++) sector[i] = 0;
  for (i=0; i<e+2; i++) sector[i] = 0xff;
  WriteSector(0);
  for (i=0; i<256; i++) sector[i] = 0;
  WriteSector(1);
  for (i=0; i<e; i++) {
    if (i == e-1) sector[7*32] = 0xff;
    WriteSector(i+2);
    }
  for (i=0; i<256; i++) sector[i] = 0;
  for (i=e+2; i<512; i++) WriteSector(i);
  }

void td_dir() {
  int flag;
  int s;
  int r;
  int i;
  int p;
  s = 2;
  if (written) WriteSector(sectorNumber);
  printf("NAME    TYPE    REGS\n");
  flag = -1;
  while (flag) {
    ReadSector(s);
    p = 0;
    while (p < 256) {
      if (sector[p] != 0 && sector[p] != 0xff) {
        for (i=0; i<7; i++)
          if (sector[p+i+1] != 0) printf("%c", sector[p+i+1]);
            else printf(" ");
        printf(" ");
        if (sector[p] == 'P') printf("PR");
        else if (sector[p] == 'D') printf("DA");
        else if (sector[p] == 'K') printf("KE");
        else if (sector[p] == 'S') printf("ST");
        else if (sector[p] == 'A') printf("WA");
        else if (sector[p] != 0x00) {
          Message("NO MEDM");
          Error();
          return;
          }
        if (sector[p+9] != 0) {
          switch(sector[p+9]) {
            case 1: printf(",S "); break;
            case 2: printf(",P "); break;
            case 3: printf(",PS"); break;
            }
          }
        else printf("   ");
        printf("   ");
        r = (sector[p+10] << 8) | sector[p+11];
        printf("%4d\n",r);
        }
      else if (sector[p] == 0xff) {
        flag = 0;
        }
      p += 32;
      }
    if (p >= 256) {
      p = 0;
      s++;
      if (s > 511) {
        flag = 0;
        Message("NO MEDM");
        Error();
        }
        else ReadSector(s);
      }
    }
  }

void td_create() {
  char filename[32];
  int size;
  NUMBER x;
  GetAlpha(filename);
  filename[7] = 0;
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  if (FindFile(filename) >= 0) {
    Message("DUP FL NAME");
    Error();
    return;
    }
  x = RecallNumber(R_X);
  size = ToInteger(x);
  CreateFile(filename, size * 7, 'D');
  }

void td_reada() {
  int  i;
  int  fp;
  int  rec;
  int  p;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'A') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  p = 0;
  ReadSector(rec);
  for (i=0; i<16*7; i++) ram[i] = sector[p++];
  for (i=0x0c0*7; i<0x200*7; i++) {
    ram[i] = sector[p++];
    if (p == 256) {
      rec++;
      ReadSector(rec);
      p = 0;
      }
    }
  }

void td_readk() {
  int i;
  int address;
  int rec;
  int fp;
  int p;
  int regs;
  int size;
  int end;
  char filename[32];
  size = 0;
  address = 0x0c0 * 7;
  GetAlpha(filename);
  filename[7] = 0;
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'K') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  regs = (sector[fp+10] << 8) | sector[fp+11];
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  if (0x0c0 + regs > end) {
    Message("NO ROOM");
    Error();
    return;
    }
  address = 0x0c0 * 7;
  while (ram[address+6] == 0xf0) {
    for (i=0; i<=6; i++) ram[address+i] = 0x00;
    address += 7;
    }
  p = 0;
  address = 0x0c0 * 7;
  ReadSector(rec);
  size = regs * 7;
  while (size > 0) {
    ram[address++] = sector[p++];
    size--;
    if (p == 256) {
      rec++;
      ReadSector(rec);
      p = 0;
      }
    }
  SetKaFlags();
  }

void td_readp() {
  int  i;
  int  fp;
  int  rec;
  int  size;
  int  p;
  int  end;
  int  adr;
  int  nabc;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'P') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  size = (sector[fp+12] << 8) | sector[fp+13];
  end = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
  end = (end * 7) + 2;
  adr = FindStart(end);
  for (i=end+1; i<=adr; i++) ram[i] = 0x00;
  p = 0;
  ReadSector(rec);
  while (size > 0) {
    nabc = ToPtr(adr--);
    ram[REG_B+1] = (nabc >> 8) & 0xff;
    ram[REG_B+0] = nabc & 0xff;
    ProgramByte(sector[p++]);
    if (p == 256) {
      rec++;
      ReadSector(rec);
      p = 0;
      }
    size--;
    }
  ReLink();
  }

void td_readr() {
  int i;
  int rec;
  int regs;
  int fp;
  int p;
  int adr;
  int addr;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  filename[7] = 0;
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'D') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  regs = (sector[fp+10] << 8) | sector[fp+11];
  ReadSector(rec);
  p = 0;
  adr = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  while (adr < 0x200) {
    addr = adr * 7;
    if (regs == 0) {
      return;
      }
    for (i=6; i>=0; i--) {
      ram[addr+i] = sector[p++];
      if (p == 256) {
        rec++;
        ReadSector(rec);
        p = 0;
        }
      }
    adr++;
    regs--;
    }
  }
void td_readrx() {
  int i;
  int adr;
  int r00;
  int size;
  NUMBER x;
  int b,e;
  if (file_rec < 0) {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  x = RecallNumber(R_X);
  GetBE(x, &b, &e);
  if (e < b) e = b;
  r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  size = 0x200 - r00;
  if (b >= size || e >= size) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  adr = (b + r00) * 7;
  ReadSector(file_rec);
  while (b <= e) {
    if (file_reg >= file_regs) {
      Message("END OF FILE");
      Error();
      return;
      }
    for (i=6; i>=0; i--) {
      ram[adr+i] = sector[file_pos++];
      if (file_pos == 256) {
        file_rec++;
        file_pos = 0;
        ReadSector(file_rec);
        }
      }
    adr += 7;
    b++;
    file_reg++;
    }
  }

void td_reads() {
  int i;
  int rec;
//  int btm;
  int fp;
//  int ofs;
  int r00_a;
  int r00_b;
//  int end;
//  int src;
//  int dst;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  filename[7] = 0;
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'S') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  ReadSector(rec);
  r00_a = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  r00_b = (sector[REG_C+2] << 4) | ((sector[REG_C+1] >> 4) & 0x0f);
  for (i=0; i<REG_P+3; i++) ram[i] = sector[i];
  for (i=2; i<=6; i++) ram[REG_D+i] = sector[REG_D+i];
  ram[REG_D+1] &= 0x0f;
  ram[REG_D+1] |= (sector[REG_D+1] & 0xf0);
  ram[REG_C+6] = sector[REG_C+6];
  ram[REG_C+5] = (ram[REG_C+5] & 0x0f) | (sector[REG_C+5] & 0xf0);
  Resize(r00_a, r00_b);
  }

void td_purge() {
  int  i;
  int  fp;
  int  rec;
  int  recs;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  if (sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  recs = (sector[fp+16] << 8) | sector[fp+17];
  for (i=0; i<32; i++) sector[fp+i] = 0;
  WriteSector(sectorNumber);
  for (i=0; i<256; i++) sector[i] = 0;
  for (i=0; i<recs; i++) WriteSector(rec+i);
  for (i=0; i<recs; i++) Deallocate(rec+i);
  }

void td_rename() {
  int i;
  int fp;
  char *comma;
  char oldname[32];
  char newname[32];
  GetAlpha(oldname);
  if (strlen(oldname) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  comma = strchr(oldname, ',');
  if (comma == NULL) {
    Message("NAME ERR");
    Error();
    return;
    }
  if (comma == oldname) {
    Message("NAME ERR");
    Error();
    return;
    }
  *comma = 0;
  comma++;
  strcpy(newname, comma);
  oldname[7] = 0;
  newname[7] = 0;
  fp = FindFile(newname);
  if (fp >= 0) {
    Message("DUP FL NAME");
    Error();
    return;
    }
  fp = FindFile(oldname);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  if (sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  for (i=1; i<8; i++) sector[fp+i] = 0;
  for (i=0; i<strlen(newname); i++)
    sector[fp+1+i] = newname[i];
  WriteSector(sectorNumber);
  }

void td_sec() {
  int  fp;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  sector[fp+9] |= 0x01;
  WriteSector(sectorNumber);
  }

void td_seekr() {
  int  fp;
  char filename[32];
  int size;
  NUMBER x;
  GetAlpha(filename);
  filename[7] = 0;
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  if (sector[fp] != 'D') {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  x = RecallNumber(R_X);
  size = ToInteger(x);
  file_rec = (sector[fp+14] << 8) | sector[fp+15];
  file_regs = (sector[fp+10] << 8) | sector[fp+11];
  if (size >= file_regs) {
    file_rec = -1;
    file_regs = -1;
    file_flags = -1;
    file_reg = -1;
    Message("END OF FILE");
    Error();
    return;
    }
  file_flags = sector[fp+9];
  file_reg = size;
  size *= 7;
  file_rec += (size / 256);
  file_pos = size & 0xff;
  }

void td_unsec() {
  int  fp;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  sector[fp+9] &= 0xfe;
  WriteSector(sectorNumber);
  }

void td_verify() {
  int  fp;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  }

void td_wrta() {
  int  i;
  int  fp;
  int  rec;
  int  p;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'A') {
    Message("DUP FL NAME");
    Error();
    return;
    }
  if (fp >= 0 && sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  if (fp >= 0) {
    rec = (sector[fp+14] << 8) | sector[fp+15];
    }
  else {
    rec = CreateFile(filename, 2352, 'A');
    if (rec < 0) {
      return;
      }
    }
  p = 0;
  for (i=0; i<16*7; i++) sector[p++] = ram[i];
  for (i=0x0c0*7; i<0x200*7; i++) {
    sector[p++] = ram[i];
    if (p == 256) {
      WriteSector(rec);
      rec++;
      p = 0;
      }
    }
  if (p != 0) WriteSector(rec);
  }

void td_wrtk() {
  int i;
  int address;
  int rec;
  int recs;
  int fp;
  int p;
  int dirsec;
  int dirofs;
  int size;
  char filename[32];
  size = 0;
  address = 0x0c0 * 7;
  while (ram[address+6] == 0xf0) {
    size += 7;
    address += 7;
    }
  if (size == 0) {
    Message("NO KEYS");
    Error();
    return;
    }
  GetAlpha(filename);
  filename[7] = 0;
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'K') {
    Message("DUP FL NAME");
    Error();
    return;
    }
  if (fp >= 0 && sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  if (fp > 0) {
    dirsec = sectorNumber;
    dirofs = fp;
    rec = (sector[fp+14] << 8) | sector[fp+15];
    recs = (sector[fp+16] << 8) | sector[fp+17];
    for (i=0; i<recs; i++) Deallocate(rec+i);
    recs = (size + 255) / 256;
    rec = FindOpenSectors(recs);
    for (i=0; i<recs; i++) Allocate(rec+i);
    ReadSector(dirsec);
    sector[dirofs + 10] = (((size + 6) / 7) >> 8) & 0xff;
    sector[dirofs + 11] = ((size + 6) / 7) & 0xff;
    sector[dirofs + 12] = (size >> 8) & 0xff;
    sector[dirofs + 13] = size & 0xff;
    sector[dirofs + 14] = (rec >> 8) & 0xff;
    sector[dirofs + 15] = rec & 0xff;
    sector[dirofs + 16] = (recs >> 8) & 0xff;
    sector[dirofs + 17] = recs & 0xff;
    WriteSector(dirsec);
    }
  else {
    rec = CreateFile(filename, size, 'K');
    }
  p = 0;
  address = 0x0c0 * 7;
  while (size > 0) {
    sector[p++] = ram[address++];
    size --;
    if (p == 256) {
      WriteSector(rec);
      rec++;
      p = 0;
      }
    }
  if (p > 0) WriteSector(rec);
  }

void td_wrtp(int priv) {
  int i;
  int address;
  int end;
  int len;
  int rec;
  int recs;
  int fp;
  int p;
  int dirsec;
  int dirofs;
  char *comma;
  char filename[32];
  char progname[32];
  GetAlpha(progname);
  if (strlen(progname) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  comma = strchr(progname, ',');
  if (comma != NULL) {
    if (comma == progname) {
printf("Need to code for ',filename'\n");
return;
      }
    else {
      *comma = 0;
      comma++;
      strcpy(filename, comma);
      }
    }
  else {
    strcpy(filename,progname);
    }
  filename[7] = 0;
printf("Progname: %s\n", progname);
printf("Filename: %s\n", filename);
  if (strlen(filename) == 0 || strlen(progname) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  address = FindGlobal(progname);
  if (address == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  address = FindStart(address);
  end = FindEnd(address);
  end -= 2;
  len = (address - end) + 1;
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'P') {
    Message("DUP FL NAME");
    Error();
    return;
    }
  if (fp >= 0 && sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  if (fp > 0) {
    dirsec = sectorNumber;
    dirofs = fp;
    rec = (sector[fp+14] << 8) | sector[fp+15];
    recs = (sector[fp+16] << 8) | sector[fp+17];
    for (i=0; i<recs; i++) Deallocate(rec+i);
    rec = FindOpenSectors(recs);
    for (i=0; i<recs; i++) Allocate(rec+i);
    ReadSector(dirsec);
    sector[dirofs + 10] = (((len + 6) / 7) >> 8) & 0xff;
    sector[dirofs + 11] = ((len + 6) / 7) & 0xff;
    sector[dirofs + 12] = (len >> 8) & 0xff;
    sector[dirofs + 13] = len & 0xff;
    sector[dirofs + 14] = (rec >> 8) & 0xff;
    sector[dirofs + 15] = rec & 0xff;
    sector[dirofs + 16] = (recs >> 8) & 0xff;
    sector[dirofs + 17] = recs & 0xff;
    WriteSector(dirsec);
printf("Overwriting\n");
printf("regs: %d\n",len/7);
printf("len : %d\n",len);
    }
  else {
    rec = CreateFile(filename, len, 'P');
    }
  p = 0;
  while (len > 0) {
    sector[p++] = ram[address--];
    len --;
    if (p == 256) {
      WriteSector(rec);
      rec++;
      p = 0;
      }
    }
  if (p > 0) WriteSector(rec);
  fp = FindFile(filename);
  if (fp >= 0) {
    if (priv) sector[fp+9] |= 0x02;
      else sector[fp+9] &= 0xfd;
    WriteSector(sectorNumber);
    }

  }

void td_wrtr() {
  int i;
  int rec;
  int regs;
  int fp;
  int p;
  int adr;
  int addr;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  filename[7] = 0;
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'D') {
    Message("DUP FL NAME");
    Error();
    return;
    }
  if (fp >= 0 && sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  regs = (sector[fp+10] << 8) | sector[fp+11];
  ReadSector(rec);
  p = 0;
  adr = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  while (adr < 0x200) {
    addr = adr * 7;
    if (regs == 0) {
      if (p != 0) WriteSector(rec);
      Message("END OF FILE");
      Error();
      return;
      }
    for (i=6; i>=0; i--) {
      sector[p++] = ram[addr+i];
      if (p == 256) {
        WriteSector(rec);
        rec++;
        p = 0;
        }
      }
    adr++;
    regs--;
    }
  if (p != 0) WriteSector(rec);
  }

void td_wrtrx() {
  int i;
  int adr;
  int r00;
  int size;
  NUMBER x;
  int b,e;
  if (file_rec < 0) {
    Message("FL TYPE ERR");
    Error();
    return;
    }
  if (file_flags & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  x = RecallNumber(R_X);
  GetBE(x, &b, &e);
  if (e < b) e = b;
  r00 = (ram[REG_C+2] << 4) | ((ram[REG_C+1] >> 4) & 0x0f);
  size = 0x200 - r00;
  if (b >= size || e >= size) {
    Message("NONEXISTENT");
    Error();
    return;
    }
  adr = (b + r00) * 7;
  ReadSector(file_rec);
  while (b <= e) {
    if (file_reg >= file_regs) {
      if (file_pos != 0) WriteSector(file_rec);
      Message("END OF FILE");
      Error();
      return;
      }
    for (i=6; i>=0; i--) {
      sector[file_pos++] = ram[adr+i];
      if (file_pos == 256) {
        WriteSector(file_rec);
        file_rec++;
        file_pos = 0;
        ReadSector(file_rec);
        }
      }
    adr += 7;
    b++;
    file_reg++;
    }
  if (file_pos != 0) WriteSector(file_rec);
  }

void td_wrts() {
  int  i;
  int  fp;
  int  rec;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp >= 0 && sector[fp] != 'S') {
    Message("DUP FL NAME");
    Error();
    return;
    }
  if (fp >= 0 && sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  if (fp >= 0) {
    rec = (sector[fp+14] << 8) | sector[fp+15];
    ReadSector(rec);
    for (i=0; i<112; i++) sector[i] = ram[i];
    WriteSector(rec);
    }
  else {
    rec = CreateFile(filename, 112, 'S');
    if (rec > 0) {
      for (i=0; i<112; i++) sector[i] = ram[i];
      WriteSector(rec);
      }
    }
  }

void td_zero() {
  int  i;
  int  fp;
  int  rec;
  int  recs;
  char filename[32];
  GetAlpha(filename);
  if (strlen(filename) == 0) {
    Message("NAME ERR");
    Error();
    return;
    }
  fp = FindFile(filename);
  if (fp < 0) {
    Message("FL NOT FOUND");
    Error();
    return;
    }
  if (sector[fp+9] & 1) {
    Message("FL SECURED");
    Error();
    return;
    }
  rec = (sector[fp+14] << 8) | sector[fp+15];
  recs = (sector[fp+16] << 8) | sector[fp+17];
  for (i=0; i<256; i++) sector[i] = 0;
  for (i=0; i<recs; i++) WriteSector(rec+i);
  }

void TapeDrive(byte function, int addr) {

  if (function == 1) {                           /* CREATE */
    td_create();
    }

  if (function == 2) {                           /* DIR */
    td_dir();
    }

  if (function == 3) {                           /* NEWM */
    if (addr < 1 || addr > 447) {
      Message("DATA ERR");
      Error();
      return;
      }
    td_newm(addr+1);
    }

  if (function == 4) {                           /* PURGE */
    td_purge();
    }

  if (function == 5) {                           /* READA */
    td_reada();
    }

  if (function == 6) {                           /* READK */
    td_readk();
    }

  if (function == 7) {                           /* READP */
    td_readp();
    }

  if (function == 8) {                           /* READR */
    td_readr();
    }

  if (function == 9) {                           /* READRX */
    td_readrx();
    }

  if (function == 10) {                          /* READS */
    td_reads();
    }

  if (function == 11) {                          /* READSUB */
    GtoEnd();
    td_readp();
    }

  if (function == 12) {                          /* RENAME */
    td_rename();
    }

  if (function == 13) {                          /* SEC */
    td_sec();
    }

  if (function == 14) {                          /* SEEKR */
    td_seekr();
    }

  if (function == 15) {                          /* UNSEC */
    td_unsec();
    }

  if (function == 16) {                          /* VERIFY */
    td_verify();
    }

  if (function == 17) {                          /* WRTA */
    td_wrta();
    }

  if (function == 18) {                          /* WRTK */
    td_wrtk();
    }

  if (function == 19) {                          /* WRTP */
    td_wrtp(0);
    }

  if (function == 20) {                          /* WRTPV */
    td_wrtp(1);
    }

  if (function == 21) {                          /* WRTR */
    td_wrtr();
    }

  if (function == 22) {                          /* WRTRX */
    td_wrtrx();
    }

  if (function == 23) {                          /* WRTS */
    td_wrts();
    }

  if (function == 24) {                          /* ZERO */
    td_zero();
    }

  }

void OpenTapeDrive(char* filename) {
  tapefile = open(filename, O_CREAT | O_RDWR, 0666);
  if (tapefile < 0) {
    printf("Could not open tape drive: %s\n",filename);
    return;
    }
  ReadSector(0);
  file_rec = -1;
  file_regs = -1;
  file_pos = -1;
  }

