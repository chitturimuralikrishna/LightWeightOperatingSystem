#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"  
#include "memory/heap/kheap.h"


// writing own print code in kernal
uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

/**
 * Creates a 16-bit character with the given character and colour.
 *
 * @param c The character to be included in the 16-bit character.
 * @param colour The colour of the character.
 *
 * @return The 16-bit character created by combining the given character and colour.
 *
 * @throws None
 */
uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

/**
 * Writes a character to the terminal at the specified coordinates with the given color.
 *
 * @param x the x-coordinate of the character position
 * @param y the y-coordinate of the character position
 * @param c the character to be written
 * @param colour the color of the character
 *
 * @throws None
 */
void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

/**
 * Writes a character to the terminal with the specified colour.
 *
 * @param c The character to write.
 * @param colour The colour of the character.
 *
 * @throws None
 */
void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}
/**
 * Initializes the terminal by setting the video memory address, 
 * resetting the terminal row and column, and clearing the screen.
 *
 * @return None
 */
void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}


/**
 * Calculates the length of a null-terminated string.
 *
 * @param str A pointer to the string to be measured.
 *
 * @return The length of the string, excluding the null terminator.
 *
 * This function iterates over the characters in the string until it encounters a
 * null character ('\0'). It keeps track of the number of characters it has
 * encountered and returns that value as the length of the string.
 *
 * Example Usage:
 * @code
 *     char str[] = "Hello, world!";
 *     size_t len = strlen(str);
 *     printf("The length of the string is %zu\n", len); // Output: 13
 * @endcode
 */
size_t strlen(const char* str)
{
    size_t len = 0; // Initialize the length to 0

    // Iterate over the characters in the string
    while(str[len])
    {
        len++; // Increment the length for each character
    }

    return len; // Return the length of the string
}

/**
 * Prints the given string to the terminal.
 *
 * @param str The string to be printed.
 *
 * @throws None
 */
void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

/**
 * Initializes the terminal and prints a message to the console.
 *
 * @return void
 */
void kernel_main()
{
    terminal_initialize();
    print("Hello world!\ntest");

    //Initialize the heap
    kheap_init();

    // Initialize the Intrrupt Descriptor Table (IDT)
    idt_init();

    //enable_interrupts(); // this is causing seabio or crash in WSR, so try to install vm and try
    //outb(0x60, 0xff);
    
    void *ptr = kmalloc(10);
    void *ptr2 = kmalloc(100); 

    kfree(ptr);

    void *ptr3 = kmalloc(10);

    if(ptr != NULL  || ptr2 != NULL ||  ptr3 != NULL)
    {

    }

    while(1)
    {
    }
}
