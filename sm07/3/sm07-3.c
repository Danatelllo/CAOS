#include "drivers/uart.h"
#include <stdarg.h>

enum { DECIMAL_BASE = 10, HEX_BASE = 16 };

void kprintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    unsigned arg = 0;
    while (*fmt != '\0') {
        if (*fmt == '%' && *(1 + fmt) != '\0' &&
            (*(1 + fmt) == 'u' || *(1 + fmt) == 'x')) {
            if (*(1 + fmt) == 'x') {
                arg = va_arg(ap, unsigned);
                if (arg == 0) {
                    uartputc('0');
                } else {
                    unsigned int step_of_hex = 1;
                    unsigned int tmp_arg = arg;
                    while (tmp_arg != 0) {
                        if (tmp_arg / HEX_BASE > 0) {
                            step_of_hex *= HEX_BASE;
                        }
                        tmp_arg /= HEX_BASE;
                    }
                    while (step_of_hex != 0) {
                        unsigned int out =
                            (((arg - arg % step_of_hex)) / step_of_hex);
                        if (out >= 10) {
                            uartputc('W' + out);
                        } else {
                            uartputc(out + '0');
                        }
                        arg = arg % step_of_hex;
                        step_of_hex /= HEX_BASE;
                    }
                }
                ++fmt;
            } else if (*(1 + fmt) == 'u') {
                arg = va_arg(ap, unsigned);
                if (arg == 0) {
                    uartputc('0');
                } else {
                    unsigned int step_of_ten = 1;
                    unsigned int tmp_arg = arg;
                    while (tmp_arg != 0) {
                        step_of_ten *= DECIMAL_BASE;
                        tmp_arg /= DECIMAL_BASE;
                    }
                    step_of_ten /= DECIMAL_BASE;
                    while (step_of_ten != 0) {
                        char out =
                            (((arg - arg % step_of_ten)) / step_of_ten) + '0';
                        arg = arg % step_of_ten;
                        uartputc(out);
                        step_of_ten /= DECIMAL_BASE;
                    }
                }
                ++fmt;
            }
        } else {
            uartputc(*fmt);
        }
        ++fmt;
    }
}
