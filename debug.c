#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "debug.h"
#include "clrout.h"

#define PROC_NAME_PATH_SIZE 32
#define OUT_STREAM stderr

void get_process_name(const pid_t pid, char* name)
{
   char proc_name_path[PROC_NAME_PATH_SIZE];
   sprintf(proc_name_path, "/proc/%d/cmdline", pid);
   
   FILE* name_file = fopen(proc_name_path, "r");
   if (name_file) {
      size_t size = fread(name, sizeof(char), MAX_PROCESS_NAME_SIZE, name_file);
      if (size > 0 && name[size - 1] == '\n') {
         name[size - 1] = '\0';
      }
   }
}

void print_location(const char* file, const char* function, int line)
{
   pid_t pid = getpid();

   char process_name[MAX_PROCESS_NAME_SIZE + 1];
   get_process_name(pid, process_name);

   set_out_color(OUT_STREAM, CLR_RED);

   fprintf(OUT_STREAM, "\n%s|%d -> %s -> %s -> line %d: \n", 
      process_name, pid, file, function, line
   );

   set_out_color(OUT_STREAM, CLR_RESET);
}

void output_debug_info(
  const char* file, const char* function, int line, const char* format, ...
){
   va_list va_args;
   va_start(va_args, format);

   print_location(file, function, line);

   set_out_color(OUT_STREAM, CLR_CYAN);

   vfprintf(OUT_STREAM, format, va_args);
   fputs("\n\n", OUT_STREAM);
   
   set_out_color(OUT_STREAM, CLR_RESET);

   va_end(va_args);
}

void output_vars(
   const char* file, const char* function, int line, const char* va_args_str, ...
){
   va_list va_args;
   va_start(va_args, va_args_str);
   
   print_location(file, function, line);
   
   set_out_color(OUT_STREAM, CLR_CYAN);

   char mutable_va_args_str[strlen(va_args_str) + 1];
   strcpy(mutable_va_args_str, va_args_str);

   bool end_reached = strtok(mutable_va_args_str, ",") == NULL;

   while (!end_reached) {

      const char* variable_name = strtok(NULL, ",");
      type_t variable_type = va_arg(va_args, type_t);

      switch (variable_type) {
         case CHAR: {
            char variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "char %s = %c\n", variable_name, variable_value);
            break;
         }
         case NCHAR: {
            char variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "char %s = %hhi\n", variable_name, variable_value);
            break;
         }
         case UNCHAR: {
            unsigned char variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "unsigned char %s = %hhu\n", variable_name, variable_value);
            break;
         }
         case SHORT: {
            short variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "short %s = %hd\n", variable_name, variable_value);
            break;
         }
         case USHORT: {
            unsigned short variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "unsigned short %s = %hu\n", variable_name, variable_value);
            break;
         }
         case INT: {
            int variable_value = va_arg(va_args, int);
            fprintf(OUT_STREAM, "int %s = %d\n", variable_name, variable_value);
            break;
         }
         case UINT: {
            unsigned int variable_value = va_arg(va_args, unsigned int);
            fprintf(OUT_STREAM, "unsigned int %s = %u\n", variable_name, variable_value);
            break;
         }
         case LONG: {
            long variable_value = va_arg(va_args, long);
            fprintf(OUT_STREAM, "long %s = %ld\n", variable_name, variable_value);
            break;
         }
         case ULONG: {
            unsigned long variable_value = va_arg(va_args, unsigned long);
            fprintf(OUT_STREAM, "unsigned long %s = %lu\n", variable_name, variable_value);
            break;
         }
         default: {
            // Invalid or unsupported type
            DBG_LOG("Invalid or unsupported variable type");
            assert(false);
            break;
         }
      }
      end_reached = strtok(NULL, ",") == NULL;
   }
   
   putchar('\n');

   set_out_color(OUT_STREAM, CLR_RESET);

   va_end(va_args);
}

