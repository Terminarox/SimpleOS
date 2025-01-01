#include "drivers/vga.h"
#include "drivers/strings.h"
#include "drivers/time.h"

int kernel_rc_entry()
{
        struct Color_struct color;
        __init_vga__color_struct(&color);
        vga_print_str("Hello, world from kernel_rc.c", &color, VGA_MEMORY_COLOR_TEXT);
        vga_print_nl();
        __init_vga__default_theme();


        vga_load_default_theme(VGA256_White_Blue, &color);
        vga_print_str("test", &color, VGA_MEMORY_COLOR_TEXT);

        busy_wait(1);
        vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
        vga_print_nl();
        //vga_print_str("\n\r", &color, VGA_MEMORY_COLOR_TEXT);
        return 0;
}
