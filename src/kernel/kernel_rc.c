#include "drivers/vga.h"
#include "drivers/strings.h"
#include "drivers/time.h"

int kernel_rc_entry()
{

	/* Test section for theme feature*/
        struct Color_struct color;
        __init_vga__color_struct(&color);
        vga_print_str("Hello, world from kernel_rc.c", &color, VGA_MEMORY_COLOR_TEXT);
        vga_print_nl();
        __init_vga__default_theme();

        vga_load_default_theme(VGA256_White_Blue, &color);
        vga_print_str("test", &color, VGA_MEMORY_COLOR_TEXT);
	vga_print_nl();

        busy_wait(1);
        vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);

	busy_wait(1);
	vga_load_default_theme(VGA256_Blue_White, &color);
	vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
        vga_print_str("this is test2", &color, VGA_MEMORY_COLOR_TEXT);
	vga_print_nl();
	/* Here test3 overwrite MESSAGE_COLOR and should not */
	busy_wait(1);
	vga_load_default_theme(VGA256_Black_White, &color);
	vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
	vga_print_str("this is test3", &color, VGA_MEMORY_COLOR_TEXT);
	vga_print_nl();

	busy_wait(1);
	vga_load_default_theme(VGA256_White_Black, &color);
        vga_write_active_theme(VGA_MEMORY_COLOR_TEXT);
	vga_print_str("this is test3", &color, VGA_MEMORY_COLOR_TEXT);
	vga_print_nl();

	return 0;
}
