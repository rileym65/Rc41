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

char* Text(char* buffer) {
  int i;
  for (i=0; i<strlen(buffer); i++) {
    if (buffer[i] == 0x7f) buffer[i] = '|';
    if (buffer[i] == 0x60) buffer[i] = '"';
    if (buffer[i] == 0x7e) buffer[i] = 'E';
    if ((buffer[i] & 0xff) == 0xff) buffer[i] = '_';
    if ((buffer[i] & 0xff) < 0x20) buffer[i] = '#';
    if (buffer[i] == 0x00) buffer[i] = '_';
    if (buffer[i] & 0x80) buffer[i] = '#';
    }
  return buffer;
  }

char *Special(char* line) {
  int   i;
  int   n;
  int   ind;
  byte  cmd;
  int   lineNumber;
  word  flags;
  char  token[32];
  char  buffer[64];
  cmd = ram[REG_R+1];
  flags = reverse[cmd].flags;
  ind = 0;
  if (FlagSet(52)) {
    lineNumber = ram[REG_E+0] + ((ram[REG_E+1] &0x0f) << 8);
    if (lineNumber == 0xfff) {
      FixLineNumber();
      lineNumber = ram[REG_E+0] + ((ram[REG_E+1] &0x0f) << 8);
      }
    lineNumber++;
    }

  if ((flags & 0x03) != 0) {
    if (*line == 0) {
      n = 0;
      while (reverse[cmd].name[n] != 0 && reverse[cmd].name[n] != ' ') {
        token[n] = reverse[cmd].name[n];
        n++;
        }
      token[n] = 0;
      if (FlagSet(52)) sprintf(buffer, "%02d %s ",lineNumber, token);
        else sprintf(buffer,"%s ",token);
      for (i=0; i<(reverse[cmd].flags & 0x03); i++) strcat(buffer,"_");
      while (strlen(buffer) < 12) strcat(buffer," ");
      printf("[%s]\n",buffer);
      if (useLcd) DrawLcd(buffer);
      fgets(line, 1023, stdin);
      while (strlen(line) > 0 && line[strlen(line)-1] < ' ')
        line[strlen(line)-1] = 0;
      line = NextToken(line, token);
      }
    else 
      line = NextToken(line, token);
    if ((flags & 0x08) != 0 && strcasecmp(token,"IND") == 0) {
      ind = 0x80;
      if (*line == 0) {
        n = 0;
        while (reverse[cmd].name[n] != 0 && reverse[cmd].name[n] != ' ') {
          token[n] = reverse[cmd].name[n];
          n++;
          }
        token[n] = 0;
        if (FlagSet(52)) sprintf(buffer,"%02d %s IND ",lineNumber, token);
          else sprintf(buffer,"%s IND ", token);
        for (i=0; i<(reverse[cmd].flags & 0x03); i++) strcat(buffer,"_");
        while (strlen(buffer) < 12) strcat(buffer," ");
        printf("[%s]\n",buffer);
        if (useLcd) DrawLcd(buffer);
        fgets(line, 1023, stdin);
        while (strlen(line) > 0 && line[strlen(line)-1] < ' ')
          line[strlen(line)-1] = 0;
        line = NextToken(line, token);
        }
      else 
        line = NextToken(line, token);
      }
    if (token[0] >= '0' && token[0] <= '9'){
      if (ind) token[2] = 0;
        else token[flags & 0x03] = 0;
      n = atoi(token);
      }
    if ((flags & 0x04) == 0x04 || ind != 0) {
      if (strcasecmp(token, "L") == 0) n = 0x74;
      if (strcasecmp(token, "X") == 0) n = 0x73;
      if (strcasecmp(token, "Y") == 0) n = 0x72;
      if (strcasecmp(token, "Z") == 0) n = 0x71;
      if (strcasecmp(token, "T") == 0) n = 0x70;
      }
    if ((flags & 0x60) != 0) {
      if (token[0] >= 'A' && token[0] <= 'J') n = token[0] - 'A' + 102;
      if (token[0] >= 'a' && token[0] <= 'e') n = token[0] - 'a' + 123;
      }
    }
  else
    n = 0;
  if ((flags & 0xe0) == 0x20) {                  // LBL
    if (token[0] == '"') {
      ram[REG_R+1] = 0xc0;
      if (FlagSet(52)) {
        sprintf(buffer,"LBL %s",token);
        ProgramStep(buffer);
        }
      ram[REG_R+1] = 0x00;
      valid = 0x00;
      return line;
      }
    }
  else if ((flags & 0xe0) == 0x40) {             // GTO
    if (token[0] == '.') {
      if (token[1] == '.') {
        GtoEnd();
        Pack();
        }
      else if (token[1] == '"') {
        n = FindGlobal(token+1);
        if (n != 0) {
          n = ToPtr(n);
          ram[REG_B+1] = (n >> 8) & 0xff;
          ram[REG_B+0] = n & 0xff;
          ram[REG_E+1] |= 0x0f;
          ram[REG_E+0] = 0xff;
          ram[REG_E+0] = 0xff;
          ram[REG_E+1] |= 0x0f;
          }
        }
      else {
        n = atoi(token+1);
        GotoLine(n);
        }
      ram[REG_R+1] = 0x00;
      valid = 0;
      }
    else if (token[0] == '"') {
      ram[REG_R+1] = 0x1d;
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
          ram[REG_E+0] = 0xff;
          ram[REG_E+1] |= 0x0f;
          }
        }
      ram[REG_R+1] = 0x00;
      valid = 0x00;
      return line;
      }
    if (ind != 0) {
      ram[REG_R+1] = 0xae;
      ram[REG_R+0] = n;
      }
    else if (n < 15) {
      ram[REG_R+1] = 0xb1+n;
      ram[REG_R+0] = 0;
      }
    else {
      ram[REG_R+1] = (ind == 0) ? 0xd0 : 0xae;
      ram[REG_R+0] = 0;
      ram[REG_E+2] &= 0xf0;
      ram[REG_E+2] |= ((n & 0x70) >> 4);
      ram[REG_E+1] &= 0x0f;
      ram[REG_E+1] |= ((n & 0x0f) << 4);
      }
    return line;
    }
  else if ((flags & 0xe0) == 0x60) {             // XEQ
    if (token[0] == '"') {
      ram[REG_R+1] = 0x1e;
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
          running = -1;
          ram[REG_E+0] = 0xff;
          ram[REG_E+1] |= 0x0f;
          }
        }
      ram[REG_R+1] = 0x00;
      valid = 0x00;
      return line;
      }
    if (ind != 0) {
      ram[REG_R+1] = 0xae;
      ram[REG_R+0] = n | 0x80;
      }
    else {
      ram[REG_R+1] = 0xe0;
      ram[REG_R+0] = 0;
      ram[REG_E+2] &= 0xf0;
      ram[REG_E+2] |= ((n & 0x70) >> 4);
      ram[REG_E+1] &= 0x0f;
      ram[REG_E+1] |= ((n & 0x0f) << 4);
      }
    return line;
    }
  n |= ind;
  switch (cmd) {
    case 0x01:
              if (n < 15) {                      // LBL
                ram[REG_R+1] = 0x01 + n;
                }
              else {
                ram[REG_R+1] = 0xcf;
                ram[REG_R+0] = n & 0x7f;
                }
              break;

    case 0x20:                                   // RCL
              if (n < 16) {
                ram[REG_R+1] = 0x20 + n;
                }
              else {
                ram[REG_R+1] = 0x90;
                ram[REG_R+0] = n;
                }
              break;
                
    case 0x30:                                   // STO
              if (n < 16) {
                ram[REG_R+1] = 0x30 + n;
                }
              else {
                ram[REG_R+1] = 0x91;
                ram[REG_R+0] = n;
                }
              break;
                
    case 0xc0:                                   // END
              ram[REG_R+1] = 0xc0;
              if (FlagSet(52)) {
                ProgramStep("END");
                }
              ram[REG_R+1] = 0x00;
              valid = 0x00;
                
      default:
              ram[REG_R+0] = n;
              break;
    }
  return line;
  }

