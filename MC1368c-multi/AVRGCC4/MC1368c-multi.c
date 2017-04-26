#include "MC1368c-multi.h" 
                              // 0    1    2   3    4    5    6     7    8   9    A     B    C    D    E   F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z    -    " "
unsigned char  lcd_symbols[38]={0x7D,0x05,0x5B,0x1F,0x27,0x3E,0x7E,0x15,0x7F,0x3F,0x77,0x6E,0x78,0x4F,0x7A,0x72,0x7C,0x67,0x05,0x4D,0x63,0x68,0x54,0x46,0x7D,0x73,0x37,0x42,0x3E,0x6A,0x6D,0x4C,0x5C,0x65,0x2F,0x59,0x02,0x0};

unsigned char lcd_buffer[16]={0};

void LCD_write_byte (unsigned char byte,unsigned char len){       
while (len!=0)
        {
        len--;
        if (byte&(1<<len)){LCD_PORT|=(1<<DATA_PIN);} else {LCD_PORT&=~(1<<DATA_PIN);}
        _delay_us(2);
        LCD_PORT&=~(1<<CLK_PIN);
		_delay_us(4);
        LCD_PORT|=(1<<CLK_PIN); 
		_delay_us(2);
        	
        }
                   
}

void LCD_init(void)
{
 //�������� ������� (���������� �������� ������ � �����������)
LCD_PORT&=~(1<<CS_PIN); //CS_PIN 
_delay_us(2);
LCD_write_byte(0x8,4);//0b1000
LCD_write_byte(0x2,8); //0b00000010
_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
_delay_us(2);

//�������� ����� ������ (� ���� ������� VLCD x 1/3, ����������� 1:4)
LCD_PORT&=~(1<<CS_PIN); //CS_PIN 
_delay_us(2);
LCD_write_byte(0x8,4); //0b1000
LCD_write_byte(0x52,8); //0b01010010
_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
_delay_us(2);

//�������� LCD (���������� �������� ������ � �������� LCD)
LCD_PORT&=~(1<<CS_PIN); //CS_PIN
_delay_us(2);
LCD_write_byte(0x8,4);//0b1000
LCD_write_byte(0x6,8); //0b00000110
_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
_delay_us(2);
}

void LCD_clear(void){
unsigned char i;
LCD_PORT&=~(1<<CS_PIN); //CS_PIN
_delay_us(2);
// ������� �� ���������� ������ � ������� ������ LCD
LCD_write_byte(0x5,3);//0b101
// �������� ���������� ������, � �������� ������ ���������� � ������� ������ LCD
LCD_write_byte(0,6);//0b000000
//���������� 16 ��� � ��������� ������ ����, ���� �������� ��� LCD �������� � ������������� �������, �� ���� ������� �������. 
//������� ������ � ���������� ������������ ����������� �������� �� 1 �� ������ 4 ����. 
for (i=0; i<16;i++)
{
LCD_write_byte(0,8);//0b00000000
}
_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
}

void LCD_on_off(_Bool on_off)
{
LCD_PORT&=~(1<<CS_PIN);
_delay_us(2);
LCD_write_byte(0x8,4); // 0b1000
if (on_off==1)
{LCD_write_byte(0x6,8);} //0b00000110 �������� �������
else
{LCD_write_byte(0x4,8);} //0b00000100 ��������� �������
_delay_us(2);
LCD_PORT|=(1<<CS_PIN);	
}	

void LCD_clean_buffer(unsigned char start,unsigned char end)
{
unsigned char a; for (a=start;a<end+1;a++) {lcd_buffer[a]&=0x80;}
}
	
void LCD_write_buffer(unsigned char pos,unsigned char len){
unsigned char a;

LCD_PORT&=~(1<<CS_PIN); //CS_PIN
_delay_us(2);
// ������� �� ���������� ������ � ������� ������ LCD
LCD_write_byte(0x5,3);//0b101
LCD_write_byte((pos<<1),6);//��������� ��������� ����� ������ �������� ������������ ������� ������� �� ������� � ���������� ��� � �������. 

// ������������� ����� � ��������� ������� pos � �� ��������� ����� len
for (a=pos;a<(len+pos);a++)
{
LCD_write_byte(lcd_buffer[a],8);
}
_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
}

void LCD_print_digit(int digit, unsigned char pos_dig,unsigned char len,unsigned char radix,_Bool on_off)
{
  char str[len];
  unsigned char i=0, ascii_conv, mask;
  if (on_off==1){mask=0x7F;} else {mask=0;} 
  itoa(digit,str,radix);
   
while (str[i]!=0)
{         
    ascii_conv=str[i]-0x30;
	if (ascii_conv==0xFD){ascii_conv=0x24;} // ��������� ���� �����
	if(ascii_conv>=0x31){ascii_conv=ascii_conv-0x27;} // ��������� ����� ��� HEX (radix 16)
	lcd_buffer[i+pos_dig]=(lcd_buffer[i+pos_dig]&0x80)|((lcd_symbols[ascii_conv])&mask);
    i++;
}
while (i<len){ lcd_buffer[i+pos_dig]=(lcd_buffer[i+pos_dig]&0x80);i++;}
 LCD_write_buffer(pos_dig,len);
}

void LCD_print_string (char *string,unsigned char pos_str,_Bool on_off)
 {
   unsigned char i=0, ascii_conv,mask;
   if (on_off==1){mask=0x7F;} else {mask=0;} 
while (string[i]!=0)
{         
    ascii_conv=string[i]-0x30;
	if(ascii_conv>=0x11){ascii_conv=ascii_conv-0x07;}
    if (ascii_conv==0xF6){ascii_conv=0x24;} // ��������� ���� �����
	if (ascii_conv==0xE9){ascii_conv=0x25;} // ��������� ������
    
	lcd_buffer[i+pos_str]=(lcd_buffer[i+pos_str]&0x80)|((lcd_symbols[ascii_conv])&mask);
    i++;
}   
  LCD_write_buffer(pos_str,i);

 }
 
void LCD_mnemsymb_on(unsigned char symbol,_Bool on_off)
{
unsigned char symb_pos[10]={0,2,3,5,6,7,10,11,13,15},address=0;
lcd_buffer[symb_pos[symbol]]=lcd_buffer[symb_pos[symbol]]|0x80;//0b10000000
if (on_off==0){lcd_buffer[symb_pos[symbol]]=lcd_buffer[symb_pos[symbol]]&~0x80;} //0b10000000
 address=symb_pos[symbol];
 if (address&1){address++;}
 
LCD_PORT&=~(1<<CS_PIN); //CS_PIN
_delay_us(2);
// ������� �� ���������� ������ � ������� ������ LCD
LCD_write_byte(0x5,3);//0b101 
LCD_write_byte((address<<1),6);//��������� ��������� ����� ������ ��������, ������������ ������� ������������ �� �������, � ���������� ��� � �������.

LCD_write_byte(lcd_buffer[symb_pos[symbol]],8); //���������� ��������� ���� � ���������� 7 ����� �� ������ � �������, ���� ������ ��� �������� �����������. 

_delay_us(2);
LCD_PORT|=(1<<CS_PIN); //CS_PIN
}
