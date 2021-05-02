#include "debug.h"

int main() 
{
   DBG_LOG("Este es un programa para el test de debug");

   char c = 'A';
   char nc = -3;
   unsigned char uc = 255;
   short s = 1;
   int intero = 1 << 20;
   float f = 0.999;
   const char* hello = "Hello world!";

   DBG_LOG_VARS(
      CHAR, c, 
      NCHAR, nc, 
      UNCHAR, uc, 
      SHORT, s,
      INT, intero,
      FLOAT, f,
      STRING, hello
   );
}
