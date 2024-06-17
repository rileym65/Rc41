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
        if (strcmp(filename, sector+p+1) == 0) return p;
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
        if (sector[p] == 'D') printf("DA");
        if (sector[p] == 'K') printf("KE");
        if (sector[p] == 'S') printf("ST");
        if (sector[p] == 'A') printf("WA");
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
  p = CreateFile(filename, size * 7, 'D');
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
  len = address - end;
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
  while (len >= 0) {
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

  if (function == 13) {                          /* SEC */
    td_sec();
    }

  if (function == 15) {                          /* UNSEC */
    td_unsec();
    }

  if (function == 17) {                          /* WRTA */
    td_wrta();
    }

  if (function == 19) {                          /* WRTP */
    td_wrtp(0);
    }

  if (function == 20) {                          /* WRTPV */
    td_wrtp(1);
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
  }

