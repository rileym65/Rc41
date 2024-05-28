#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>


#ifndef MAIN
#define LINK extern
#else
#define LINK
#endif

typedef unsigned char byte;

#include "commands.h"

#define RAMSIZE 28672
#define REG_T       0
#define REG_Z       7
#define REG_Y      14
#define REG_X      21
#define REG_L      28
#define REG_M      35
#define REG_N      42
#define REG_O      49
#define REG_P      56
#define REG_Q      63
#define REG_R      70
#define REG_A      77
#define REG_B      84
#define REG_C      91
#define REG_D      98
#define REG_E     105
#define LIFT      112
#define PENDING   113

#define R_T         0
#define R_Z         1
#define R_Y         2
#define R_X         3
#define R_L         4
#define R_M         5
#define R_N         6
#define R_O         7
#define R_P         8
#define R_Q         9
#define R_R        10
#define R_A        11
#define R_B        12
#define R_C        13
#define R_D        14
#define R_E        15

typedef struct {
  byte sign;
  byte mantissa[10];
  byte esign;
  byte exponent[2];
  } NUMBER;

LINK char display[32];
LINK byte ram[RAMSIZE];
LINK NUMBER a;
LINK NUMBER b;
LINK NUMBER c;
LINK NUMBER ZERO;
LINK NUMBER ONE;
LINK NUMBER NEGONE;
LINK NUMBER PI;
LINK NUMBER DTOR;
LINK NUMBER RTOD;
LINK NUMBER GTOR;
LINK NUMBER RTOG;
LINK NUMBER E;
LINK NUMBER TEN;
LINK int    debug;
LINK int    dp;
LINK int    lift;
LINK int    running;
LINK int    on;
LINK char   buffer[32];
LINK int    ramClear;
LINK char   screen[32];
LINK int    byteCount;

extern NUMBER Add(NUMBER a, NUMBER b);
extern void   AddNumber(char n);
extern void   Arcl(int rreg);
extern void   Asto(int rreg);
extern NUMBER AtoN(char* number);
extern void   Aview();
extern void   Bst();
extern void   Cat(char* token);
extern void   Cf(byte n);
extern void   Cle();
extern void   ClearFlag(int f);
extern void   Clrg();
extern void   Debug(char* cmd);
extern NUMBER Dec(NUMBER a);
extern void   Del(char* token);
extern char*  Display(char* buffer);
extern NUMBER Div(NUMBER a, NUMBER b);
extern int    Dse(byte post);
extern void   EMinus();
extern void   Eng(byte n);
extern void   EPlus();
extern void   EReg(byte post);
extern int    Exec(int addr);
extern NUMBER Fact(NUMBER a);
extern int    FcQc(byte n);
extern int    FindEnd(int address);
extern int    FindGlobal(char* label);
extern int    FindNextGlobal(int address);
extern int    FindStart(int address);
extern void   Fix(byte n);
extern void   FixLineNumber();
extern int    FlagSet(int f);
extern char*  Format(NUMBER a, char* dest);
extern NUMBER Fractional(NUMBER a);
extern int    FromPtr(int ptr);
extern int    Fs(byte n);
extern int    FsQc(byte n);
extern void   GetHms(NUMBER a, int* h, int* m, int *s, int *f);
extern int    Gto2(int address);
extern int    GtoAlpha(int address);
extern void   GotoLine(int line);
extern int    GtoXeq(int address);
extern NUMBER Hms(NUMBER a);
extern NUMBER HmsMinus(NUMBER a, NUMBER b);
extern NUMBER HmsPlus(NUMBER a, NUMBER b);
extern NUMBER Hr(NUMBER a);
extern void   Init();
extern NUMBER Integer(NUMBER a);
extern int    Isg(byte post);
extern int    isize(int address);
extern int    IsZero(NUMBER a);
extern void   Mean();
extern void   Message(char* msg);
extern NUMBER Mod(NUMBER x, NUMBER y);
extern NUMBER Mul(NUMBER a, NUMBER b);
extern NUMBER Normalize(NUMBER N);
extern char*  NtoA(NUMBER a,char* buffer);
extern NUMBER Oct(NUMBER a);
extern void   Pack();
extern void   ProgramByte(byte b);
extern char*  ProgramLine(char* buffer);
extern void   ProgramStep(char* line);
extern void   Push(int address);
extern NUMBER Rcl(int rreg);
extern NUMBER RecallNumber(int reg);
extern void   Rnd();
extern int    Rtn(int address);
extern void   Sci(byte n);
extern void   Sdev();
extern void   SetFlag(int f);
extern void   SetX(NUMBER n, int l, int s);
extern void   Sf(byte n);
extern void   ShowNumber(NUMBER n);
extern void   ShowStatRegs(int stackOnly);
extern void   Size(char* token);
extern int    Skip(int addr);
extern void   Sst();
extern void   Sto(NUMBER a,int rreg);
extern void   StoreNumber(NUMBER n, int reg);
extern NUMBER Sub(NUMBER a, NUMBER b);
extern NUMBER TensCompliment(NUMBER a);
extern int    ToInteger(NUMBER a);
extern void   Tone(byte n);
extern int    ToPtr(int addr);
extern void   View(byte post);


#endif

