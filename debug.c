#include "header.h"

char* Hex(char* line, int *dest) {
  *dest = 0;
  while ((*line >= '0' && *line <= '9') ||
         (*line >= 'A' && *line <= 'F') ||
         (*line >= 'a' && *line <= 'f')) {
    *dest <<= 4;
    if (*line >= '0' && *line <= '9') *dest += (*line - '0');
    if (*line >= 'A' && *line <= 'F') *dest += (*line - 55);
    if (*line >= 'a' && *line <= 'f') *dest += (*line - 87);
    line++;
    }
  return line;
  }

char* Decimal(char* line, int *dest) {
  *dest = 0;
  while (*line >= '0' && *line <= '9') {
    *dest *= 10;
    *dest += (*line - '0');
    line++;
    }
  return line;
  }

void Debug(char* cmd) {
  int i;
  int j;
  int start;
  int end;
  int base;
  int addr;
  int file;
  char filename[1024];
  char card[5];
  int  p;
  cmd++;
  if (*cmd == '?') {
    printf("\n");
    printf("\\bj             - Perform synthetic byte jumper\n");
    printf("\\card filename  - Load card\n");
    printf("\\dreg ddd[-ddd] - Show data register contents\n");
    printf("\\reg hhh[-hhh]  - Show register contents\n");
    printf("\\size           - Show data register count\n");
    printf("\\stack          - Show stack registers\n");
    printf("\\stat           - Show all stat registers\n");
    printf("\\tape filename  - Mount tape file\n");
    }
  if (strcasecmp(cmd, "keys") == 0) {
    printf("     E-      Y^X      X^2      10^X     E^X   \n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("  |  E+  | | 1/X  | | SQRT | | LOG  | |  LN  |\n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("    CLE       %%       ASIN     ACOS     ATAN  \n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("  | X<>Y | | RDN  | | SIN  | | COS  | | TAN  |\n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("             ASN      LBL      GTO      BST   \n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("  |      | | XEQ  | | STO  | | RCL  | | SST  |\n");
    printf("  +------+ +------+ +------+ +------+ +------+\n");
    printf("         CAT          ISG      RTN      CLX   \n");
    printf("  +---------------+ +------+ +------+ +------+\n");
    printf("  |    ENTER^     | | CHS  | | EEX  | | <--  |\n");
    printf("  +---------------+ +------+ +------+ +------+\n");
    printf("    X=Y?         SF          CF         FS?   \n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("  |  -   |    |  7   |    |  8   |    |  9   |\n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("    X<=Y?       BEEP        P-R         R-P   \n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("  |  +   |    |  4   |    |  5   |    |  6   |\n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("    X>Y?        FIX         SCI         ENG   \n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("  |  *   |    |  1   |    |  2   |    |  3   |\n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("    X=0?         PI        LASTX        VIEW  \n");
    printf("  +------+    +------+    +------+    +------+\n");
    printf("  |  /   |    |  0   |    |  .   |    |  RS  |\n");
    printf("  +------+    +------+    +------+    +------+\n");
    }
  if (strcasecmp(cmd, "bj") == 0 && FlagSet(52) == 0) {
    addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
    addr = FromPtr(addr);
    i = (ram[addr] & 0x0f);
    addr -= i;
    addr = ToPtr(addr);
    ram[REG_B+1] = (addr >> 8) & 0xff;
    ram[REG_B+0] = addr & 0xff;
    }
  if (strcasecmp(cmd, "stack") == 0) {
    ShowStatRegs(-1);
    return;
    }
  if (strcasecmp(cmd, "stat") == 0) {
    ShowStatRegs(0);
    return;
    }
  if (strncasecmp(cmd, "reg ", 4) == 0) {
    cmd += 4;
    cmd = Hex(cmd, &start);
    end = start;
    if (*cmd=='-') {
      cmd++;
      cmd = Hex(cmd, &end);
      }
    if (end > start) {
      i = start; start = end; end = i;
      }
    for (i=start; i>=end; i--) {
      printf("%03x:",i);
      for (j=6; j>=0; j--)
        printf(" %02x",ram[i*7+j]);
      printf("\n");
      }
    }
  if (strncasecmp(cmd, "dreg ", 5) == 0) {
    base = (ram[REG_C+2] << 4) + ((ram[REG_C+1] >> 4) & 0x0f);
    cmd += 5;
    cmd = Decimal(cmd, &start);
    end = start;
    if (*cmd=='-') {
      cmd++;
      cmd = Decimal(cmd, &end);
      }
    start += base;
    end += base;
    if (start > 0xfff) start = 0xfff;
    if (end > 0xfff) end = 0xfff;
printf("Base: %x, start: %x, end: %x\n",base,start,end);
    if (end > start) {
      i = start; start = end; end = i;
      }
    for (i=start; i>=end; i--) {
      printf("%03d:",i-base);
      for (j=6; j>=0; j--)
        printf(" %02x",ram[i*7+j]);
      printf("\n");
      }
    }
  if (strcasecmp(cmd, "size") == 0) {
    base = (ram[REG_C+2] << 4) + ((ram[REG_C+1] >> 4) & 0x0f);
    printf("Size=%d\n",RAMTOP - base);
    }

  if (strncasecmp(cmd, "card ", 5) == 0) {
    cmd += 5;
    p = 0;
    while (*cmd == ' ') cmd++;
    while (*cmd > ' ') filename[p++] = *cmd++;
    filename[p] = 0;
    if (FlagSet(52)) {
      Wprg(filename);
      }
    else {
      file = open(filename, O_RDONLY);
      if (file > 0) {
        read(file, card, 1);
        close(file);
        if (card[0] == 'S') Rsts(filename);
        if (card[0] == 'A') Rall(filename);
        if (card[0] == 'P') Rprg(filename);
        }
      else printf("Could not read card file\n");
      }
    }

  if (strncasecmp(cmd, "tape ", 5) == 0) {
    cmd += 5;
    p = 0;
    while (*cmd == ' ') cmd++;
    while (*cmd > ' ') filename[p++] = *cmd++;
    filename[p] = 0;
    OpenTapeDrive(filename);
    }

  }

