#include "header.h"

/*
                0
          -------------
          |\a  8|   b/|      .e
        5 | \   |   / |
          |  \  |  /  | 1
          |6  \ | /  7|
          |----- -----|
          |   / | \   |
        4 |  /  |  \  | 2    .f
          | /   |   \ |      ,g
          |/d  9|   c\|
          -------------
                3
    g fedc ba98 7654 3210
        11  1 1      11 1

  ---
 |\|/|o
  - -
 |/|\|o
  --- /

 +-+-+
 |\|/|o
 +-V-+
 |/|\|o
 +---+/

 +-+--
  \|  o
   +  
  / \|o
 +---+/
*/

u_int32_t charset[130] = {   0x00001,     /* 00 */
                             0x031c1,     /* 01 */
                             0x03fff,     /* 02 */
                             0x03fff,     /* 03 */
                             0x03101,     /* 04 */
                             0x03141,     /* 05 */
                             0x02101,     /* 06 */
                             0x03fff,     /* 07 */
                             0x03fff,     /* 08 */
                             0x03fff,     /* 09 */
                             0x03fff,     /* 0A */
                             0x03fff,     /* 0B */
                             0x02182,     /* 0C */
                             0x02a08,     /* 0D */
                             0x03fff,     /* 0E */
                             0x03fff,     /* 0F */
                             0x03fff,     /* 10 */
                             0x03fff,     /* 11 */
                             0x03fff,     /* 12 */
                             0x03fff,     /* 13 */
                             0x03fff,     /* 14 */
                             0x03fff,     /* 15 */
                             0x03fff,     /* 16 */
                             0x03fff,     /* 17 */
                             0x03fff,     /* 18 */
                             0x03fff,     /* 19 */
                             0x03fff,     /* 1A */
                             0x03fff,     /* 1B */
                             0x03fff,     /* 1C */
                             0x028c8,     /* 1D */
                             0x03fff,     /* 1E */
                             0x03fff,     /* 1F */
                             0x00000,     /* 20 */
                             0x00300,     /* 21 ! */
                             0x00120,     /* 22 " */
                             0x003ce,     /* 23 # */
                             0x003ed,     /* 24 $ */
                             0x03ce4,     /* 25 % */
                             0x0350d,     /* 26 & */
                             0x00100,     /* 27 ' */
                             0x01800,     /* 28 ( */
                             0x02400,     /* 29 ) */
                             0x03fc0,     /* 2A * */
                             0x003c0,     /* 2B + */
                             0x18000,     /* 2C , */
                             0x000c0,     /* 2D - */
                             0x08000,     /* 2E . */
                             0x02800,     /* 2F / */
                             0x0283f,     /* 30 0 */
                             0x00006,     /* 31 1 */
                             0x000db,     /* 32 2 */
                             0x000cf,     /* 33 3 */
                             0x000e6,     /* 34 4 */
                             0x0048d,     /* 35 5 */
                             0x000fd,     /* 36 6 */
                             0x00007,     /* 37 7 */
                             0x000ff,     /* 38 8 */
                             0x000ef,     /* 39 9 */
                             0x0c000,     /* 3A : */
                             0x1c000,     /* 3B ; */
                             0x02808,     /* 3C < */
                             0x000c8,     /* 3D = */
                             0x01408,     /* 3E > */
                             0x002a3,     /* 3F ? */
                             0x001bb,     /* 40 @ */
                             0x000f7,     /* 41 A */
                             0x0038f,     /* 42 B */
                             0x00039,     /* 43 C */
                             0x0030f,     /* 44 D */
                             0x000f9,     /* 45 E */
                             0x000f1,     /* 46 F */
                             0x000bd,     /* 47 G */
                             0x000f6,     /* 48 H */
                             0x00309,     /* 49 I */
                             0x0000e,     /* 4A J */
                             0x01870,     /* 4B K */
                             0x00038,     /* 4C L */
                             0x00c36,     /* 4D M */
                             0x01436,     /* 4E N */
                             0x0003f,     /* 4F O */
                             0x000f3,     /* 50 P */
                             0x0103f,     /* 51 Q */
                             0x010f3,     /* 52 R */
                             0x000ed,     /* 53 S */
                             0x00301,     /* 54 T */
                             0x0003e,     /* 55 U */
                             0x02830,     /* 56 V */
                             0x03036,     /* 57 W */
                             0x03c00,     /* 58 X */
                             0x00e00,     /* 59 Y */
                             0x02809,     /* 5A Z */
                             0x00039,     /* 5B [ */
                             0x01400,     /* 5C \ */
                             0x0000f,     /* 5D ] */
                             0x02803,     /* 5E ^ */
                             0x00008,     /* 5F _ */
                             0x00101,     /* 60 t */
                             0x0105c,     /* 61 a */
                             0x000fc,     /* 62 b */
                             0x000d8,     /* 63 c */
                             0x000de,     /* 64 d */
                             0x02058,     /* 65 e */
                             0x03fff,     /* 66 */
                             0x03fff,     /* 67 */
                             0x03fff,     /* 68 */
                             0x03fff,     /* 69 */
                             0x03fff,     /* 6A */
                             0x03fff,     /* 6B */
                             0x03fff,     /* 6C */
                             0x03fff,     /* 6D */
                             0x03fff,     /* 6E */
                             0x03fff,     /* 6F */
                             0x03fff,     /* 70 */
                             0x03fff,     /* 71 */
                             0x03fff,     /* 72 */
                             0x03fff,     /* 73 */
                             0x03fff,     /* 74 */
                             0x03fff,     /* 75 */
                             0x03fff,     /* 76 */
                             0x03fff,     /* 77 */
                             0x03fff,     /* 78 */
                             0x03fff,     /* 79 */
                             0x000f0,     /* 7A */
                             0x03fff,     /* 7B */
                             0x03fff,     /* 7C */
                             0x03fff,     /* 7D */
                             0x02409,     /* 7E */
                             0x000f0,     /* 7F */
                             0x024c0,     /* 80 forward goose */
                             0x018c0,     /* 81 backward goose */
                         };

