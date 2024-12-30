#define MAX_ROW 25
#define MAX_COL 80
#define VGA_MEMORY_MONOCHROME_TEXT 0xB0000
#define VGA_MEMORY_COLOR_TEXT (char *)0xb8000
#define VGA_MEMORY_GRAPHIC_MOD 0xA0000
/* Define BackGround Color.
 * If you want to get Font Color, divide by 0x10 (16d).
 */
enum VGA256_color {
        VGA256_Black         = 0x00,
        VGA256_Blue          = 0x10,
        VGA256_Green         = 0x20,
        VGA256_Cyan          = 0x30,
        VGA256_Red           = 0x40,
        VGA256_Magenta       = 0x50,
        VGA256_Brown         = 0x60,
        VGA256_White         = 0x70,
        VGA256_Grey          = 0x80,
        VGA256_Light_Blue    = 0x90,
        VGA256_Light_Green   = 0xa0,
        VGA256_Light_Cyan    = 0xb0,
        VGA256_Light_Red     = 0xc0,
        VGA256_Light_Magenta = 0xd0,
        VGA256_Yellow        = 0xe0,
        VGA256_Bright_White  = 0xf0

};

enum Message_Type {
        ERROR_MESSAGE,
        WARNING_MESSAGE,
        SUCCESS_MESSAGE
};

struct Color_struct {
        enum VGA256_color background;
        enum VGA256_color foreground;
        int color;
}VGA256_Color_Err, VGA256_Color_Warn, VGA256_Color_Success, VGA256_Theme_Default, VGA256_Theme_White_Black, VGA256_Theme_Black_White, VGA256_Theme_Blue_White, VGA256_Theme_White_Blue, VGA256_Active_Theme;

/*$1:text color; $2 background color*/
enum VGA256_color_theme {
        VGA256_White_Black,
        VGA256_Black_White,
        VGA256_Blue_White,
        VGA256_White_Blue,
};

struct Cursor {
        int row;
        int col;
        int cursor;
} VGAState;

struct Color_struct message_color_struct[3];
/* change CURSOR according to int row and int col */
void update_cursor(int row, int col)
{
        VGAState.row=row;
        VGAState.col=col;
        VGAState.cursor = 2 * (VGAState.row * 80 + VGAState.col);
}

void vga_print_nl()
{
        update_cursor(VGAState.row+1, 0);
}


/*      DO NOT print a new line !
 * ONLY change CURSOR to the followirror: parameter 'row' has just a forward declarationsng ROW.
 */

void save_cursor_state(struct Cursor *cursor_save_struct)
{
        *cursor_save_struct=VGAState;
}
void restore_cursor_state(struct Cursor *cursor_restore_struct)
{
        VGAState=*cursor_restore_struct;
}
void align_video_memory_to_cursor_offset(char **video_memory)
{
        *video_memory=*(video_memory + VGAState.cursor);
        VGAState.row=0;
        VGAState.col=0;
        VGAState.cursor=0;

}

/* display only one char at the position given by CURSOR.*/
void vga_print_char(char buffer, int color, char *video_memory_base)
{
        *(video_memory_base + VGAState.cursor) = buffer;
        *(video_memory_base + VGAState.cursor + 1) = color;

}

/* Print an entire string using print_video_memory_char.
 * update_cursor according to the lenght of the string.
 */
void vga_print_str(char str[], struct Color_struct *color, char *video_memory_base)
{
        for (int i = 0; str[i]!=0; i++) {
                vga_print_char(str[i], color->color, video_memory_base);
                //calculate position of the folling char.

                /* if the position of the following char is higher than the MAX_COL value
                 * then print newline.
                 */
                if (VGAState.col+1 > MAX_COL) {
                        vga_print_nl(video_memory_base);
                      }
                /* Set the cursor to the position of the following char.*/
                update_cursor(VGAState.row, VGAState.col + 1);
        }
}




void vga_print_err(char str[], char *video_memory_base)
{
        vga_print_str(str, &VGA256_Color_Err, video_memory_base);
}

void vga_print_warn(char str[], char *video_memory_base)
{
        vga_print_str(str, &VGA256_Color_Warn, video_memory_base);
}

void vga_print_success(char str [], char *video_memory_base)
{
        vga_print_str(str, &VGA256_Color_Success, video_memory_base);
}
void vga_print_message(char str[], enum Message_Type msg_type, char *video_memory_base)
{
        switch(msg_type) {
                case ERROR_MESSAGE :
                        vga_print_err(str, video_memory_base);
                        break;
                case WARNING_MESSAGE:
                        vga_print_warn(str, video_memory_base);
                        break;
                case SUCCESS_MESSAGE :
                        vga_print_success(str, video_memory_base);
                        break;
                default:
                        vga_print_warn("VGA_print_message: MsgType do not match with Message_type enum.", video_memory_base);
                        vga_print_warn(str,video_memory_base);
        }
}

