#include "drivers/strings.c"
#include "drivers/vga.h"
#include "kernel_rc.h"
/*      DO NOT change VGAState struct yourself.
 * You can use the api function in order to manipulate them.
 *
 * update_cursor(int row, int col) -> change VGAState.cursor according to row and col given.
 * update_cursor() -> VGAStage.cursor = 2 * (VGAStage.row*80 + VGAStage.col)
 *
 *
 * The only reason for you to use VGAState struct is to get:
 * - actual cursot offset -> VGAState.cursor
 * - actual row -> VGAState.row
 * - actual col -> VGAStage.col
 *
 * Be VERY CAREFUL when you modify this struct by yourself.
 * The following line could be not printed as you want them to be.
 *
 * If you want to do something at boot, use kernel_rc.c file.
 * The kernel will call the funtion kernel_rc_entry() with no arguments.
 *
 * kernel_rc_entry must return one of this value,
 * 0  -> SUCCESS
 * 1 = EXIT  -> WARNING
 * 2 < EXIT_CODE -> ERROR
 */
void main()
{
        update_cursor(14,0);

        struct Color_struct color;
        initialize_color_struct(&color);
        initialize_message_color_struct();

        char *video_memory_base = (char*) VGA_MEMORY_COLOR_TEXT;

        char ok_message[] = "OK";
        char no_message[] = "NO";

        char gdt_loaded_message[] = "32-bits protected mod: Kernel: GDT loaded.";
        char cursor_ok_message[] = "32-bits protected mod: Kernel: Cursor: ";
        char drivers_loaded_message[] = "32-bits protected mod: Kernel: VGA Drivers: ";
        char kernel_rc_msg[] = "32-bits protected mod: Kernel: kernel_rc_entry exit code: ";


        vga_print_str(gdt_loaded_message, &color, video_memory_base);
        vga_print_nl();

        vga_print_str(cursor_ok_message, &color, video_memory_base);
        vga_print_message(ok_message, SUCCESS_MESSAGE, video_memory_base);
        vga_print_nl();

        vga_print_str(drivers_loaded_message, &color, video_memory_base);
        initialize_color_struct(&color);
        vga_print_message(ok_message, SUCCESS_MESSAGE, video_memory_base);
        //set_color_struct(&color, VGA256_Black, VGA256_Green);
        vga_print_nl();
        int kernel_rc_return = kernel_rc_entry(/*&Cursor, &Color, &VGA_Color_Err, &VGA_Color_Warn, &VGA_Color_Success*/);
        char buffer[4];
        int_to_ascii(kernel_rc_return, buffer);

        vga_print_str(kernel_rc_msg, &color, video_memory_base);

        switch (kernel_rc_return) {
                case 0: vga_print_message(buffer, SUCCESS_MESSAGE,video_memory_base);
                        break;
                case 1: vga_print_message(buffer, WARNING_MESSAGE, video_memory_base);
                        break;
                default:vga_print_message(buffer, ERROR_MESSAGE, video_memory_base);
        }

}
