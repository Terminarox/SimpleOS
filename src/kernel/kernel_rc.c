#include "drivers/vga.h"


int kernel_rc_entry()
{
        struct Color_struct color;
        initialize_color_struct(&color);

        char *video_memory_base = (char *) VGA_MEMORY_COLOR_TEXT;

        char hello_world[] = "Hello, World from kernel_rc_entry.";


        vga_print_str(hello_world, &color, video_memory_base);
        vga_print_nl();

        return 0;
}
