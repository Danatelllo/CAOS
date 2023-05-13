#include "drivers/vga.h"

enum { QUANTITY_OF_COLUMNS = 16, QUANTITY_OF_ROWS = 16, BASE = 16 };

void show_vga_symbol_table(void) {
    vga_clear_screen();
    char *first_row = "  0 1 2 3 4 5 6 7 8 9 a b c d e f";
    char *column = "0123456789abcdef";
    vga_print_string_noscroll(first_row);
    unsigned int row = COLS;

    for (int current_column = 0; current_column < QUANTITY_OF_COLUMNS;
         ++current_column) {
        vga_set_char(row, column[current_column]);
        for (int current_row = 0; current_row < QUANTITY_OF_ROWS;
             ++current_row) {
            vga_set_char(row + 2 * (current_row + 1),
                         current_column * BASE + current_row);
        }
        row += COLS;
    }
}
