#define MAIN
#include "header.h"
#include <math.h>

char *NextToken(char* line, char* token) {
  int p;
  int qt;
  qt = 0;
  while (*line == ' ') line++;
  p = 0;
  while (*line != 0 && ((*line > ' ' && qt == 0) || (qt != 0))) {
    if (*line == '"') {
      qt = (qt == 0) ? -1 : 0;
      token[p++] = *line++;
      }
    else token[p++] = *line++;
    }
  token[p] = 0;
  while (*line != 0 && *line <= ' ') line++;
  return line;
  }


char *PostFix(byte flags, char* line, byte *b) {
  int   n;
  char  token[32];
  line = NextToken(line, token);
  if (token[0] >= '0' && token[0] <= '9') {
    n = atoi(token);
    if (n < 0) n = 0;
    if (n > 99) n = 99;
    *b = n;
    }
  else if (strcasecmp(token, "L") == 0) *b = 0x74;
  else if (strcasecmp(token, "X") == 0) *b = 0x73;
  else if (strcasecmp(token, "Y") == 0) *b = 0x72;
  else if (strcasecmp(token, "Z") == 0) *b = 0x71;
  else if (strcasecmp(token, "T") == 0) *b = 0x70;
  else if (strcasecmp(token, "ind") == 0) {
  line = NextToken(line, token);
    if (token[0] >= '0' && token[0] <= '9') {
      n = atoi(token);
      if (n < 0) n = 0;
      if (n > 99) n = 99;
      *b = n+128;
      }
    else if (strcasecmp(token, "L") == 0) *b = 0xf4;
    else if (strcasecmp(token, "X") == 0) *b = 0xf3;
    else if (strcasecmp(token, "Y") == 0) *b = 0xf2;
    else if (strcasecmp(token, "Z") == 0) *b = 0xf1;
    else if (strcasecmp(token, "T") == 0) *b = 0xf0;
    }
  return line;
  }

char *InputGtoXeq(char* line, byte base) {
  int n;
  char token[256];
  char buffer[300];
  line = NextToken(line, token);
  if (token[0] == '.') {
    if (token[1] == '.') {
      GtoEnd();
//      n = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
//      ram[REG_B+0] = n & 0xff;
//      ram[REG_B+1] = 0x30 | ((n >> 8) & 0x0f);
//      ram[REG_E+0] = 0x00;
//      ram[REG_E+1] &= 0xf0;
      Pack();
      }
    else if (token[1] == '"') {
      }
    else {
      n = atoi(token+1);
      GotoLine(n);
      }
    ram[REG_R+1] = 0x00;
    }
  else {
    if (token[0] == '"') {
      ram[REG_R+1] = (base == 0xd0) ? 0x1d : 0x1e;
      if (FlagSet(52)) {
        sprintf(buffer,"GTO %s",token);
        ProgramStep(buffer);
        }
      else {
        if (FlagSet(22)) EndNumber();
        n = FindGlobal(token);
        if (n != 0) {
          n = ToPtr(n);
          ram[REG_B+1] = (n >> 8) & 0xff;
          ram[REG_B+0] = n & 0xff;
          ram[REG_E+1] |= 0x0f;
          ram[REG_E+0] = 0xff;
          if (base == 0xe0) {
            running = -1;
            ram[REG_E+0] = 0xff;
            ram[REG_E+1] |= 0x0f;
            }
          }
        }
      ram[REG_R+1] = 0x00;
      }
    if (strcasecmp(token, "IND") == 0) {
      line = NextToken(line, token);
      n = atoi(token);
      ram[REG_R+1] = 0xae;
      if (base == 0xd0) ram[REG_R+0] = n;
        else ram[REG_R+0] = n | 0x80;
      }
    else if (token[0] >= '0' && token[0] <= '9') {
      n = atoi(token);
      if (n <= 14 && base == 0xd0) {
        ram[REG_R+1] = 0xb1+n;
        ram[REG_R+0] = 0;
        }
      else {
        ram[REG_R+1] = base;
        ram[REG_R+0] = 0;
        ram[REG_E+2] &= 0xf0;
        ram[REG_E+2] |= ((n & 0x70) >> 4);
        ram[REG_E+1] &= 0x0f;
        ram[REG_E+1] |= ((n & 0x0f) << 4);
        }
      }
    else if (token[0] >= 'A' && token[0] <= 'J') {
      n = token[0] - 'A' + 102;
      ram[REG_R+1] = base;
      ram[REG_R+0] = 0;
      ram[REG_E+2] &= 0xf0;
      ram[REG_E+2] |= ((n & 0x70) >> 4);
      ram[REG_E+1] &= 0x0f;
      ram[REG_E+1] |= ((n & 0x0f) << 4);
      }
    else if (token[0] >= 'a' && token[0] <= 'e') {
      n = token[0] - 'a' + 123;
      ram[REG_R+1] = base;
      ram[REG_R+0] = 0;
      ram[REG_E+2] &= 0xf0;
      ram[REG_E+2] |= ((n & 0x70) >> 4);
      ram[REG_E+1] &= 0x0f;
      ram[REG_E+1] |= ((n & 0x0f) << 4);
      }
    }
  return line;
  }

