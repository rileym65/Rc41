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

typedef struct {
  byte sign;
  byte mantissa[20];
  byte esign;
  int exponent[3];
  } DNUMBER;

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
LINK NUMBER LOGE;
LINK NUMBER ILOGE;
LINK int    debug;
LINK int    dp;
LINK int    lift;
LINK int    running;
LINK int    on;
LINK char   buffer[32];
LINK int    ramClear;
LINK char   screen[32];
LINK int    byteCount;
LINK int    singleStep;
LINK char   printBuffer[1024];
LINK int    printPosition;
LINK int    linksCleared;

#ifdef MAIN
NUMBER  S_ONE  = { 0, { 1,0,0,0,0,0,0,0,0,0 }, 0, { 0,0 } };
DNUMBER S_PI   = { 0, { 3,1,4,1,5,9,2,6,5,3 }, 0, { 0,0 } };
DNUMBER D_ZERO = { 0, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
DNUMBER D_HALF = { 0, { 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 9, { 0,0,1 } };
DNUMBER D_ONE  = { 0, { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
DNUMBER D_TWO  = { 0, { 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, 0, { 0,0,0 } };
DNUMBER D_PI   = { 0, { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4 }, 0, { 0,0,0 } };
DNUMBER D_PI2  = { 0, { 1,5,7,0,7,9,6,3,2,6,7,9,4,8,9,6,6,1,9,2 }, 0, { 0,0,0 } };
#else
extern NUMBER S_ONE;
extern NUMBER S_PI;
extern DNUMBER D_PI;
extern DNUMBER D_PI2;
extern DNUMBER D_ZERO;
extern DNUMBER D_HALF;
extern DNUMBER D_ONE;
extern DNUMBER D_TWO;
#endif

extern NUMBER  Acos(NUMBER a);
extern NUMBER  Add(NUMBER a, NUMBER b);
extern void    AddNumber(char n);
extern void    Arcl(int rreg);
extern NUMBER  Asin(NUMBER a);
extern void    Asto(int rreg);
extern NUMBER  Atan(NUMBER a);
extern NUMBER  AtoN(char* number);
extern void    Aview();
extern void    Bst();
extern int     CardReader(byte function, int addr);
extern void    Cat(char* token);
extern void    Cf(byte n);
extern void    Cle();
extern void    ClearFlag(int f);
extern void    Clp(char* name);
extern void    Clrg();
extern NUMBER  Cos(NUMBER a);
extern DNUMBER D_Add(DNUMBER a, DNUMBER b);
extern DNUMBER D_Div(DNUMBER a, DNUMBER b);
extern DNUMBER D_Mul(DNUMBER a, DNUMBER b);
extern DNUMBER D_Sub(DNUMBER a, DNUMBER b);
extern void    Debug(char* cmd);
extern NUMBER  Dec(NUMBER a);
extern void    Del(char* token);
extern char*   Display(char* buffer);
extern NUMBER  Div(NUMBER a, NUMBER b);
extern NUMBER  DNumberToNumber(DNUMBER a);
extern int     Dse(byte post);
extern void    EMinus();
extern void    Eng(byte n);
extern void    EPlus();
extern void    EReg(byte post);
extern void    Error();
extern NUMBER  Ex(NUMBER a);
extern int     Exec(int addr);
extern NUMBER  Fact(NUMBER a);
extern int     FcQc(byte n);
extern int     FindEnd(int address);
extern int     FindGlobal(char* label);
extern int     FindNextGlobal(int address);
extern int     FindStart(int address);
extern void    Fix(byte n);
extern void    FixLineNumber();
extern int     FlagSet(int f);
extern char*   Format(NUMBER a, char* dest);
extern NUMBER  Fractional(NUMBER a);
extern int     FromPtr(int ptr);
extern int     Fs(byte n);
extern int     FsQc(byte n);
extern void    GetHms(NUMBER a, int* h, int* m, int *s, int *f);
extern int     Gto2(int address);
extern int     GtoAlpha(int address);
extern void    GotoLine(int line);
extern int     GtoXeq(int address);
extern int     GtoXeqInd(int address);
extern NUMBER  Hms(NUMBER a);
extern NUMBER  HmsMinus(NUMBER a, NUMBER b);
extern NUMBER  HmsPlus(NUMBER a, NUMBER b);
extern NUMBER  Hr(NUMBER a);
extern void    Init();
extern NUMBER  Integer(NUMBER a);
extern int     Isg(byte post);
extern int     IsInteger(NUMBER a);
extern int     isize(int address);
extern int     IsZero(NUMBER a);
extern NUMBER  Ln(NUMBER a);
extern NUMBER  Ln1PlusX(NUMBER a);
extern void    Mean();
extern void    Message(char* msg);
extern NUMBER  Mod(NUMBER x, NUMBER y);
extern NUMBER  Mul(NUMBER a, NUMBER b);
extern NUMBER  Normalize(NUMBER N);
extern char*   NtoA(NUMBER a,char* buffer);
extern DNUMBER NumberToDNumber(NUMBER a);
extern NUMBER  Oct(NUMBER a);
extern void    Pack();
extern void    Printer(byte function);
extern void    ProgramByte(byte b);
extern char*   ProgramLine(char* buffer);
extern char*   ProgramList(int lineNumber, int adr, char* dest);
extern void    ProgramStep(char* line);
extern void    Prp(char* name);
extern void    Push(int address);
extern NUMBER  Rcl(int rreg);
extern NUMBER  RecallNumber(int reg);
extern void    Rnd();
extern int     Rtn(int address);
extern void    Sci(byte n);
extern void    Sdev();
extern void    SetFlag(int f);
extern void    SetX(NUMBER n, int l, int s);
extern void    Sf(byte n);
extern void    ShowNumber(NUMBER n);
extern void    ShowStatRegs(int stackOnly);
extern NUMBER  Sin(NUMBER a);
extern void    Size(char* token);
extern int     Skip(int addr);
extern NUMBER  Sqrt(NUMBER a);
extern void    Sst();
extern void    Sto(NUMBER a,int rreg);
extern void    StoreNumber(NUMBER n, int reg);
extern NUMBER  Sub(NUMBER a, NUMBER b);
extern NUMBER  Tan(NUMBER a);
extern NUMBER  TensCompliment(NUMBER a);
extern int     ToInteger(NUMBER a);
extern void    Tone(byte n);
extern int     ToPtr(int addr);
extern void    View(byte post);
extern void    Wprg(char* name);
extern NUMBER  YtoX(NUMBER y, NUMBER x);


#endif

# define M_El           2.718281828459045235360287471352662498L /* e */
# define M_LOG2El       1.442695040888963407359924681001892137L /* log_2 e */
# define M_LOG10El      0.434294481903251827651128918916605082L /* log_10 e */
# define M_LN2l         0.693147180559945309417232121458176568L /* log_e 2 */
# define M_LN10l        2.302585092994045684017991454684364208L /* log_e 10 */
# define M_PIl          3.141592653589793238462643383279502884L /* pi */
# define M_PI_2l        1.570796326794896619231321691639751442L /* pi/2 */
# define M_PI_4l        0.785398163397448309615660845819875721L /* pi/4 */
# define M_1_PIl        0.318309886183790671537767526745028724L /* 1/pi */
# define M_2_PIl        0.636619772367581343075535053490057448L /* 2/pi */
# define M_2_SQRTPIl    1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
# define M_SQRT2l       1.414213562373095048801688724209698079L /* sqrt(2) */
# define M_SQRT1_2l     0.707106781186547524400844362104849039L /* 1/sqrt(2) */

