struct Cursor {
        int row;
        int col;
        int cursor;
} VGAState;

// return CURSOR
int get_cursor()
{
        return VGAState.cursor;
}

int get_cursor_row()
{
        return VGAState.row;
}

int get_cursor_col()
{
        return VGAState.col;
}
// change CURSOR according to int row and int col
void update_cursor (int row, int col)
{
        VGAState.row=row;
        VGAState.col=col;
        VGAState.cursor = 2 * (VGAState.row * 80 + VGAState.col);
}

/*      DO NOT print a new line !
 * ONLY change CURSOR to the following ROW.
 */
void print_video_memory_nl()
{
        update_cursor(VGAState.row+1, 0);
}

/*void update_video_memory (char **video_memory)
{
        *video_memory=*(video_memory + VGAState.cursor);
}
*/
// display only one char at the position given by CURSOR.
void print_video_memory_char (char buffer, int color, char *video_memory_base)
{
        //char *cursor = (char *) get_cursor();
        *(video_memory_base + VGAState.cursor) = buffer;
        *(video_memory_base + VGAState.cursor + 1) = color;

}

/* Print an entire string using print_video_memory_char.
 * update_cursor according to the lenght of the string.
 */
void print_video_memory_str(char str[], int color, char *video_memory_base)
{
        for (int i = 0; str[i]!=0; i++) {
                print_video_memory_char(str[i], color, video_memory_base);
                update_cursor(VGAState.row, VGAState.col + 1);
        }
}
