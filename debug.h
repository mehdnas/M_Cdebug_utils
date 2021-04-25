
#define MAX_PROCESS_NAME_SIZE 128

/**
   Constants used to indicate the variable types.
   the U stands for unsigned and N stands for numeric. LDOUBLE is the 128 bits float.
*/
typedef enum TYPES_ENUM {
   CHAR, NCHAR, UNCHAR, 
   SHORT, USHORT,
   INT, UINT,
   LONG, ULONG,
   FLOAT, DOUBLE, LDOUBLE
} type_t;

#if !defined(NDEBUG) && defined(MDEBUG)
   
   /**
      A macro that works just like printf but with the addition 
      that it also indicates the file, function and line where 
      it was called.

      The output is like:
      'filename' -> 'function' -> line 'lineNumber': 'the string formated'

      @param format The string with the format just like printf
      @param ... The parameters with whitch the output string gets
         formated.
   */
   #define DBG_LOG(format, ...) \
      output_debug_info(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__)

   /**
      Prints the variables passed as type_t type, T variable, ... and the location
      where the call was produced.

      @param ... The variables preceeded by their types (type, variable, ...).
   */
   #define DBG_LOG_VARS(...) \
      output_vars(__FILE__, __FUNCTION__, __LINE__, #__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__)

#else

   // If NDEBUG is defined then the macros estend to nothing.
   #define DBG_LOG(format, ...) 
   #define DBG_LOG_VARS(...) 

#endif


/**
   The function used in DEBUG_LOG to output the debug info.

   @param file The file name
   @param function The function name
   @param line The line where the call was produced.
   @param format A string with the format of the output.
   @param ... The parameters with whitch the output string
      gets formated.
*/
void output_debug_info(
   const char* file, const char* function, int line, const char* format, ...
);

/**
   The function used in DEBUG_LOG_VARS macro. Prints the variables passed 
   as parameters one line per variable. The location (file, function and 
   line) of the call is printed before.

   @param file The file where the function was called.
   @param function The function that called this function.
   @param line The line where the function was called.
   @param va_args_str the string of the arguments that was passed to the function
      in source code.
   @param ... The variables preceeded by their types: (tipe_t type, T variable, ...)
*/
void output_vars(
   const char* file, const char* function, int line, const char* va_args_string, ...
);


