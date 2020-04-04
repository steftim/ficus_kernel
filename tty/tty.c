#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tty.h"
#include "strlen.h"
#include "colors.h"

static const size_t SCREEN_WIDTH = 80;
static const size_t SCREEN_HEIGHT = 25;


static inline uint8_t tty_entry_color(enum terminal_color fg, enum terminal_color bg){
        return fg | bg << 4;
}

static inline uint16_t tty_entry(unsigned char uc, uint8_t color){
        return (uint16_t) uc | (uint16_t) color << 8;
}

size_t tty_row = 0;
size_t tty_column = 0;
uint8_t tty_color;
volatile uint16_t *tty_buffer = (uint16_t*) 0xB8000;

void tty_initianalize(void){
/*    tty_row = 0;
    tty_column = 0;
    tty_color = tty_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
    tty_buffer = (uint16_t*) 0xB8000;*/
    tty_color = tty_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);

    for (size_t y = 0; y < SCREEN_HEIGHT; y++) {
	    for (size_t x = 0; x < SCREEN_WIDTH; x++) {
		    const size_t index = y * SCREEN_WIDTH + x;
		    tty_buffer[index] = tty_entry(' ', tty_color);
	    }
	} 
}

void tty_setcolor(uint8_t color){
	tty_color = color;
}

void tty_putentrychar(char c, uint8_t color, size_t x, size_t y){
	const size_t index = y * SCREEN_WIDTH + x;
	tty_buffer[index] = tty_entry(c, color);
}

void tty_putchar(char c){

	if(tty_row == SCREEN_HEIGHT){	
	        tty_scroll();
    }
    if(c == '\n'){
            tty_column = 0;
            ++tty_row;
        }else {
		    tty_putentrychar(c, tty_color, tty_column, tty_row);
		    if (++tty_column == SCREEN_WIDTH){
			    tty_column = 0;
                tty_row++;
    	    }
	    }	
}

//void tty_putvar(int num){

//}

void tty_write(const char* data, size_t size){
        for(size_t i = 0; i < size; i++){
                tty_putchar(data[i]);
        }
}

void printkern(const char* data){
        tty_write(data, strlen(data));
}


void tty_clear(void){
    for(size_t i = 0; i < SCREEN_WIDTH; i++){
        for(size_t j = 0; j < SCREEN_HEIGHT; j++){
	        tty_color = tty_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
	        tty_putchar(' ');
	    }
    }
//	tty_color = tty_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
	tty_row = 0;
	tty_column = 0;
}

void tty_scroll(void){
	for(size_t i = 1; i <= SCREEN_HEIGHT - 1; i++){
        for(size_t j = 0; j <= SCREEN_WIDTH; j++){
            if(i == SCREEN_HEIGHT){
			    const size_t index = tty_row * SCREEN_WIDTH + j;
			    tty_buffer[index] = ' ';
			}else{
			    const size_t index = i * SCREEN_WIDTH + j;
			    tty_putentrychar(tty_buffer[index], tty_color, j, i - 1);
            }
		}
	}
    tty_row--;
 }
