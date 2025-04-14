
/*  STDLIB printf implementation
 *  Martin Kopka 2025
*/

#include "stdlib/stdio.h"

//---- INTERNAL FUNCTIONS ----------------------------------------------------------------------------------------------------------------------------------------

typedef enum {

    PRINTF_INT_FLAG_SIGNED = (1 << 0),
    PRINTF_INT_FLAG_FORCE_PLUS_SIGN = (1 << 1),
    PRINTF_INT_FLAG_INSERT_SPACE = (1 << 2),
    PRINTF_INT_FLAG_PRINT_FORMAT_SPECIFIER = (1 << 3),
    PRINTF_INT_FLAG_PAD_WITH_ZEROS = (1 << 4),
    PRINTF_INT_FLAG_LEFT_JUSTIFY = (1 << 5),
    PRINTF_INT_FLAG_UPPERCASE = (1 << 6)

} printf_integer_flag_t;

void __printf_integer(uint32_t num, uint8_t base, uint32_t flags, uint8_t width);
void __printf_int_milli(int value, uint8_t dec_places);

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum {

    STATE_DEFAULT,      // waiting for %, else printing characters
    STATE_FLAGS,        // reading flags
    STATE_WIDTH,        // reading width
    STATE_SPECIFIER     // parsing specifier (arg data type)

} printf_state_t;

// writes the string pointed by format to the standard output
int printf(const char *format, ...) {

    int *argp = ((int*)&format) + 1;      // pointer to the next argument
    printf_state_t state = STATE_DEFAULT;
    uint8_t width = 0;
    printf_integer_flag_t int_flags = 0;

    while (*format != '\0') {

        switch (state) {

            case STATE_DEFAULT: {

                switch (*format) {

                    // format specifier start, start parsing it
                    case '%': state = STATE_FLAGS; break;

                    // normal character
                    default: putc(*format); break;
                }

            } break;

            case STATE_FLAGS: {

                switch (*format) {

                    // left-justify within the given field width; Right justification is the default (see width sub-specifier).
                    case '-': int_flags |= PRINTF_INT_FLAG_LEFT_JUSTIFY; break;

                    // forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
                    case '+': int_flags |= PRINTF_INT_FLAG_FORCE_PLUS_SIGN; break;

                    // if no sign is going to be written, a blank space is inserted before the value.
                    case ' ': int_flags |= PRINTF_INT_FLAG_INSERT_SPACE; break;

                    // used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero.
                    // used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
                    case '#': int_flags |= PRINTF_INT_FLAG_PRINT_FORMAT_SPECIFIER; break;

                    // left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).
                    case '0': int_flags |= PRINTF_INT_FLAG_PAD_WITH_ZEROS; break;
                    
                    // no valid flag specified, don't consume the format character
                    default: {
                        
                        format--; 
                        state = STATE_WIDTH;

                    } break;
                }

            } break;

            case STATE_WIDTH: {

                switch (*format) {

                    // width in the specifier is not supported

                    // the width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
                    case '*': width = (uint8_t)*(argp + 1); break;

                    // width not specified, don't consume the format character
                    default: format--; break;
                }

                state = STATE_SPECIFIER;

            } break;

            // parse the specifier (argument data type)
            case STATE_SPECIFIER: {

                switch (*format) {

                    // Signed decimal integer
                    case 'd': 
                    case 'i': __printf_integer((uint32_t)*argp, 10, int_flags | PRINTF_INT_FLAG_SIGNED, width); break;

                    // unsigned decimal integer
                    case 'u': __printf_integer((uint32_t)*argp, 10, int_flags, width); break;

                    // unsigned octal
                    case 'o':  __printf_integer((uint32_t)*argp, 8, int_flags, width); break;

                    // unsigned hexadecimal integer
                    case 'x': __printf_integer((uint32_t)*argp, 16, int_flags, width); break;

                    // unsigned hexadecimal integer (uppercase)
                    case 'X': __printf_integer((uint32_t)*argp, 16, int_flags | PRINTF_INT_FLAG_UPPERCASE, width); break;

                    // TODO: float

                    // character
                    case 'c': putc((char)*argp); break;

                    // string of characters
                    case 's': puts((const char*)*argp); break;

                    // pointer address
                    case 'p': __printf_integer((uint32_t)*argp, 16, int_flags | PRINTF_INT_FLAG_PAD_WITH_ZEROS | PRINTF_INT_FLAG_UPPERCASE, 8); break;

                    // a % followed by another % character will write a single % to the stream.
                    case '%': putc('%'); argp--; break;

                    // CUSTOM: divide a number by 1000 and print it with the remainder after the decimal point
                    case 'm': __printf_int_milli((int)*argp, width);

                    // invalid specifier, nothing printed
                    default: break;
                }

                argp++;
                if (width > 0) argp++;
                state = STATE_DEFAULT;
                width = 0;
                int_flags = 0;

            } break;

            default: break;
        }

        format++;
    }

    return (0);
}

