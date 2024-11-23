int CURSOR;
int ROW;
int COL;


char* update_video_memory(/* arguments */) {
        return (char *) (0xb8000+CURSOR);
}

void update_cursor (int row, int col)
{
        CURSOR = 2 * (ROW * 80 + COL);
}


void update_cursor_end_str ()
{
        CURSOR = 2 * ((ROW+1)*80+0);
}

//write an only char on video memory
void print_video_memory_char (char buffer, int color, char *video_memory)
{

        *(video_memory) = buffer;
        *(video_memory+1) = color;

}


// write string video memory.
void print_video_memory_str(char str[], int color, char *video_memory)
{
        for (int i=0; str[i]!=0; i++) {
                print_video_memory_char(str[i], 0x0f, video_memory);
                video_memory=video_memory+2;
                update_cursor(ROW, i+1);

        }
        //update_cursor_end_str();

}
//2 * (ligne * 80 + colonne);
void main()
{
        ROW = 1;
        COL = 0;
        CURSOR = 2 * (ROW * 80 + COL);

        char *video_memory = (char*) 0xb8000;
        video_memory=video_memory+CURSOR;

        char str[] = "32-bits protected mod: Kernel: GDT loaded.";
        char str2[] = "32-bits protected mod: Kernel: Testing cursor.";

        print_video_memory_str(str, 0x0f, video_memory);
        video_memory = update_video_memory();
        print_video_memory_str(str2, 0x0f, video_memory);

}
