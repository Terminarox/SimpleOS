#ifndef VGA_H_   /* Include guard */
#define VGA_H_
#define MAX_ROW 25
#define MAX_COL 80
#define VGA_MEMORY_MONOCHROME_TEXT 0xB0000
#define VGA_MEMORY_COLOR_TEXT (char *)0xb8000
#define VGA_MEMORY_GRAPHIC_MOD 0xA0000


/* Define BackGround Color.
 * If you want to get Font Color, divide by 0x0f (16d).
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
};

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
};
void vga_update_cursor (int row, int col);
void vga_align_video_memory_to_cursor_offset(char **video_memory_ptr);
void vga_save_cursor_state (struct Cursor *cursor_save_struct);
void vga_restore_cursor_state (struct Cursor *cursor_restore_struct);

int vga_extract_color_from_enum (enum VGA256_color *color);
void vga_set_color_struct (struct Color_struct *color, enum VGA256_color background, enum VGA256_color foreground);
void vga_cpy_color_struct(struct Color_struct *destination, struct Color_struct *source);
void __init_vga__color_struct(struct Color_struct *color);
void __init_vga__message_color_struct();

void __init_vga__default_theme();
int vga_load_default_theme(enum VGA256_color_theme theme, struct Color_struct *color);
int vga_write_active_theme(char *video_memory_base);
void vga_cpy_active_theme(struct Color_struct *color);
struct Color_struct *vga_get_active_theme_ptr();
struct Color_struct vga_get_active_theme();

void vga_print_char (char buffer, int color, char *video_memory_base);
void vga_print_str(char str[], struct Color_struct *color, char *video_memory_base);
void vga_print_message(char str[], enum Message_Type msg_type, char *video_memory_base);
void vga_print_nl ();
void vga_clear_line(int row, char *video_memory_base);
void vga_clear_screen (int row, char *video_memory_base, int save_cursor);

#endif
