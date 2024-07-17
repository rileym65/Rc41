#ifndef _CMDS_H
#define _CMDS_H

/* Flags byte
   bit 0 - 1 character input
       1 - 2 character input
       2 - 3 character input
       3 - allow stack
       4 - indirect
       5 - alpha
       6
       7 - Not in program

   bit 0 \ 00  - no arg
       1 / 01  - 1 digit arg
           10  - 2 digit arg
           11  - 3 digit arg
       2       - allow stack (X,Y,Z,T,L)
       3       - allow indirect
       4       - alpha arg
       5 \ 000 - no special handling
       6 / 001 - LBL handling
       7   010 - GTO handling
           011 - XEQ handling
           100 - RCL handling
           101 - STO handling
           110 - END handling
      15       - not in program
*/

typedef struct {
  char *name;
  byte  cmd;
  int   key;
  word  flags;
  } CATALOG;

#ifdef MAIN

CATALOG catalog[] = {
    { "0",       0x10,   82,    0 },    /*  00 */
    { "1",       0x11,   72,    0 },    /*  01 */
    { "2",       0x12,   73,    0 },    /*  02 */
    { "3",       0x13,   74,    0 },    /*  03 */
    { "4",       0x14,   62,    0 },    /*  04 */
    { "5",       0x15,   63,    0 },    /*  05 */
    { "6",       0x16,   64,    0 },    /*  06 */
    { "7",       0x17,   52,    0 },    /*  07 */
    { "8",       0x18,   53,    0 },    /*  08 */
    { "9",       0x19,   54,    0 },    /*  09 */
    { ".",       0x1a,   83,    0 },    /*  10 */
    { "EEX",     0x1b,   44, 0x80 },    /*  11 */
    { "+",       0x40,   61,    0 },    /*  12 */
    { "-",       0x41,   41,    0 },    /*  13 */
    { "*",       0x42,   71,    0 },    /*  14 */
    { "/",       0x43,   81,    0 },    /*  15 */
    { "1/X",     0x60,   12,    0 },    /*  16 */
    { "10^X",    0x57,  -14,    0 },    /*  17 */
    { "ABS",     0x61,   00,    0 },    /*  18 */
    { "ACOS",    0x5d,  -24,    0 },    /*  19 */
    { "ADV",     0x8f,   00,    0 },    /*  20 */
    { "AOFF",    0x8b,   00,    0 },    /*  21 */
    { "AON",     0x8c,   00,    0 },    /*  22 */
    { "ARCL",    0x9b,  -34, 0x15 },    /*  23 */
    { "ASHF",    0x88,   00,    0 },    /*  24 */
    { "ASIN",    0x5c,  -23,    0 },    /*  25 */
    { "ASN",     0x00,  -32, 0x80 },    /*  26 */
    { "ASTO",    0x9a,  -33, 0x15 },    /*  27 */
    { "ATAN",    0x5e,  -25,    0 },    /*  28 */
    { "AVIEW",   0x7e,  -84,    0 },    /*  29 */
    { "BEEP",    0x86,  -62,    0 },    /*  30 */
    { "BST",     0x00,  -35, 0x80 },    /*  31 */
    { "CAT",     0x00,   41, 0x80 },    /*  32 */
    { "CF",      0xa9,  -53, 0x12 },    /*  33 */
    { "CHS",     0x54,   43,    0 },    /*  34 */
    { "CLA",     0x87,  -45,    0 },    /*  35 */
    { "CLD",     0x7f,   00,    0 },    /*  36 */
    { "CLE",     0x70,  -21,    0 },    /*  37 */
    { "CLP",     0x00,   00, 0x80 },    /*  38 */
    { "CLRG",    0x8a,   00,    0 },    /*  39 */
    { "CLST",    0x73,   00,    0 },    /*  40 */
    { "CLX",     0x77,  -45,    0 },    /*  41 */
    { "COS",     0x5a,   24,    0 },    /*  42 */
    { "D-R",     0x6a,   00,    0 },    /*  43 */
    { "DEC",     0x5f,   00,    0 },    /*  44 */
    { "DEG",     0x80,   00,    0 },    /*  45 */
    { "DEL",     0x00,   00, 0x80 },    /*  46 */
    { "DSE",     0x97,   00, 0x1a },    /*  47 */
    { "E^X",     0x55,  -15,    0 },    /*  48 */
    { "E^X-1",   0x58,   00,    0 },    /*  49 */
    { "END",     0xc0,   00,    0 },    /*  50 */
    { "ENG",     0x9e,  -74, 0x11 },    /*  51 */
    { "ENTER^",  0x83,   41,    0 },    /*  52 */
    { "FACT",    0x62,   00,    0 },    /*  53 */
    { "FC?",     0xad,   00, 0x12 },    /*  54 */
    { "FC?C",    0xab,   00, 0x12 },    /*  55 */
    { "FIX",     0x9c,  -72, 0x11 },    /*  56 */
    { "FRC",     0x69,   00,    0 },    /*  57 */
    { "FS?",     0xac,  -54, 0x12 },    /*  58 */
    { "FS?C",    0xaa,   00, 0x12 },    /*  59 */
    { "GRAD",    0x82,   00,    0 },    /*  60 */
    { "GTO",     0xb1,  -34,    0 },    /*  61 */
    { "HMS",     0x6c,   00,    0 },    /*  62 */
    { "HMS+",    0x49,   00,    0 },    /*  63 */
    { "HMS-",    0x4a,   00,    0 },    /*  64 */
    { "HR",      0x6d,   00,    0 },    /*  65 */
    { "INT",     0x68,   00,    0 },    /*  66 */
    { "ISG",     0x96,  -43, 0x1a },    /*  67 */
    { "LASTX",   0x76,  -83,    0 },    /*  68 */
    { "LBL",     0x01,  -33,    0 },    /*  69 */
    { "LOG",     0x56,   14,    0 },    /*  70 */
    { "LN",      0x50,   15,    0 },    /*  71 */
    { "LN1+X",   0x65,   00,    0 },    /*  72 */
    { "MEAN",    0x7c,   00,    0 },    /*  73 */
    { "MOD",     0x4b,   00,    0 },    /*  74 */
    { "OCT",     0x6f,   00,    0 },    /*  75 */
    { "OFF",     0x8d,   00,    0 },    /*  76 */
    { "ON",      0x00,   00, 0x80 },    /*  77 */
    { "P-R",     0x4e,   63,    0 },    /*  78 */
    { "PACK",    0x00,   00, 0x80 },    /*  79 */
    { "%",       0x4c,  -22,    0 },    /*  80 */
    { "%CH",     0x4d,   00,    0 },    /*  81 */
    { "PI",      0x72,  -82,    0 },    /*  82 */
    { "PROMPT",  0x8e,   00,    0 },    /*  83 */
    { "PSE",     0x89,   00,    0 },    /*  84 */
    { "R^",      0x74,   00,    0 },    /*  85 */
    { "R-D",     0x6b,   00,    0 },    /*  86 */
    { "R-P",     0x4f,   64,    0 },    /*  87 */
    { "RAD",     0x81,   00,    0 },    /*  88 */
    { "RCL",     0x20,   34, 0x1a },    /*  89 */
    { "RDN",     0x75,   22,    0 },    /*  90 */
    { "RND",     0x6e,   00,    0 },    /*  91 */
    { "RTN",     0x85,  -44,    0 },    /*  92 */
    { "SDEV",    0x7d,   00,    0 },    /*  93 */
    { "SCI",     0x9d,  -73, 0x11 },    /*  94 */
    { "SF",      0xa8,  -52, 0x12 },    /*  95 */
    { "E+",      0x47,   11,    0 },    /*  96 */
    { "E-",      0x48,  -11,    0 },    /*  97 */
    { "EREG",    0x99,   00, 0x12 },    /*  98 */
    { "SIN",     0x59,   23,    0 },    /*  99 */
    { "SIGN",    0x7a,   00,    0 },    /* 100 */
    { "SIZE",    0x00,   00, 0x80 },    /* 101 */
    { "SQRT",    0x52,   13,    0 },    /* 102 */
    { "SST",     0x00,   35, 0x80 },    /* 103 */
    { "ST+",     0x92,   00, 0x12 },    /* 104 */
    { "ST-",     0x93,   00, 0x12 },    /* 105 */
    { "ST*",     0x94,   00, 0x12 },    /* 106 */
    { "ST/",     0x95,   00, 0x12 },    /* 107 */
    { "STO",     0x30,   33,    0 },    /* 108 */
    { "STOP",    0x84,   00,    0 },    /* 109 */
    { "TAN",     0x5b,   25,    0 },    /* 110 */
    { "TONE",    0x9f,   00, 0x11 },    /* 111 */
    { "VIEW",    0x98,  -84, 0x12 },    /* 112 */
    { "X=0?",    0x67,  -81,    0 },    /* 113 */
    { "X<>0?",   0x63,   00,    0 },    /* 114 */
    { "X<0?",    0x66,   00,    0 },    /* 115 */
    { "X<=0?",   0x7b,   00,    0 },    /* 116 */
    { "X>0?",    0x64,   00,    0 },    /* 117 */
    { "X=Y?",    0x78,  -51,    0 },    /* 118 */
    { "X<>Y?",   0x79,   00,    0 },    /* 119 */
    { "X<Y?",    0x44,   00,    0 },    /* 120 */
    { "X<=Y?",   0x46,   61,    0 },    /* 121 */
    { "X>Y?",    0x45,  -71,    0 },    /* 122 */
    { "X<>",     0xce,   00, 0x12 },    /* 123 */
    { "X<>Y",    0x71,   21,    0 },    /* 124 */
    { "XEQ",     0x1e,   32,    0 },    /* 125 */
    { "X^2",     0x51,  -13,    0 },    /* 126 */
    { "Y^X",     0x53,  -12,    0 },    /* 127 */
    { "",        0x00,   00, 0xff }     /* 128 */
  };
