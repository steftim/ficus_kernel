#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
size_t tty_row;
size_t tty_column;
uint8_t tty_color;
volatile uint16_t *tty_buffer;

void tty_initianalize(void);

void tty_setcolor(uint8_t color);

void tty_putentrychar(char c, uint8_t color, size_t x, size_t y);

void tty_putchar(char c);

void tty_write(const char* data, size_t size);

void printkern(const char* data);

void tty_clear(void);

void tty_scroll(void);