char *InputLbl(char* line) {
  int n;
  char token[256];
  char buffer[300];
  line = NextToken(line, token);
  if (token[0] >= '0' && token[0] <= '9') {
    n = atoi(token);
    if (n <= 14) {
      ram[REG_R+1] = 0x01+n;
      ram[REG_R+0] = 0;
      }
    else {
      ram[REG_R+1] = 0xcf;
      ram[REG_R+0] = n & 0x7f;
      }
    }
  else if (token[0] >= 'A' && token[0] <= 'J') {
    ram[REG_R+1] = 0xcf;
    ram[REG_R+0] = token[0] - 'A' + 102;
    }
  else if (token[0] >= 'a' && token[0] <= 'e') {
    ram[REG_R+1] = 0xcf;
    ram[REG_R+0] = token[0] - 'a' + 123;
    }
  else if (token[0] == '"') {
    ram[REG_R+1] = 0xc0;
    if (FlagSet(52)) {
      sprintf(buffer,"LBL %s",token);
      ProgramStep(buffer);
      }
    ram[REG_R+1] = 0x00;
    }
  return line;
  }

char *InputRcl(char* line) {
  byte  n;
  line = PostFix(0x12, line, &n);
  if (n < 16) {
    ram[REG_R+1] = 0x20 + n;
    }
  else {
    ram[REG_R+1] = 0x90;
    ram[REG_R+0] = n;
    }
  return line;
  }

char *InputEnd(char* line) {
  ram[REG_R+1] = 0xc0;
  if (FlagSet(52)) {
    ProgramStep("END");
    }
  ram[REG_R+1] = 0x00;
  return line;
  }

char *InputSto(char* line) {
  byte  n;
  line = PostFix(0x12, line, &n);
  if (n < 16) {
    ram[REG_R+1] = 0x30 + n;
    }
  else {
    ram[REG_R+1] = 0x91;
    ram[REG_R+0] = n;
    }
  return line;
  }