#else
extern CATALOG catalog[];
#endif

typedef struct {
  int number;
  char* name;
  int   size;
  } REV;

#ifdef MAIN
// High nybble of size
// 0x10 - Alpha destination follows
// 0x20 - XROM follows
// 0x30 - GTO IND/XEQ IND
// 0x40 - 2-byte GTO/LBL
// 0x50 - GLOBAL
// 0x60 - 3-byte GTO/XEQ
// 0x70 - Text line
// 0x80 - Second byte is 0-9
// 0x90 - local label


REV reverse[] = {
    { 0x00, "",           0x01 },
    { 0x01, "LBL 00",     0x01 },
    { 0x02, "LBL 01",     0x01 },
    { 0x03, "LBL 02",     0x01 },
    { 0x04, "LBL 03",     0x01 },
    { 0x05, "LBL 04",     0x01 },
    { 0x06, "LBL 05",     0x01 },
    { 0x07, "LBL 06",     0x01 },
    { 0x08, "LBL 07",     0x01 },
    { 0x09, "LBL 08",     0x01 },
    { 0x0a, "LBL 09",     0x01 },
    { 0x0b, "LBL 10",     0x01 },
    { 0x0c, "LBL 11",     0x01 },
    { 0x0d, "LBL 12",     0x01 },
    { 0x0e, "LBL 13",     0x01 },
    { 0x0f, "LBL 14",     0x01 },
    { 0x10, "0",          0x01 },
    { 0x11, "1",          0x01 },
    { 0x12, "2",          0x01 },
    { 0x13, "3",          0x01 },
    { 0x14, "4",          0x01 },
    { 0x15, "5",          0x01 },
    { 0x16, "6",          0x01 },
    { 0x17, "7",          0x01 },
    { 0x18, "8",          0x01 },
    { 0x19, "9",          0x01 },
    { 0x1a, ".",          0x01 },
    { 0x1b, "EEX",        0x01 },
    { 0x1c, "CHS",        0x01 },
    { 0x1d, "GTO",        0x13 },
    { 0x1e, "XEQ",        0x13 },
    { 0x1f, "",           0x01 },
    { 0x20, "RCL 00",     0x01 },
    { 0x21, "RCL 01",     0x01 },
    { 0x22, "RCL 02",     0x01 },
    { 0x23, "RCL 03",     0x01 },
    { 0x24, "RCL 04",     0x01 },
    { 0x25, "RCL 05",     0x01 },
    { 0x26, "RCL 06",     0x01 },
    { 0x27, "RCL 07",     0x01 },
    { 0x28, "RCL 08",     0x01 },
    { 0x29, "RCL 09",     0x01 },
    { 0x2a, "RCL 10",     0x01 },
    { 0x2b, "RCL 11",     0x01 },
    { 0x2c, "RCL 12",     0x01 },
    { 0x2d, "RCL 13",     0x01 },
    { 0x2e, "RCL 14",     0x01 },
    { 0x2f, "RCL 15",     0x01 },
    { 0x30, "STO 00",     0x01 },
    { 0x31, "STO 01",     0x01 },
    { 0x32, "STO 02",     0x01 },
    { 0x33, "STO 03",     0x01 },
    { 0x34, "STO 04",     0x01 },
    { 0x35, "STO 05",     0x01 },
    { 0x36, "STO 06",     0x01 },
    { 0x37, "STO 07",     0x01 },
    { 0x38, "STO 08",     0x01 },
    { 0x39, "STO 09",     0x01 },
    { 0x3a, "STO 10",     0x01 },
    { 0x3b, "STO 11",     0x01 },
    { 0x3c, "STO 12",     0x01 },
    { 0x3d, "STO 13",     0x01 },
    { 0x3e, "STO 14",     0x01 },
    { 0x3f, "STO 15",     0x01 },
    { 0x40, "+",          0x01 },
    { 0x41, "-",          0x01 },
    { 0x42, "*",          0x01 },
    { 0x43, "/",          0x01 },
    { 0x44, "X<Y?",       0x01 },
    { 0x45, "X>Y?",       0x01 },
    { 0x46, "X<=Y?",      0x01 },
    { 0x47, "E+",         0x01 },
    { 0x48, "E-",         0x01 },
    { 0x49, "HMS+",       0x01 },
    { 0x4a, "HMS-",       0x01 },
    { 0x4b, "MOD",        0x01 },
    { 0x4c, "%",          0x01 },
    { 0x4d, "%CH",        0x01 },
    { 0x4e, "P-R",        0x01 },
    { 0x4f, "R-P",        0x01 },
    { 0x50, "LN",         0x01 },
    { 0x51, "X^2",        0x01 },
    { 0x52, "SQRT",       0x01 },
    { 0x53, "Y^X",        0x01 },
    { 0x54, "CHS",        0x01 },
    { 0x55, "E^X",        0x01 },
    { 0x56, "LOG",        0x01 },
    { 0x57, "10^X",       0x01 },
    { 0x58, "E^X-1",      0x01 },
    { 0x59, "SIN",        0x01 },
    { 0x5a, "COS",        0x01 },
    { 0x5b, "TAN",        0x01 },
    { 0x5c, "ASIN",       0x01 },
    { 0x5d, "ACOS",       0x01 },
    { 0x5e, "ATAN",       0x01 },
    { 0x5f, "DEC",        0x01 },
    { 0x60, "1/X",        0x01 },
    { 0x61, "ABS",        0x01 },
    { 0x62, "FACT",       0x01 },
    { 0x63, "X<>0?",      0x01 },
    { 0x64, "X>0?",       0x01 },
    { 0x65, "LN1+X",      0x01 },
    { 0x66, "X<0?",       0x01 },
    { 0x67, "X=0?",       0x01 },
    { 0x68, "INT",        0x01 },
    { 0x69, "FRC",        0x01 },
    { 0x6a, "D-R",        0x01 },
    { 0x6b, "R-D",        0x01 },
    { 0x6c, "HMS",        0x01 },
    { 0x6d, "HR",         0x01 },
    { 0x6e, "RND",        0x01 },
    { 0x6f, "OCT",        0x01 },
    { 0x70, "CLE",        0x01 },
    { 0x71, "X<>Y",       0x01 },
    { 0x72, "PI",         0x01 },
    { 0x73, "CLST",       0x01 },
    { 0x74, "R^",         0x01 },
    { 0x75, "RDN",        0x01 },
    { 0x76, "LASTX",      0x01 },
    { 0x77, "CLX",        0x01 },
    { 0x78, "X=Y?",       0x01 },
    { 0x79, "X<>Y?",      0x01 },
    { 0x7a, "SIGN",       0x01 },
    { 0x7b, "X<=0?",      0x01 },
    { 0x7c, "MEAN",       0x01 },
    { 0x7d, "SDEV",       0x01 },
    { 0x7e, "AVIEW",      0x01 },
    { 0x7f, "CLD",        0x01 },
    { 0x80, "DEG",        0x01 },
    { 0x81, "RAD",        0x01 },
    { 0x82, "GRAD",       0x01 },
    { 0x83, "ENTER^",     0x01 },
    { 0x84, "STOP",       0x01 },
    { 0x85, "RTN",        0x01 },
    { 0x86, "BEEP",       0x01 },
    { 0x87, "CLA",        0x01 },
    { 0x88, "ASHF",       0x01 },
    { 0x89, "PSE",        0x01 },
    { 0x8a, "CLRG",       0x01 },
    { 0x8b, "AOFF",       0x01 },
    { 0x8c, "AON",        0x01 },
    { 0x8d, "OFF",        0x01 },
    { 0x8e, "PROMPT",     0x01 },
    { 0x8f, "ADV",        0x01 },
    { 0x90, "RCL",        0x02 },
    { 0x91, "STO",        0x02 },
    { 0x92, "ST+",        0x02 },
    { 0x93, "ST-",        0x02 },
    { 0x94, "ST*",        0x02 },
    { 0x95, "ST/",        0x02 },
    { 0x96, "ISG",        0x02 },
    { 0x97, "DSE",        0x02 },
    { 0x98, "VIEW",       0x02 },
    { 0x99, "EREG",       0x02 },
    { 0x9a, "ASTO",       0x02 },
    { 0x9b, "ARCL",       0x02 },
    { 0x9c, "FIX",        0x82 },
    { 0x9d, "SCI",        0x82 },
    { 0x9e, "ENG",        0x82 },
    { 0x9f, "TONE",       0x82 },
    { 0xa0, "XROM",       0x22 },
    { 0xa1, "XROM",       0x22 },
    { 0xa2, "XROM",       0x22 },
    { 0xa3, "XROM",       0x22 },
    { 0xa4, "XROM",       0x22 },
    { 0xa5, "XROM",       0x22 },
    { 0xa6, "XROM",       0x22 },
    { 0xa7, "XROM",       0x22 },
    { 0xa8, "SF",         0x02 },
    { 0xa9, "CF",         0x02 },
    { 0xaa, "FS?C",       0x02 },
    { 0xab, "FC?C",       0x02 },
    { 0xac, "FS?",        0x02 },
    { 0xad, "FC?",        0x02 },
    { 0xae, "GTO",        0x32 },
    { 0xaf, "",           0x02 },
    { 0xb0, "",           0x01 },
    { 0xb1, "GTO 00",     0x42 },
    { 0xb2, "GTO 01",     0x42 },
    { 0xb3, "GTO 02",     0x42 },
    { 0xb4, "GTO 03",     0x42 },
    { 0xb5, "GTO 04",     0x42 },
    { 0xb6, "GTO 05",     0x42 },
    { 0xb7, "GTO 06",     0x42 },
    { 0xb8, "GTO 07",     0x42 },
    { 0xb9, "GTO 08",     0x42 },
    { 0xba, "GTO 09",     0x42 },
    { 0xbb, "GTO 10",     0x42 },
    { 0xbc, "GTO 11",     0x42 },
    { 0xbd, "GTO 12",     0x42 },
    { 0xbe, "GTO 13",     0x42 },
    { 0xbf, "GTO 14",     0x42 },
    { 0xc0, "GLOBAL",     0x53 },
    { 0xc1, "GLOBAL",     0x53 },
    { 0xc2, "GLOBAL",     0x53 },
    { 0xc3, "GLOBAL",     0x53 },
    { 0xc4, "GLOBAL",     0x53 },
    { 0xc5, "GLOBAL",     0x53 },
    { 0xc6, "GLOBAL",     0x53 },
    { 0xc7, "GLOBAL",     0x53 },
    { 0xc8, "GLOBAL",     0x53 },
    { 0xc9, "GLOBAL",     0x53 },
    { 0xca, "GLOBAL",     0x53 },
    { 0xcb, "GLOBAL",     0x53 },
    { 0xcc, "GLOBAL",     0x53 },
    { 0xcd, "GLOBAL",     0x53 },
    { 0xce, "X<>",        0x02 },
    { 0xcf, "LBL",        0x92 },
    { 0xd0, "GTO",        0x63 },
    { 0xd1, "GTO",        0x63 },
    { 0xd2, "GTO",        0x63 },
    { 0xd3, "GTO",        0x63 },
    { 0xd4, "GTO",        0x63 },
    { 0xd5, "GTO",        0x63 },
    { 0xd6, "GTO",        0x63 },
    { 0xd7, "GTO",        0x63 },
    { 0xd8, "GTO",        0x63 },
    { 0xd9, "GTO",        0x63 },
    { 0xda, "GTO",        0x63 },
    { 0xdb, "GTO",        0x63 },
    { 0xdc, "GTO",        0x63 },
    { 0xdd, "GTO",        0x63 },
    { 0xde, "GTO",        0x63 },
    { 0xdf, "GTO",        0x63 },
    { 0xe0, "XEQ",        0x63 },
    { 0xe1, "XEQ",        0x63 },
    { 0xe2, "XEQ",        0x63 },
    { 0xe3, "XEQ",        0x63 },
    { 0xe4, "XEQ",        0x63 },
    { 0xe5, "XEQ",        0x63 },
    { 0xe6, "XEQ",        0x63 },
    { 0xe7, "XEQ",        0x63 },
    { 0xe8, "XEQ",        0x63 },
    { 0xe9, "XEQ",        0x63 },
    { 0xea, "XEQ",        0x63 },
    { 0xeb, "XEQ",        0x63 },
    { 0xec, "XEQ",        0x63 },
    { 0xed, "XEQ",        0x63 },
    { 0xee, "XEQ",        0x63 },
    { 0xef, "XEQ",        0x63 },
    { 0xf0, "",           0x71 },
    { 0xf1, "",           0x72 },
    { 0xf2, "",           0x73 },
    { 0xf3, "",           0x74 },
    { 0xf4, "",           0x75 },
    { 0xf5, "",           0x76 },
    { 0xf6, "",           0x77 },
    { 0xf7, "",           0x78 },
    { 0xf8, "",           0x79 },
    { 0xf9, "",           0x7a },
    { 0xfa, "",           0x7b },
    { 0xfb, "",           0x7c },
    { 0xfc, "",           0x7d },
    { 0xfd, "",           0x7e },
    { 0xfe, "",           0x7f },
    { 0xff, "",           0x70 },
  };
