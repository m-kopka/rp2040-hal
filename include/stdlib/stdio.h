#ifndef _STDLIB_STDIO_H_
#define _STDLIB_STDIO_H_

/*  STDLIB printf implementation
 *  Martin Kopka 2025
*/

#include <stdint.h>
#include <stdbool.h>

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// used by printf and must be defined by the application
void putc(char c);

// used by printf and must be defined by the application
void puts(const char *str);

// writes the string pointed by format to the standard output
int printf(const char *format, ...);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _STDLIB_STDIO_H_ */