/*#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>*/
#include "../tty/tty.h"
//#include "../tty/strlen.h"

#if defined(__linux__)
#error "Error:: this compiler is not cross-compile"
#endif

#if !defined(__i386__)
#error "Error:: i686 elf only"
#endif

int kernel_main(){

tty_initianalize();
for(int k = 0; k < 580960000; k++){}

for(int i = 0; i < 40; i++){
    tty_putchar('[');
    tty_putchar(i + 0);
    tty_putchar(']');
    printkern(" INFO::Text console initialized\n");
    for(int k = 0; k < 80960000; k++){}
}
return 1;
}
