#pragma once

#include <stdio.h>

#define MAX_PROCESS_NAME_SIZE 128
#define OUT_STREAM stderr

/**
   Constants used to indicate variable types.
   the U stands for unsigned and N stands for numeric.
*/
typedef enum TYPES_ENUM {
   CHAR, NCHAR, UNCHAR, 
   SHORT, USHORT,
   INT, UINT,
   LONG, ULONG,
   FLOAT, DOUBLE,
   STRING
} type_t;

#if !defined(NDEBUG) && defined(MDBG) 
   /**
      A macro that works just like printf but with the addition 
      that it also indicates the location (calling process, file, 
      function and line where it was called.

      If MDBG and NDEBUG are both not defined then this macro expands
      to a fprintf(OUT_STREAM, format, ...))

      @param format The string with the format just like printf
      @param ... The parameters with whitch the output string gets
         formated (in the same way as printf).
   */
   #define DBG_LOG(format, ...) \
      output_debug_info(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__)
   
   /**
      Prints the variables passed as (type_t type, T variable, ...) and the location
      where the call was produced. The macro works only if MDBG is defined.

      For this macro to work, MDBG needs to be defined and NDEBUG not defined. Otherwise
      the macro expans to nothing.

      @param ... The variables preceeded by their types (type, variable, ...).
   */
   #define DBG_LOG_VARS(...) \
      output_vars(__FILE__, __FUNCTION__, __LINE__, #__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)

#elif !defined(MDBG)

   // If NDEBUG is not defined but MDBG is also not, this macro works just like a printf.
   #define DBG_LOG(format, ...) fprintf(OUT_STREAM, format __VA_OPT__(,) __VA_ARGS__);

   // This macro needs both NDEBUG to not be and MDBG to be defined.
   #define DBG_LOG_VARS(...) 

#else 
   
   // if NDEBUG is defined and MDBG is not defined, both macros expand to nothing.
   #define DBG_LOG(format, ...)
   #define DBG_LOG(...)

#endif


/**
   The function used in DBG_LOG to output the debug info.

   @param file The name of the file.
   @param function The the name of the calling function.
   @param line The number of the line where the call was produced.
   @param format A string with the format of the output (like printf).
   @param ... The parameters with whitch the output string
      gets formated (like printf).
*/
void output_debug_info(
   const char* file, const char* function, int line, const char* format, ...
);

/**
   The function used in DBG_LOG_VARS macro. Prints the variables passed 
   as parameters one line per variable. The location (calling process, file, 
   function and line) of the call is printed before.

   @param file The file where the function was called.
   @param function The name of the calling function.
   @param line The line where the call was produced.
   @param va_args_str the string of the arguments that was passed to the function
      in source code.
   @param ... The variables preceeded by their types: (tipe_t type, T variable, ...)
*/
void output_vars(
   const char* file, const char* function, int line, const char* va_args_string, ...
);


