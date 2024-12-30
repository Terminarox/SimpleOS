#include "drivers/vga.h"
#include "drivers/strings.h"
#include "drivers/time.h"

int kernel_rc_entry()
{
        struct Color_struct color;
        __init_color_struct(&color);
        set_color_struct(&color, VGA256_Red, VGA256_Black);
        vga_print_str("Hello, world from kernel_rc.c", &color, VGA_MEMORY_COLOR_TEXT);
        vga_print_nl();
        __init_default_theme();
        load_default_theme(VGA256_White_Blue);
        busy_wait(1);
        vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
        return 0;
}
