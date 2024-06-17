#include "header.h"

int tapefile;
byte sector[256];
int  sectorNumber;
int  sectorPtr;
int  written;

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
        if (sector[p] == 'D') printf("DA");
        if (sector[p] == 'K') printf("KE");
        if (sector[p] == 'S') printf("ST");
        if (sector[p] == 'A') printf("WA");
        if (sector[p+9] & 1) printf(",S");
        else printf("  ");
        printf("    ");
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
      if (s > 511) flag = 0;
        else ReadSector(s);
      }

    }
  }

void td_create() {
  int p;
  char filename[32];
  int m;
  int size;
  NUMBER x;
printf("Create data file\n");
  m = REG_P+2;
  while (m >= REG_M && ram[m] == 0x00) m--;
  p = 0;
  while (m >= REG_M) {
    if (ram[m] != 0x00) filename[p++] = ram[m];
    m--;
    }
  if (p > 7) p = 7;
  filename[p] = 0;
printf("Filename: %s\n",filename);
  x = RecallNumber(R_X);
ShowNumber(x);
  size = ToInteger(x);
printf("Size: %d\n",size);
  p = CreateFile(filename, size * 7, 'D');
printf("create result: %d\n",p);
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

  }

void OpenTapeDrive(char* filename) {
  tapefile = open(filename, O_CREAT | O_RDWR, 0666);
  if (tapefile < 0) {
    printf("Could not open tape drive: %s\n",filename);
    return;
    }
  ReadSector(0);
  }

