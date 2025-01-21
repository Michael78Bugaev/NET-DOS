// default_vga.c

#include <80x50vga.h>
#include <ioports.h>
#include <stdint.h>
#include <string.h>


void	vgaprint(uint8_t *str)
{
	/* Функция печати строки */
	
	// uint8_t *str: указатель на строку (на первый символ строки). Строка должна
	// быть null-terminated.

	while (*str)
	{
		putchar(*str, WHITE_ON_BLACK);
		str++;
	}
}

void	putchar(uint8_t character, uint8_t attribute_byte)
{
	/* Более высокоуровневая функция печати символа */

	// uint8_t character: байт, соответствующий символу
	// uint8_t attribute_byte: байт, соответствующий цвету текста/фона символа

	uint16_t offset;

	offset = get_cursor();
	if (character == '\n')
	{
		// Переводим строку.
		if ((offset / 2 / MAX_COLS) == (MAX_ROWS - 1)) 
			scroll_line();
		else
			set_cursor((offset - offset % (MAX_COLS*2)) + MAX_COLS*2);
	}
	else 
	{
		if (offset == (MAX_COLS * MAX_ROWS * 2)) scroll_line();
		write(character, attribute_byte, offset);
		set_cursor(offset+2);
	}
}

void	scroll_line()
{
	uint8_t i = 1;
	uint16_t last_line;

	while (i < MAX_ROWS)
	{
		memcpy(
			(uint8_t *)(VIDEO_ADDRESS + (MAX_COLS * i * 2)),
			(uint8_t *)(VIDEO_ADDRESS + (MAX_COLS * (i-1) * 2)),
			(MAX_COLS*2)
		);
		i++;
	}

	last_line = (MAX_COLS*MAX_ROWS*2) - MAX_COLS*2;
	i = 0;
	while (i < MAX_COLS)
	{
		write('\0', WHITE_ON_BLACK, (last_line + i * 2));
		i++;
	}
	set_cursor(last_line);
}

void clear_screen()
{

	uint16_t	offset = 0;
	while (offset < (MAX_ROWS * MAX_COLS * 2))
	{
		write('\0', WHITE_ON_BLACK, offset);
		offset += 2;
	}
	set_cursor(0);
}

void write(uint8_t character, uint8_t attribute_byte, uint16_t offset)
{
	uint8_t *vga = (uint8_t *) VIDEO_ADDRESS;
	vga[offset] = character;
	vga[offset + 1] = attribute_byte;
}

uint16_t get_cursor()
{

	outb(REG_SCREEN_CTRL, 14);
	uint8_t high_byte = inb(REG_SCREEN_DATA);
	outb(REG_SCREEN_CTRL, 15);
	uint8_t low_byte = inb(REG_SCREEN_DATA);
	return (((high_byte << 8) + low_byte) * 2);
}

void set_cursor(uint16_t pos)
{
	pos /= 2;

	outb(REG_SCREEN_CTRL, 14);
	outb(REG_SCREEN_DATA, (uint8_t)(pos >> 8));
	outb(REG_SCREEN_CTRL, 15);
	outb(REG_SCREEN_DATA, (uint8_t)(pos & 0xff));
}