/*calculate the Color of the foregroung from the Backgroung Color Code*/
int extract_color_from_enum(enum VGA256_color *color)
{
        return (*color)/0x10;
}

void __init_color_struct(struct Color_struct *color)
{
        color->background = VGA256_Black;
        color->foreground = VGA256_White;
        int extracted_foreground = extract_color_from_enum(&(color->foreground));
        color->color = color->background + extracted_foreground;
}

/* Clear only the line scpecified*/
void vga_clear_line(int row, char *video_memory_base)
{
        struct Color_struct null;
        __init_color_struct(&null);
        update_cursor(row, 0);
        for (int i = 0; i < MAX_COL; i++) {
                vga_print_str(" ", &null, video_memory_base);
        }
}

/* Clear screen From row specified to the last row*/
void vga_clear_screen(int row, char *video_memory_base, int save_cursor)
{
        int saved_row = VGAState.row;
        int saved_col = VGAState.col;

        for (int i = row; i < MAX_ROW; i++){
                vga_clear_line(i, video_memory_base);
        }

        switch (save_cursor) {
                case 0: update_cursor(row, 0);
                        break;
                default: update_cursor(saved_row, saved_col);
        }
}

/* Change Color_struct member according to argument given by caller. */
void set_color_struct(struct Color_struct *color, enum VGA256_color foreground, enum VGA256_color background)
{
        color->background = background;
        color->foreground = foreground;
        int extracted_foreground = extract_color_from_enum(&(color->foreground));
        color->color = color->background + extracted_foreground;

}

/* Initialize Color_struct with default value background: Black; and foreground: Bright_white.
 * Initialization color are the same as used by default (=> 0x0f).
 */
void cpy_color_struct(struct Color_struct *destination, struct Color_struct *source)
{
        set_color_struct(destination, source->foreground, source->background);
}

void __init_message_color_struct()
{
        set_color_struct(&VGA256_Color_Err, VGA256_Red, VGA256_Black);
        set_color_struct(&VGA256_Color_Warn, VGA256_Yellow, VGA256_Black);
        set_color_struct(&VGA256_Color_Success, VGA256_Green, VGA256_Black);
}
int __init_default_theme(){
        set_color_struct(&VGA256_Theme_Black_White, VGA256_Black, VGA256_White);
        set_color_struct(&VGA256_Theme_White_Black, VGA256_White, VGA256_Black);
        set_color_struct(&VGA256_Theme_Blue_White, VGA256_Blue, VGA256_White);
        set_color_struct(&VGA256_Theme_White_Blue, VGA256_White, VGA256_Blue);
        return 0;
}
/* change color theme and change message_color struct BackGround according to the theme */
int load_default_theme(enum VGA256_color_theme theme)
{
        switch(theme) {
                case VGA256_White_Black: cpy_color_struct(&VGA256_Active_Theme, &VGA256_Theme_White_Black);
                                        break;
                case VGA256_Black_White: cpy_color_struct(&VGA256_Active_Theme, &VGA256_Theme_Black_White);
                                        break;
                case VGA256_Blue_White: cpy_color_struct(&VGA256_Active_Theme, &VGA256_Theme_Blue_White);
                                        break;
                case VGA256_White_Blue: cpy_color_struct(&VGA256_Active_Theme, &VGA256_Theme_White_Blue);
                                        break;
        }
        set_color_struct(&VGA256_Color_Err, VGA256_Red, VGA256_Active_Theme.background);
        set_color_struct(&VGA256_Color_Warn, VGA256_Yellow, VGA256_Active_Theme.background);
        set_color_struct(&VGA256_Color_Success, VGA256_Green, VGA256_Active_Theme.background);
        return 0;
}

int vga_write_active_theme(char *video_memory_base){
        struct Color_struct color;
        __init_color_struct(&color);
        set_color_struct(&color, VGA256_Blue, VGA256_Green);
        //vga_print_str("this is a test of active them color struct", &VGA256_Active_Theme, VGA_MEMORY_COLOR_TEXT);
        for (int i = 0; i < 2*(25*80); i=i+2) {
                if (*(video_memory_base+i+1)!=VGA256_Color_Err.color && *(video_memory_base+i+1)!=VGA256_Color_Warn.color && *(video_memory_base+i+1)!=VGA256_Color_Success.color)
                {
                        *(video_memory_base+i+1) = VGA256_Active_Theme.color;
                }
        }
        return 0;
}
