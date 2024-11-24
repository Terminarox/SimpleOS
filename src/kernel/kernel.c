#include "drivers/strings.c"
#include "drivers/vga.c"

/*      DO NOT manipulate VGAState struct yourself.
 * You can use the following function in order to manipulate them.
 * update_cursor(int row, int col) -> change VGAState.cursor according to row and col given.
 * get_cursor()-> return VGAState.cursor,
 * get_cursor_row() -> return VGAState.row,
 * get_cursor_col() -> return VGAState.col
 *
 */
void main()
{
        update_cursor(1,0);

        char *video_memory_base = (char*) 0xb8000;
        char str[] = "32-bits protected mod: Kernel: GDT loaded.\0";
        char str2[] = "32-bits protected mod: Kernel: If you can see this line, Cursor Error detected.\0";
        char *space = " ";
        char cursor_ok_message[] = "32-bits protected mod: Kernel: Cursor OK.";

        print_video_memory_str(str, 0x0f, video_memory_base);
        print_video_memory_nl(video_memory_base);

        int saved_row = get_cursor_row();
        int saved_col = get_cursor_col();

        int str2_size = size_str(str2);

        print_video_memory_str(str2, 0xf0, video_memory_base);

        update_cursor(saved_row, saved_col);

        for (int i = 0; i<=str2_size; i++) {
                print_video_memory_str(space, 0x0f, video_memory_base);
        }
        update_cursor(saved_row, saved_col);
        print_video_memory_str(cursor_ok_message, 0x0f, video_memory_base);

}