#else
extern REV reverse[];
#endif


typedef struct {
  char *name;
  byte  cmd;
  byte  post;
  byte  flags;
  } CATALOG2;

#ifdef MAIN

CATALOG2 catalog2[] = {
    { "ACA",     0xa7, 0x41,    0 },
    { "ACCHR",   0xa7, 0x42,    0 },
    { "ACCOL",   0xa7, 0x43,    0 },
    { "ACSPEC",  0xa7, 0x44,    0 },
    { "ACX",     0xa7, 0x45,    0 },
    { "BLDSPEC", 0xa7, 0x46,    0 },
    { "PRA",     0xa7, 0x48,    0 },
    { "PRBUF",   0xa7, 0x4a,    0 },
    { "PRFLAGS", 0xa7, 0x4b,    0 },
    { "PRKEYS",  0xa7, 0x4c,    0 },
    { "PRP",     0xa7, 0x4d,    0 },
    { "PRREG",   0xa7, 0x50,    0 },
    { "PRREGX",  0xa7, 0x51,    0 },
    { "PRE",     0xa7, 0x52,    0 },
    { "PRSTK",   0xa7, 0x53,    0 },
    { "PRX",     0xa7, 0x54,    0 },
    { "SKPCHR",  0xa7, 0x56,    0 },
    { "SKPCOL",  0xa7, 0x57,    0 },

    { "RDTA",    0xa7, 0x82,    0 },
    { "RDTAX",   0xa7, 0x83,    0 },
    { "VER",     0xa7, 0x85,    0 },
    { "WALL",    0xa7, 0x86,    0 },
    { "WDTA",    0xa7, 0x87,    0 },
    { "WDTAX",   0xa7, 0x88,    0 },
    { "WSTS",    0xa7, 0x8a,    0 },
    { "7CLREG",  0xa7, 0x8b,    0 },
    { "7DSP0",   0xa7, 0x8c,    0 },
    { "7DSP1",   0xa7, 0x8d,    0 },
    { "7DSP2",   0xa7, 0x8e,    0 },
    { "7DSP3",   0xa7, 0x8f,    0 },
    { "7DSP4",   0xa7, 0x90,    0 },
    { "7DSP5",   0xa7, 0x91,    0 },
    { "7DSP6",   0xa7, 0x92,    0 },
    { "7DSP7",   0xa7, 0x93,    0 },
    { "7DSP8",   0xa7, 0x94,    0 },
    { "7DSP9",   0xa7, 0x95,    0 },
    { "7DSPI",   0xa7, 0x96,    0 },
    { "7DSZ",    0xa7, 0x97,    0 },
    { "7DSZI",   0xa7, 0x98,    0 },
    { "7ENG",    0xa7, 0x99,    0 },
    { "7FIX",    0xa7, 0x9a,    0 },
    { "7ISZ",    0xa7, 0x9d,    0 },
    { "7ISZI",   0xa7, 0x9e,    0 },
    { "7P<>S",   0xa7, 0x9f,    0 },
    { "7SCI",    0xa7, 0xa4,    0 },

    { "CREATE",  0xa7, 0x01,    0 },
    { "DIR",     0xa7, 0x02,    0 },
    { "NEWM",    0xa7, 0x03,    0 },
    { "PURGE",   0xa7, 0x04,    0 },
    { "READA",   0xa7, 0x05,    0 },
    { "READK",   0xa7, 0x06,    0 },
    { "READP",   0xa7, 0x07,    0 },
    { "READR",   0xa7, 0x08,    0 },
    { "READRX",  0xa7, 0x09,    0 },
    { "READS",   0xa7, 0x0a,    0 },
    { "READSUB", 0xa7, 0x0b,    0 },
    { "RENAME",  0xa7, 0x0c,    0 },
    { "SEC",     0xa7, 0x0d,    0 },
    { "SEEKR",   0xa7, 0x0e,    0 },
    { "UNSEC",   0xa7, 0x0f,    0 },
    { "VERIFY",  0xa7, 0x10,    0 },
    { "WRTA",    0xa7, 0x11,    0 },
    { "WRTK",    0xa7, 0x12,    0 },
    { "WRTP",    0xa7, 0x13,    0 },
    { "WRTPV",   0xa7, 0x14,    0 },
    { "WRTR",    0xa7, 0x15,    0 },
    { "WRTRX",   0xa7, 0x16,    0 },
    { "WRTS",    0xa7, 0x17,    0 },
    { "ZERO",    0xa7, 0x18,    0 },
    { "",        0x00, 0x00, 0xff }
  };

