#include "string.h"
#include "types.h"

void memset(void * dest, const int val, const uint32_t size)
{
    __asm__ __volatile__(
    "pushl %%eax               \n\t"
    "pushl %%ebx               \n\t"
    "pushl %%ecx               \n\t"

    "movl %1, %%ecx            \n\t"
    "movl %0, %%eax            \n\t"
    "movl %2, %%ebx            \n\t"
    "memset.loop:              \n\t"
    "    movb %%bl, (%%eax)    \n\t"
    "    inc  %%eax            \n\t"
    "loop memset.loop          \n\t"

    "popl %%ecx                \n\t"
    "popl %%ebx                \n\t"
    "popl %%eax                \n\t"
    : : "r" (dest), "r" (size), "r" (val) : "memory");
}

void memcpy(void * dest, const void * src, uint32_t size);
int memcmp(const void * s1, const void * s2, uint32_t n);

void sputc(const char c, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    if (*offset + 1 < buffer_len)
    {
        buffer[*offset] = c;
        *offset += 1;
        buffer[*offset] = 0;
    }
}

/*!
 * @brief Print unsigned number on screen
 * @param num Unsigned number
 * @param base16 Is base16 mode active
 * @param buffer String buffer
 * @param offset Current string offset
 * @param buffer_len Buffer max length
 * @return NONE
 */
void sprint_num(uint64_t num, const bool base16, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    uint32_t p = 0;
    int i = 0;
    int base = base16 ? 16 : 10;

    if (num == 0)
    {
        sputc('0', buffer, offset, buffer_len);
        return;
    }

    while (num != 0)
    {
        p = num % base;
        __asm__ volatile("push %0" : : "r"(p) : "memory");
        num /= base;
        i++;
    }

    for (; i > 0; i--)
    {
        __asm__ volatile("pop %0" : "=r"(p) : "0"(p) : "memory");
        char out = (char)('0' + p);
        if (out > '9') {
            out += 'A' - '9' - 1; // skip other ASCII map directly to 'A' - 'Z' region
        }
        sputc(out, buffer, offset, buffer_len);
    }
}

/*!
 * @brief Print signed number on screen
 * @param num Signed number
 * @param buffer String buffer
 * @param offset Current string offset
 * @return NONE
 */
void sprint_signed(int num, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    uint32_t unsigned_num = *(uint32_t*)&num;
    if ((unsigned_num & 0x80000000) != 0) {
        sputc('-', buffer, offset, buffer_len);
        unsigned_num = ~unsigned_num;
        unsigned_num++;
    }

    sprint_num(unsigned_num, false, buffer, offset, buffer_len);
}

void sprint_64bit_signed(int64_t num, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    uint64_t unsigned_num = *(uint64_t*)&num;
    if ((unsigned_num & 0x8000000000000000) != 0) {
        sputc('-', buffer, offset, buffer_len);
        unsigned_num = ~unsigned_num;
        unsigned_num++;
    }

    sprint_num(unsigned_num, false, buffer, offset, buffer_len);
}

/*!
 * @brief Print float-point
 * @param value Number
 * @param precision Precision (decimal count)
 * @param buffer String buffer
 * @param offset Current string offset
 * @return NONE
 */
void sprint_double(double value, const int precision, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    uint64_t int_part = 0;
    double frac_part;
    uint64_t scale = 0;
    uint64_t frac_scaled = 0;
    uint64_t div = 0;

    // Deal with sign first.
    if (value < 0.0)
    {
        sputc('-', buffer, offset, buffer_len); value = -value;
    }

    // Separate the integer and fractional parts.
    int_part = (uint64_t) value;
    frac_part = value - (double) int_part;

    // Print the integer part.
    sprint_num(int_part, false, buffer, offset, buffer_len);

    // Print fractional part, if requested.
    if (precision > 0)
    {
        sputc('.', buffer, offset, buffer_len);

        // Scale fractional part to an integer with rounding.
        scale = 1ULL;
        for (int i = 0; i < precision; ++i) scale *= 10ULL;

        // Add 0.5 for correct rounding.
        frac_scaled = (uint64_t)(frac_part * (double)scale + 0.5);

        // Handle cases where rounding spills into the next integer.
        if (frac_scaled >= scale) {
            ++int_part;
            frac_scaled -= scale;
        }

        // Print leading zeros in the fractional part.
        div = scale / 10ULL;
        while (div) {
            sputc( (char)('0' + (frac_scaled / div) % 10), buffer, offset, buffer_len);
            div /= 10ULL;
        }
    }
}