//---- INTERNAL FUNCTIONS ----------------------------------------------------------------------------------------------------------------------------------------

void __printf_integer(uint32_t num, uint8_t base, uint32_t flags, uint8_t width) {

    char output[32];
    bool is_negative = false;
	int i = 0;
	int digit;

    // is in signed mode and number is negative (MSB set)
    if ((flags & PRINTF_INT_FLAG_SIGNED) && (num & 0x80000000)) {

        num = -num;         // converts to unsigned with the loss of the sign
        is_negative = true; // store the sign into this flag
    }

	do {

		digit = num % base;
        num /= base;

		if (digit < 0xA) output[i++] = '0' + digit;
		else if (flags & PRINTF_INT_FLAG_UPPERCASE) output[i++] = 'A' + digit - 0xA;
        else output[i++] = 'a' + digit - 0xA;

	} while ((num != 0) && (i < (32 - 1)));

    if (is_negative) output[i++] = '-';
    else if (flags & PRINTF_INT_FLAG_FORCE_PLUS_SIGN) output[i++] = '+';
    else if (flags & PRINTF_INT_FLAG_INSERT_SPACE) output[i++] = ' ';

    if (flags & PRINTF_INT_FLAG_PRINT_FORMAT_SPECIFIER) {

        if (base == 8) puts("0");
        else if (base == 16) puts("0x");
    }

    uint8_t rear_padding_size = 0;

    if (width > 0) {

        if (flags & PRINTF_INT_FLAG_LEFT_JUSTIFY) rear_padding_size = width - i;
        else {

            char padding = (flags & PRINTF_INT_FLAG_PAD_WITH_ZEROS) ? '0' : ' ';
            while (i != width) output[i++] = padding;
        }
    }

    while (i > 0) putc(output[--i]);        // print the buffer in reverse

    for (i = 0; i < rear_padding_size; i++) putc(' ');
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// divides a number by 1000, converts it to string and sends it via DEBUG_UART with selected number of decimal places
void __printf_int_milli(int value, uint8_t dec_places) {

    char string[16];        // stores the string generated from the input integer
    int buff_index = 0;     // write head to the string array
    int remainder = value;
    int i = 0;

    while (remainder > 0 || i < 3) {    // iterate while there are digits left or the decimal part isn't complete

        int digit = remainder % 10;     // get last digit
        remainder /= 10;

        // convert the current digit to a character and append it to the buffer; skip if the digit is ignored (dec_places setting)
        if (++i > 3 - dec_places) string[buff_index++] = digit + '0';

        // append a decimal point after the decimal part is finished
        if (i == 3) string[buff_index++] = '.';
    }        

    if (value < 1000) string[buff_index++] = '0';        // if the value doesn't have an integer part, append a zero

    // print the buffer (the characters are in reverse order)
    while (buff_index > 0) putc(string[--buff_index]);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