#else

extern CATALOG2 catalog2[];

#endif

typedef struct {
  byte cmd;
  byte post;
  char* name;
  } REV2;

#ifdef MAIN

REV2 reverse2[] = {
  { 0xa7, 0x41, "ACA"       },
  { 0xa7, 0x42, "ACCHR"     },
  { 0xa7, 0x43, "ACCOL"     },
  { 0xa7, 0x44, "ACSPEC"    },
  { 0xa7, 0x45, "ACX"       },
  { 0xa7, 0x46, "BLDSPEC"   },
  { 0xa7, 0x48, "PRA"       },
  { 0xa7, 0x4a, "PRBUF"     },
  { 0xa7, 0x4b, "PRFLAGS"   },
  { 0xa7, 0x4c, "PRKEYS"    },
  { 0xa7, 0x50, "PRREG"     },
  { 0xa7, 0x51, "PRREGX"    },
  { 0xa7, 0x52, "PRE"       },
  { 0xa7, 0x53, "PRSTACK"   },
  { 0xa7, 0x54, "PRX"       },
  { 0xa7, 0x56, "SKPCHR"    },
  { 0xa7, 0x57, "SKPCOL"    },

  { 0xa7, 0x82, "RDTA"      },
  { 0xa7, 0x83, "RDTAX"     },
  { 0xa7, 0x85, "VER"       },
  { 0xa7, 0x86, "WALL"      },
  { 0xa7, 0x87, "WDTA"      },
  { 0xa7, 0x88, "WDTAX"     },
  { 0xa7, 0x8a, "WSTS"      },
  { 0xa7, 0x8b, "7CLREG"    },
  { 0xa7, 0x8c, "7DSP0"     },
  { 0xa7, 0x8d, "7DSP1"     },
  { 0xa7, 0x8e, "7DSP2"     },
  { 0xa7, 0x8f, "7DSP3"     },
  { 0xa7, 0x90, "7DSP4"     },
  { 0xa7, 0x91, "7DSP5"     },
  { 0xa7, 0x92, "7DSP6"     },
  { 0xa7, 0x93, "7DSP7"     },
  { 0xa7, 0x94, "7DSP8"     },
  { 0xa7, 0x95, "7DSP9"     },
  { 0xa7, 0x96, "7DSPI"     },
  { 0xa7, 0x97, "7DSZ"      },
  { 0xa7, 0x98, "7DSZI"     },
  { 0xa7, 0x99, "7ENG"      },
  { 0xa7, 0x9a, "7FIX"      },
  { 0xa7, 0x9d, "7ISZ"      },
  { 0xa7, 0x9e, "7ISZI"     },
  { 0xa7, 0x9f, "7P<>S"     },
  { 0xa7, 0xa4, "7SCI"      },

  { 0xa7, 0x01, "CREATE"    },
  { 0xa7, 0x02, "DIR"       },
  { 0xa7, 0x03, "NEWM"      },
  { 0xa7, 0x04, "PURGE"     },
  { 0xa7, 0x05, "READA"     },
  { 0xa7, 0x06, "READK"     },
  { 0xa7, 0x07, "READP"     },
  { 0xa7, 0x08, "READR"     },
  { 0xa7, 0x09, "READRX"    },
  { 0xa7, 0x0a, "READS"     },
  { 0xa7, 0x0b, "READSUB"   },
  { 0xa7, 0x0c, "RENAME"    },
  { 0xa7, 0x0d, "SEC"       },
  { 0xa7, 0x0e, "SEEKR"     },
  { 0xa7, 0x0f, "UNSEC"     },
  { 0xa7, 0x10, "VERIFY"    },
  { 0xa7, 0x11, "WRTA"      },
  { 0xa7, 0x12, "WRTK"      },
  { 0xa7, 0x13, "WRTP"      },
  { 0xa7, 0x14, "WRTPV"     },
  { 0xa7, 0x15, "WRTR"      },
  { 0xa7, 0x16, "WRTRX"     },
  { 0xa7, 0x17, "WRTS"      },
  { 0xa7, 0x18, "ZERO"      },

  { 0xff, 0xff, ""          }
  };

#else

extern REV2 reverse2[];

#endif

#endif