int main(int argc, char** argv) {
  int   adr;
  int   dst;
  int   flag;
  int   addr;
  int   i;
  int   j;
  int   instBj;
  char  buffer[1024];
  char  token[32];
  char  token2[32];
  int   isNumber;
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
    if (ram[addr+6] != 0xf0) {
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

/* ****************************** */
/* ***** Program is running ***** */
/* ****************************** */
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
        }
      }

/* ****************************** */
/* ***** No program running ***** */
/* ****************************** */
    else {
      Display(screen);
      strcpy(buffer, screen);
      printf("\n[%s]\n",Text(buffer));
      if (useLcd) DrawLcd(screen);
      if (debug) ShowStatRegs(0);
      ClearFlag(50);
      if (FlagSet(52)) printf("PRGM");
      printf(">");
      fgets(buffer, 1023, stdin);
      while (strlen(buffer) > 0 && buffer[strlen(buffer)-1] < ' ')
        buffer[strlen(buffer)-1] = 0;
      pchar = buffer;
      while (*pchar == ' ') pchar++;

/* ******************************** */
/* ***** Check for \ commands ***** */
/* ******************************** */
      if (*pchar == '\\') {
        Debug(pchar);
        *pchar = 0;
        }

/* ******************************** */
/* ***** Process command line ***** */
/* ******************************** */
      while (*pchar != 0) {
        valid = 0;
        pchar = NextToken(pchar, token);
        isNumber = -1;
        for (i=0; i<strlen(token); i++)
          if (token[i] != '.' && (token[i] < '0' || token[i] > '9')) isNumber = 0;

/* ******************************************* */
/* ***** Process token if it is a number ***** */
/* ******************************************* */
        if (isNumber) {
          if (FlagSet(52)) {
            if (!FlagSet(22)) {
              ram[REG_R+1] = 0x00;
              ProgramStep(NULL);
              }
            SetFlag(22);
            for (i=0; i<strlen(token); i++) {
              if (token[i] >= '0' && token[i] <= '9')
                ram[REG_R+1] = token[i] - '0' + 0x10;
              else if (token[i] == '.') ram[REG_R+1] = 0x1a;
              else ram[REG_R+1] = 0x00;
              ProgramStep(NULL);
              }
//            ProgramStep(token);
            }
          else {
            for (i=0; i<strlen(token); i++) {
              if (token[i] == '.') ram[REG_R+1] = 0x1a;
                else ram[REG_R+1] = token[i] - '0' + 0x10;
              Exec(71);
              }
            }
          }

/* **************************************** */
/* ***** Check and process ALPHA mode ***** */
/* **************************************** */
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
  
          }

/* ******************************************************* */
/* ***** If not a number or Alpha mode, then command ***** */
/* ******************************************************* */
        else {
          i = 0;

/* ********************************************* */
/* ***** Process non programmable commands ***** */
/* ********************************************* */
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

/* ********************************************************* */
/* ***** Process specific calculator key being pressed ***** */
/* ********************************************************* */
          else if (token[0] == '<' && token[strlen(token)-1] == '>') {
            i = 0;
            while (keys[i].cmd != 0xff && strcasecmp(keys[i].key, token) != 0) {
              i++;
              }
            if (keys[i].cmd != 0xff) {

              /* ************************* */
              /* ***** Is key ASNed? ***** */
              /* ************************* */
              if (GetKaFlag(keys[i].keycode)) {

                /* ******************************************* */
                /* ***** Search key assignment registers ***** */
                /* ******************************************* */
                addr = 0x0c0 * 7;
                while (ram[addr+6] == 0xf0 &&
                       ram[addr+0] != keys[i].keycode &&
                       ram[addr+3] != keys[i].keycode) addr += 7;

                /* *********************************************** */
                /* ***** Process if key found in KA register ***** */
                /* *********************************************** */
                if (ram[addr+6] == 0xf0) {
                  valid = 0xff;
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
                  }

                /* *************************************************** */
                /* ***** If not in KA registers, search programs ***** */
                /* *************************************************** */
                else {
                  adr = ((ram[REG_C+1] & 0x0f) << 8) | ram[REG_C+0];
                  adr = FromPtr(adr) + 2;
                  flag = 0;
                  while (flag == 0) {
                    if (ram[adr] >= 0xc0 && ram[adr] <= 0xcd &&
                        ram[adr-2] >= 0xf0 && ram[adr-3] == keys[i].keycode) {
                      flag = 1;
                      }
                    else {
                      dst = ((ram[adr] & 0x0f) << 8) | ram[adr-1];
                      dst = ((dst & 0x1ff) * 7) + ((dst >> 9) & 0x7);
                      if (dst == 0) flag = 2;
                      else adr += dst - 1;
                      }
                    }
                  if (flag == 1) {
                    adr = ToPtr(adr+1);
                    ram[REG_B+1] = (adr >> 8) & 0xff;
                    ram[REG_B+0] = adr & 0xff;
                    ram[REG_E+1] |= 0x0f;
                    ram[REG_E+0] = 0xff;
                    if (FlagSet(22)) EndNumber();
                    running = -1;
                    }

                  /* ****************************************** */
                  /* ***** If still not found, then error ***** */
                  /* ****************************************** */
                  else
                    Message("NONEXISTENT");
                  }
                }

              /* ************************************************** */
              /* ***** Use stadndard command if key not ASNed ***** */
              /* ************************************************** */
              else {
                i = keys[i].cmd;
                if (catalog[i].flags != 0xff) {
                  valid = 0xff;
                  ram[REG_R+1] = catalog[i].cmd;
                  if (FlagSet(22) && ram[REG_R+1] == 0x54)
                    ram[REG_R+1] = 0x1c;
                  }
                }

              }
            /* ************************************************* */
            /* ***** Error if specified key does not exist ***** */
            /* ************************************************* */
            else {
              Message("NONEXISTENT");
              }
            }

/* ******************************************** */
/* ***** Otherwise process normal command ***** */
/* ******************************************** */
          else {
            while (catalog[i].flags != 0xff &&
                   strcasecmp(catalog[i].name, token) != 0) {
              i++;
              }
            if (catalog[i].flags != 0xff) {
              valid = 0xff;
                ram[REG_R+1] = catalog[i].cmd;
                ram[REG_R+0] = 0x00;
                if (FlagSet(22) && ram[REG_R+1] == 0x54)
                  ram[REG_R+1] = 0x1c;
              }
            else {
              i = 0;
              while (catalog2[i].flags != 0xff &&
                     strcasecmp(catalog2[i].name, token) != 0) i++;
              if (catalog2[i].flags == 0xff) Message("NONEXISTENT");
              else {
                valid = 0xff;
                ram[REG_R+1] = catalog2[i].cmd;
                ram[REG_R+0] = catalog2[i].post;
                }
              }
            }

          if (valid) {
            if (ram[REG_R+0] == 0x00 &&
                reverse[ram[REG_R+1]].flags != 0) pchar = Special(pchar);
            if (valid) {
              if (FlagSet(52)) {
                if (ram[REG_R+1] != 0x00) ProgramStep(NULL);
                }
              else if (ram[71] != 0) Exec(71);
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