int main(int argc, char** argv) {
  int   addr;
  int   i;
  int   j;
  int   instBj;
  char  buffer[1024];
  char  token[32];
  char  token2[32];
  int   isNumber;
  byte  b;
  char *pchar;
  int   file;
  debug = 0;
  ramClear = 0;
  singleStep = 0;
  instBj = 0;
  useLcd = 0;
  strcpy(printBuffer,"");
  printPosition = 0;
  ram[LIFT] = 'D';
  ram[PENDING] = 'D';
  for (i=1; i<argc; i++) {
    if (strcmp(argv[i],"-bj") == 0) instBj = -1;
    if (strcmp(argv[i],"-d") == 0) debug = -1;
    if (strcmp(argv[i],"-rc") == 0) ramClear = -1;
    if (strcmp(argv[i],"-ss") == 0) { singleStep = -1; debug = -1; }
    if (strcmp(argv[i],"-lcd") == 0) useLcd = 0xff;
    }
  Init();
  OpenTapeDrive("tape1.dat");
  if (ramClear == 0) {
    file = open("rc41.ram", O_RDONLY);
    if (file > 0) {
      read(file, ram, sizeof(ram));
      close(file);
      if (debug) ShowStatRegs(0);
      }
    else Message("MEMORY LOST");
    }
  else Message("MEMORY LOST");
  SetFlag(55);
  SetFlag(21);

  if (instBj) {
    printf("Installing Byte Jumper on <E+>\n");
    addr = 0x0c0 * 7;
    while (ram[addr+6] == 0xf0 &&
           ram[addr+0] != 0x00 &&
           ram[addr+3] != 0x00) addr += 7;
printf("Address: %x\n",addr/7);
    if (ram[addr+6] != 0xf0) {
printf("New register\n");
      ram[addr+6] = 0xf0;
      }
    SetKaFlag(1, 1);
    if (ram[addr+0] == 0x00) {
      ram[addr+0] = 0x01;
      ram[addr+1] = 'A';
      ram[addr+2] = 0xf1;
      }
    else {
      ram[addr+3] = 0x01;
      ram[addr+4] = 'A';
      ram[addr+5] = 0xf1;
      }
    }

  while (on) {
    if (running) {
      addr = (ram[REG_B+1] << 8) | ram[REG_B+0];
      addr = FromPtr(addr) - 1;
      addr = Exec(addr);
      if (addr != 0) {
        addr = ToPtr(addr + 1);
        ram[REG_B+1] = (addr >> 8) & 0xff;
        ram[REG_B+0] = addr & 0xff;
        }
      else {
        running = 0;
//        ram[REG_E+0] = 0xff;
//        ram[REG_E+1] |= 0x0f;
        }
      }
    else {
      printf("\n[%s]\n",Display(screen));
      if (useLcd) DrawLcd(Display(screen));
      if (debug) ShowStatRegs(0);
      ClearFlag(50);
      if (FlagSet(52)) printf("PRGM");
      printf(">");
      fgets(buffer, 1023, stdin);
      while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < ' ')
        buffer[strlen(buffer)-1] = 0;
      pchar = buffer;
      while (*pchar == ' ') pchar++;
      if (*pchar == '\\') {
        Debug(pchar);
        *pchar = 0;
        }
      while (*pchar != 0) {
        pchar = NextToken(pchar, token);
        isNumber = -1;
        for (i=0; i<strlen(token); i++)
          if (token[i] != '.' && (token[i] < '0' || token[i] > '9')) isNumber = 0;
        if (isNumber) {
          if (FlagSet(52)) {
            SetFlag(22);
            ProgramStep(token);
            }
          else {
            for (i=0; i<strlen(token); i++) {
              if (token[i] == '.') ram[REG_R+1] = 0x1a;
                else ram[REG_R+1] = token[i] - '0' + 0x10;
              Exec(71);
              }
            }
          }
        else if (token[0] == '"') {
          if (FlagSet(52)) {
            ram[REG_R+1] = 0xf0;
            ProgramStep(token);
            }
          else {
            i = 1;
            if (token[i] != '|') {
              for (j=REG_M; j<=REG_P+2; j++) ram[j] = 0;
              } else i++;
            while (token[i] != '"' && token[i] != 0) {
              for (j=REG_P+2; j>REG_M; j--)
                ram[j] = ram[j-1];
              ram[REG_M] = token[i++];
              if (ram[REG_M] > 'e' && ram[REG_M] <= 'z')
                ram[REG_M] -= 32;
              }
            }
  
  
  //        i = 1;
  //        ram[REG_R+1] = 0xf0;
  //        while (token[i] != '"' && token[i] != 0) {
  //          ram[REG_R+1]++;
  //          ram[REG_R+1-i] = token[i];
  //          if (ram[REG_R+1-i] > 'e' &&
  //              ram[REG_R+1-i] <= 'z') ram[REG_R+1-i] -= 32;
  //          i++;
  //          }
  //        Exec(0x100a);
          }
        else {
          i = 0;
          if (strcasecmp(token,"PRGM") == 0) {
            linksCleared = 0;
            if (FlagSet(52)) ClearFlag(52);
              else SetFlag(52);
            }
          else if (strcasecmp(token,"SST") == 0) {
            Sst();
            }
          else if (strcasecmp(token,"BST") == 0) {
            Bst();
            }
          else if (strcasecmp(token,"CAT") == 0) {
            pchar = NextToken(pchar, token);
            Cat(token);
            }
          else if (strcasecmp(token,"DEL") == 0) {
            pchar = NextToken(pchar, token);
            Del(token);
            }
          else if (strcasecmp(token,"SIZE") == 0) {
            pchar = NextToken(pchar, token);
            Size(token);
            }
          else if (strcasecmp(token,"PACK") == 0) {
            Pack();
            }
          else if (strcasecmp(token, "ASN") == 0) {
            pchar = NextToken(pchar, token);
            pchar = NextToken(pchar, token2);
            Asn(token, token2);
            }
          else if (strcasecmp(token,"PRP") == 0) {
            pchar = NextToken(pchar, token);
            Prp(token);
            }
          else if (strcasecmp(token,"CLP") == 0) {
            pchar = NextToken(pchar, token);
            Clp(token);
            }
          else if (strcasecmp(token,"VER") == 0) {
            CardReader(5,0);
            }
          else if (strcasecmp(token,"WALL") == 0) {
            CardReader(6,0);
            }
          else if (strcasecmp(token,"RALL") == 0) {
            CardReader(37,0);
            }
          else if (strcasecmp(token,"NEWM") == 0) {
            pchar = NextToken(pchar, token);
            TapeDrive(3, atoi(token));
            }
          else if (strcasecmp(token,"RS") == 0) {
            if (FlagSet(22)) EndNumber();
            running = -1;
            ram[REG_E+0] = 0xff;
            ram[REG_E+1] |= 0x0f;
            }
          else if (token[0] == '<' && token[strlen(token)-1] == '>') {
            i = 0;
            while (keys[i].cmd != 0xff && strcasecmp(keys[i].key, token) != 0) {
              i++;
              }
            if (keys[i].cmd != 0xff) {
              if (GetKaFlag(keys[i].keycode)) {
                addr = 0x0c0 * 7;
                while (ram[addr+6] == 0xf0 &&
                       ram[addr+0] != keys[i].keycode &&
                       ram[addr+3] != keys[i].keycode) addr += 7;
                if (ram[addr+6] != 0xf0) {
                  Message("NONEXISTENT");
                  }
                else {
                  if (ram[addr+0] == keys[i].keycode) {
                    if (ram[addr+2] <= 0x0f) {
                      ram[REG_R+1] = ram[addr+1];
                      ram[REG_R+0] = 0x00;
                      }
                    else {
                      ram[REG_R+1] = ram[addr+2];
                      ram[REG_R+0] = ram[addr+1];
                      }
                    }
                  else {
                    if (ram[addr+5] <= 0x0f) {
                      ram[REG_R+1] = ram[addr+4];
                      ram[REG_R+0] = 0x00;
                      }
                    else {
                      ram[REG_R+1] = ram[addr+5];
                      ram[REG_R+0] = ram[addr+4];
                      }
                    }
                  if (FlagSet(52)) ProgramStep(NULL);
                    else if (ram[71] != 0) Exec(71);
                  }
                }
              else {
                i = keys[i].cmd;
                if (catalog[i].flags != 0xff) {
                  if (catalog[i].cmd == 0x20) pchar = InputRcl(pchar);
                  else if (catalog[i].cmd == 0x30) pchar = InputSto(pchar);
                  else if (catalog[i].cmd == 0xb1) pchar = InputGtoXeq(pchar, 0xd0);
                  else if (catalog[i].cmd == 0x1e) pchar = InputGtoXeq(pchar, 0xe0);
                  else if (catalog[i].cmd == 0x01) pchar = InputLbl(pchar);
                  else if (catalog[i].cmd == 0xc0) pchar = InputEnd(pchar);
                  else {
                    ram[REG_R+1] = catalog[i].cmd;
                    if (catalog[i].flags & 0x3) {
                      pchar = PostFix(catalog[i].flags, pchar, &b);
                      ram[REG_R+0] = b;
                      }
                    }
                  if (FlagSet(52)) ProgramStep(NULL);
                    else if (ram[71] != 0) Exec(71);
                  }
                }

              }
            else {
              Message("NONEXISTENT");
              }
            }
          else {
            while (catalog[i].flags != 0xff && strcasecmp(catalog[i].name, token) != 0) {
              i++;
              }
            if (catalog[i].flags != 0xff) {
              if (catalog[i].cmd == 0x20) pchar = InputRcl(pchar);
              else if (catalog[i].cmd == 0x30) pchar = InputSto(pchar);
              else if (catalog[i].cmd == 0xb1) pchar = InputGtoXeq(pchar, 0xd0);
              else if (catalog[i].cmd == 0x1e) pchar = InputGtoXeq(pchar, 0xe0);
              else if (catalog[i].cmd == 0x01) pchar = InputLbl(pchar);
              else if (catalog[i].cmd == 0xc0) pchar = InputEnd(pchar);
              else {
                ram[REG_R+1] = catalog[i].cmd;
                if (catalog[i].flags & 0x3) {
                  pchar = PostFix(catalog[i].flags, pchar, &b);
                  ram[REG_R+0] = b;
                  }
                }
              if (FlagSet(52)) ProgramStep(NULL);
                else if (ram[71] != 0) Exec(71);
              }
            else {
              i = 0;
              while (catalog2[i].flags != 0xff && strcasecmp(catalog2[i].name, token) != 0) i++;
              if (catalog2[i].flags == 0xff) Message("NONEXISTENT");
              else {
                ram[REG_R+1] = catalog2[i].cmd;
                ram[REG_R+0] = catalog2[i].post;
                if (FlagSet(52)) ProgramStep(NULL);
                  else if (ram[71] != 0) Exec(71);
                }
              }

            }
          }
        }
      }
    }

  file = open("rc41.ram", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (file >= 0) {
    write(file, ram, sizeof(ram));
    close(file);
    }

  }

