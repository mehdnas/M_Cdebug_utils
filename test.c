#include "debug.h"

int main() 
{
   DBG_LOG("Este es un programa para el test de debug");

   char c = 'A';
   char nc = -3;
   unsigned char uc = 255;
   short s = 1;
   int intero = 1 << 20;

   DBG_LOG_VARS(
      CHAR, c, 
      NCHAR, nc, 
      UNCHAR, uc, 
      SHORT, s,
      INT, intero
   );
}