/*!
 * @brief Translate escape code into meaningful actions
 * @param code Escape code
 * @return Action determined by provided code
 */
escape_actions_t escape(char code);

/*!
 * @brief Print a null-terminated const char * string
 * @param str String to print
 * @param buffer String buffer
 * @param offset Current string offset
 * @return NOTHING
 */
void sputs(const char *str, char * buffer, uint32_t * offset, const uint32_t buffer_len)
{
    while (*str) {
        sputc(*str, buffer, offset, buffer_len);
        str++;
    }
}

uint32_t sprintf(char *buffer, const uint32_t buffer_length, const char * fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);

    uint32_t i = 0;
    bool this_is_escape = false;
    int precision = 2;
    uint32_t offset = 0;
    while (fmt[i] != '\0')
    {
        if (this_is_escape)
        {
            const escape_actions_t action = escape(fmt[i]);
            switch (action)
            {
                case PRINT_NUMBER_IN_BASE10: {
                    const int num = __builtin_va_arg(ap, int);
                    sprint_signed(num, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_UNSIGNED_NUMBER_IN_BASE10:
                case PRINT_NUMBER_IN_BASE16:
                {
                    const uint32_t num = __builtin_va_arg(ap, uint32_t);
                    sprint_num(num, action == PRINT_NUMBER_IN_BASE16, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_64BIT_NUMBER_IN_BASE10: {
                    const int64_t num = __builtin_va_arg(ap, int64_t);

                    sprint_64bit_signed(num, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_64BIT_UNSIGNED_NUMBER_IN_BASE10:
                case PRINT_64BIT_NUMBER_IN_BASE16: {
                    const uint64_t num = __builtin_va_arg(ap, uint64_t);
                    sprint_num(num, action == PRINT_64BIT_NUMBER_IN_BASE16, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_STRING: {
                    const char * str = __builtin_va_arg(ap, const char *);
                    sputs(str, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_CHARACTER: {
                    const int c = __builtin_va_arg(ap, int); // 'char' is promoted to 'int' when passed through '...'
                    sputc((char)c, buffer, &offset, buffer_length);
                    break;
                }
                case PRINT_FLOAT: // 'float' is promoted to 'double' when passed through '...'
                case PRINT_DOUBLE: {
                    const double d = __builtin_va_arg(ap, double);
                    sprint_double(d, precision, buffer, &offset, buffer_length);
                    break;
                }
                case FLOAT_PRECISION_CHANGE: {
                    precision = __builtin_va_arg(ap, int);
                    break;
                }
                case CURSOR_HIDE:
                case CURSOR_SHOW:
                case SET_FONT_COLOR_BLACK:
                case SET_FONT_COLOR_BLUE:
                case SET_FONT_COLOR_GREEN:
                case SET_FONT_COLOR_CYAN:
                case SET_FONT_COLOR_RED:
                case SET_FONT_COLOR_MAGENTA:
                case SET_FONT_COLOR_YELLOW:
                case SET_FONT_COLOR_WHITE:
                case SET_BACK_COLOR_BLACK:
                case SET_BACK_COLOR_BLUE:
                case SET_BACK_COLOR_GREEN:
                case SET_BACK_COLOR_CYAN:
                case SET_BACK_COLOR_RED:
                case SET_BACK_COLOR_MAGENTA:
                case SET_BACK_COLOR_YELLOW:
                case SET_BACK_COLOR_WHITE:
                case SET_TO_DEFAULT_COLOR:
                    break;
                case PRINT_NEXT_CHARACTER:
                default: sputc(fmt[i], buffer, &offset, buffer_length); break;
            }

            this_is_escape = false;
        }
        else
        {
            if (fmt[i] == '%') {
                this_is_escape = true;
            } else {
                sputc(fmt[i], buffer, &offset, buffer_length);
            }
        }

        i++;
    }

    __builtin_va_end(ap);
    return offset;
}
