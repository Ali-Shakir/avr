#define F_CPU 12000000
#define LCD_PORT PORTB // PORTB2 - CS; PORTB1 - WR; PORTB0 - DATA;
#define DATA_PIN 0
#define CLK_PIN 1
#define CS_PIN 2
#define BIN 2
#define DEC 10
#define HEX 16
#define true 1
#define false 0 


#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <stdlib.h>



void LCD_write_byte (unsigned char byte, unsigned char len);

void LCD_on_off(_Bool on_off); //включает/выключает дисплей

// эти функции пользователю не нужны в общем случае
void LCD_clean_buffer(unsigned char start,unsigned char end);
void LCD_write_buffer(unsigned char pos,unsigned char len);

// это пользовательские функции
void LCD_init(void);
void LCD_clear(void);
void LCD_print_digit(int digit,unsigned char pos_dig,unsigned char len,unsigned char radix,_Bool on_off);//LCD_print_digit(число,позиция,длина,система_счисления,Включить_выключить);
void LCD_print_string (char *string,unsigned  char pos_str,_Bool on_off);
void LCD_mnemsymb_on(unsigned char symbol,_Bool on_off);
