#pragma once

#define MAX_PROCESS_NAME_SIZE 128

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

#if !defined(NDEBUG) 
   /**
      A macro that works just like printf but with the addition 
      that it also indicates the location (calling process, file, 
      function and line where it was called.

      @param format The string with the format just like printf
      @param ... The parameters with whitch the output string gets
         formated (in the same way as printf).
   */
   #define DBG_LOG(format, ...) \
      output_debug_info(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__)
   
   /**
      Prints the variables passed as (type_t type, T variable, ...) and the location
      where the call was produced. The macro works only if MDBG is defined.

      @param ... The variables preceeded by their types (type, variable, ...).
   */
   #ifdef MDBG
      #define DBG_LOG_VARS(...) \
         output_vars(__FILE__, __FUNCTION__, __LINE__, #__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)
   #else
      // The macro expanded to nothing if MDBG is not defined.
      #define DBG_LOG_VARS(...) 
   #endif

#else

   // If NDEBUG is defined then the macros expand to nothing.
   #define DBG_LOG(format, ...) 
   #define DBG_LOG_VARS(...) 

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


