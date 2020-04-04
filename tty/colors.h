//screen colors
enum terminal_color {
	TTY_COLOR_BLACK	    	    = 0,
	TTY_COLOR_BLUE		        = 1,
	TTY_COLOR_GREEN		        = 2,
	TTY_COLOR_CYAN	    	    = 3,
	TTY_COLOR_RED	    	    = 4,
	TTY_COLOR_MAGENTA	        = 5,
	TTY_COLOR_BROWN		        = 6,
	TTY_COLOR_LIGHT_GREY	    = 7,
	TTY_COLOR_DARK_GREY	        = 8,
	TTY_COLOR_LIGHT_BLUE	    = 9,
	TTY_COLOR_LIGHT_GREEN	    = 10,
	TTY_COLOR_LIGHT_CYAN	    = 11,
	TTY_COLOR_LIGHT_RED	        = 12,
	TTY_COLOR_LIGHT_MAGENTA	    = 13,
	TTY_COLOR_LIGHT_BROWN	    = 14,
	TTY_COLOR_WHITE		        = 15,
};

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
volatile uint16_t *tty_buffer;

static inline uint8_t tty_entry_color(enum terminal_color fg, enum terminal_color bg);

static inline uint16_t tty_entry(unsigned char uc, uint8_t color);

