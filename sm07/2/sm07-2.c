#include "drivers/port.h"
#include "drivers/vga.h"

static unsigned get_offset(unsigned col, unsigned row) {
    return row * COLS + col;
}

static unsigned get_row_from_offset(unsigned offset) {
    return offset / COLS;
}

void vga_set_cursor(unsigned offset) {
    unsigned short low = (unsigned short)0xFF & offset;
    unsigned short big = (unsigned short)offset >> 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, big);
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, low);
}

void vga_get_char(unsigned offset, char *c) {
    *c = video_memory[2 * offset];
}

void scroll() {
    unsigned int current_offset = 0;
    char current_char;
    while (current_offset + COLS < COLS * ROWS) {
        vga_get_char(current_offset + COLS, &current_char);
        vga_set_char(current_offset, current_char);
        ++current_offset;
    }
    current_char = ' ';
    while (current_offset < COLS * ROWS) {
        vga_set_char(current_offset, current_char);
        ++current_offset;
    }
}

void vga_putc(char c) {
    unsigned int offset = vga_get_cursor();
    if (c == '\n') {
        if (offset + COLS >= COLS * ROWS) {
            scroll();
            offset = (COLS * ROWS) - COLS;
            vga_set_cursor(offset);
        } else {
            offset = get_offset(0, get_row_from_offset(offset) + 1);
            vga_set_cursor(offset);
        }
    } else {
        if (offset == COLS * ROWS) {
            scroll();
            offset = (COLS * ROWS) - COLS;
            vga_set_char(offset, c);
            vga_set_cursor(offset + 1);
        } else {
            vga_set_char(offset, c);
            vga_set_cursor(offset + 1);
        }
    }
}
