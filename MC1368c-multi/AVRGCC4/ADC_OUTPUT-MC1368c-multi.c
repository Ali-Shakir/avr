


#include "MC1368c-multi.h"
#include <avr/interrupt.h>
#include <util/delay.h>


// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
_delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

ISR (TIMER0_COMP_vect)
{
	cli();
	LCD_print_digit((read_adc(7)>>2),0,3,DEC,true);
	sei();
	
}	


int main(void)
{DDRB|=(1<<DATA_PIN)|(1<<CLK_PIN)|(1<<CS_PIN);LCD_PORT|=(1<<CLK_PIN)|(1<<CS_PIN);
	DDRC|=(1<<0);PORTC|=(1<<0);

// ADC initialization
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);


// Timer/Counter 0 initialization
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x74;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (0<<TOIE0);
	
	

	sei();
	
	LCD_init();
	LCD_clear();
	
	 while(1)
    {						
				        
    }
		
}