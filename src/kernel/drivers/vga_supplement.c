#include "vga.h"
void vga_print_str_f(char str[], char *arg[], struct Color_struct *color, char *video_memory_base)
{
        for (int i = 0; arg[i]!=0; i++) {
                vga_print_str(arg[i], color, video_memory_base);
                vga_print_nl();
        }

}
