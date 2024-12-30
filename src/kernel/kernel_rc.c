#include "drivers/vga.h"
#include "drivers/strings.h"
#include "drivers/time.h"

int kernel_rc_entry()
{
        struct Color_struct color;
        __init_color_struct(&color);
        vga_print_str("Hello, world from kernel_rc.c", &color, VGA_MEMORY_COLOR_TEXT);
        vga_print_nl();
        __init_default_theme();
        load_default_theme(VGA256_White_Blue);
        vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
        //busy_wait(2);
        return 0;
}