void DrawLcd(char* msg) {
  int i;
  byte b;
  printf("\n");

/* ***** Line 1 ***** */
  for (i=0; i<strlen(msg); i++) {
    b = msg[i];
    if (b == 0xff) b = 0;
    if (b != ':' && b != ';' && b != '.' && b != ',') {
      if (b > 129) b = 128;
      if (charset[b] & 0x0001) {
        if ((charset[b] & 0x0420) != 0) printf("+"); else printf("-");
        }
      else printf(" ");
      if (charset[b] & 0x0001) printf("-"); else printf(" ");
      if (charset[b] & 0x0001) {
        if ((charset[b] & 0x0100) != 0) printf("+"); else printf("-");
        }
      else printf(" ");
      if (charset[b] & 0x0001) printf("-"); else printf(" ");
      if (charset[b] & 0x0001) {
        if ((charset[b] & 0x0802) != 0) printf("+"); else printf("-");
        }
      else printf(" ");

      printf(" ");
      }
    }
  printf("\n");

/* ***** Line 2 ***** */
  for (i=0; i<strlen(msg); i++) {
    b = msg[i];
    if (b == 0xff) b = 0;
    if (b != ':' && b != ';' && b != '.' && b != ',') {
      if (b > 129) b = 128;
      if (charset[b] & 0x0020) printf("|"); else printf(" ");
      if (charset[b] & 0x0400) printf("\\"); else printf(" ");
      if (charset[b] & 0x0100) printf("|"); else printf(" ");
      if (charset[b] & 0x0800) printf("/"); else printf(" ");
      if (charset[b] & 0x0002) printf("|"); else printf(" ");
      if (msg[i+1] == ':') printf("o");
      else if (msg[i+1] == ';') printf("o");
      else printf(" ");
      }
    }
  printf("\n");

/* ***** Line 3 ***** */
  for (i=0; i<strlen(msg); i++) {
    b = msg[i];
    if (b == 0xff) b = 0;
    if (b != ':' && b != ';' && b != '.' && b != ',') {
      if (b > 129) b = 128;
      if (charset[b] & 0x0030) {
        if ((charset[b] & 0x70) == 0x20) printf(" ");
        else if ((charset[b] & 0x0040) != 0) printf("+"); else printf("|");
        }
      else printf(" ");
      if (charset[b] & 0x0040) printf("-"); else printf(" ");
      if ((charset[b] & 0x3fc0) == 0x01400) printf("\\");
      else if ((charset[b] & 0x3fc0) == 0x2800) printf("/");
      else if ((charset[b] & 0x3fc0) == 0x0300) printf("|");
      else if ((charset[b] & 0x3fc0) == 0x00c0) printf("-");
      else if ((charset[b] & 0x3fc0) == 0x3c00) printf("X");
      else if ((charset[b] & 0x3fc0) == 0x0c00) printf("V");
      else if ((charset[b] & 0x3fc0) == 0x2400) printf(")");
      else if ((charset[b] & 0x3fc0) == 0x1800) printf("(");
      else if ((charset[b] & 0x3fc0) == 0x0100) printf(" ");
      else if ((charset[b] & 0x3fc0) == 0x0e00) printf("V");
      else if ((charset[b] & 0x3fc0) != 0x0000) printf("+");
      else printf(" ");
      if (charset[b] & 0x0080) printf("-"); else printf(" ");
      if (charset[b] & 0x0006) {
        if ((charset[b] & 0x0080) != 0) printf("+"); else printf("|");
        }
      else printf(" ");
      printf(" ");
      }
    }
  printf("\n");

/* ***** Line 4 ***** */
  for (i=0; i<strlen(msg); i++) {
    b = msg[i];
    if (b == 0xff) b = 0;
    if (b != ':' && b != ';' && b != '.' && b != ',') {
      if (b > 129) b = 128;
      if (charset[b] & 0x0010) printf("|"); else printf(" ");
      if (charset[b] & 0x2000) printf("/"); else printf(" ");
      if (charset[b] & 0x0200) printf("|"); else printf(" ");
      if (charset[b] & 0x1000) printf("\\"); else printf(" ");
      if (charset[b] & 0x0004) printf("|"); else printf(" ");
      if (msg[i+1] == ':') printf("o");
      else if (msg[i+1] == ';') printf("o");
      else if (msg[i+1] == '.') printf("o");
      else if (msg[i+1] == ',') printf("o");
      else printf(" ");
      }
    }
  printf("\n");

/* ***** Line 1 ***** */
  for (i=0; i<strlen(msg); i++) {
    b = msg[i];
    if (b == 0xff) b = 0;
    if (b != ':' && b != ';' && b != '.' && b != ',') {
      if (b > 129) b = 128;
      if ((charset[b] & 0x2018) == 0x0008) printf("-");
      else if ((charset[b] & 0x2018) == 0x2008) printf("+");
      else if ((charset[b] & 0x2018) == 0x2018) printf("+");
      else if ((charset[b] & 0x2018) == 0x0018) printf("+");
      else printf(" ");
      if (charset[b] & 0x0008) printf("-"); else printf(" ");
      if ((charset[b] & 0x0208) == 0x0208) printf("+");
      else if ((charset[b] & 0x0208) == 0x0008) printf("-");
      else printf(" ");
      if (charset[b] & 0x0008) printf("-"); else printf(" ");

      if ((charset[b] & 0x100c) == 0x0008) printf("-");
      else if ((charset[b] & 0x100c) == 0x1008) printf("+");
      else if ((charset[b] & 0x100c) == 0x100c) printf("+");
      else if ((charset[b] & 0x100c) == 0x000c) printf("+");
      else printf(" ");

      if (msg[i+1] == ',' || msg[i+1] == ';') printf("/");
      else printf(" ");
      }
    }
  printf("\n");

  printf("        ");
  if (FlagSet(27)) printf("USER  "); else printf("      ");
  if (FlagSet(42)) printf("GRAD  ");
  else if (FlagSet(43)) printf(" RAD  ");
  else printf("      ");
  if (FlagSet(47)) printf("SHIFT  "); else printf("       ");
  if (FlagSet(0)) printf("0 "); else printf("  ");
  if (FlagSet(1)) printf("1 "); else printf("  ");
  if (FlagSet(2)) printf("2 "); else printf("  ");
  if (FlagSet(3)) printf("3 "); else printf("  ");
  if (FlagSet(4)) printf("4 "); else printf("  ");
  if (FlagSet(52)) printf("PRGM  "); else printf("      ");
  if (FlagSet(48)) printf("ALPHA  "); else printf("       ");

  printf("\n");

  }

