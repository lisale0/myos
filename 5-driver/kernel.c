#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* targetting linux */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/*32-bit ix86 targets. */
#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif


/* Hardware text mode color constants. */
enum vga_color {
            VGA_COLOR_BLACK = 0,
            VGA_COLOR_BLUE = 1,
            VGA_COLOR_GREEN = 2,
            VGA_COLOR_CYAN = 3,
            VGA_COLOR_RED = 4,
            VGA_COLOR_MAGENTA = 5,
            VGA_COLOR_BROWN = 6,
            VGA_COLOR_LIGHT_GREY = 7,
            VGA_COLOR_DARK_GREY = 8,
            VGA_COLOR_LIGHT_BLUE = 9,
            VGA_COLOR_LIGHT_GREEN = 10,
            VGA_COLOR_LIGHT_CYAN = 11,
            VGA_COLOR_LIGHT_RED = 12,
            VGA_COLOR_LIGHT_MAGENTA = 13,
            VGA_COLOR_LIGHT_BROWN = 14,
            VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// each entry is 2 bytes wide starting at address 0xB8000
uint16_t *frame_buffer = (uint16_t*) 0xB8000;
size_t frame_row;
size_t frame_column;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

int strlen(char *str){
  size_t len = 0;
  while (str[len] != '\0'){
    len += 1;
  }
  return len;

}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
  /** Bit:     | 15 14 13 12 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
   *  0-3: Background
   *  4-7: Foreground
   *  8-15 for ASCII
   */

	return (uint16_t) uc | (uint16_t) color << 8;
}


/** write_cell
 *  write to frame buffer cell
 */
void write_cell(unsigned int i, char c, uint8_t color){
  frame_buffer[i] = c | color << 8;
}

/** get_vga_color
 */
uint8_t get_vga_color(unsigned char fg, unsigned char bg){
  return fg | bg << 4;
}


/** initialize_terminal
 * initializes the vga height and width of the terminal
 */
void initialize_teminal(){
  int idx;

  terminal_row = 0;
  terminal_column = 0;

  for (size_t y = 0; y < VGA_HEIGHT; y++){
    for (size_t x = 0; x < VGA_WIDTH; x++){
      idx = y * VGA_WIDTH + x;
      frame_buffer[idx] = vga_entry(' ', terminal_color);

    }
  }
}


void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t idx = y * VGA_WIDTH + x;
	frame_buffer[idx] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  /*reset colume and row*/
  if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

/** write_string
 * write string to terminal
 */
void write_string(char *data){
  size_t strl = strlen(data);
  for (size_t i =0; i < strl; i++){
    terminal_putchar(data[i]);
  }
}

void set_terminal_color(){
  terminal_color = get_vga_color(VGA_COLOR_GREEN, VGA_COLOR_WHITE);
}

/*Moving the cursor*/
#include "io.h"

/*The I/O Ports*/
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5


/*The I/O Port commands*/
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

void fb_move_cursor(unsigned short pos){
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);

}


void kernel_main(){
  set_terminal_color();
  initialize_teminal();
  write_string("Hello World\n");

  fb_move_cursor(5);
}
