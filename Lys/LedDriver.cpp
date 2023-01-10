#include "Headers/LedDriver.h"

LedDriver::LedDriver(unsigned char port, unsigned char bit)
: _port(port), _bit(bit)
{	
	switch(_port)
	{
		case 'A':
			DDRA = 0xFF;
			break;
		
		case 'B':
			DDRB = 0xFF;
			
			if (_bit == 7)
			{
				// TIMER 0 (pin 13 (PB7)) -----
				
				TCCR0A = 0b10000011;
				TCCR0B = 0b00000001;
				OCR0A = 0;
				
				// ----------------------
			}
			else if (_bit == 5)
			{
				// TIMER 1 (pin 11 (PB5)) -----
				
				TCCR1A = 0b10000011;
				TCCR1B = 0b00000001;
				OCR1A = 0;
				
				// ----------------------
			}
			break;
			
		case 'C':
			DDRC = 0xFF;
			break;
		
		case 'H':
			DDRH = 0xFF;
			break;
	}
}

void LedDriver::off()
{
	unsigned char pattern = 0b11111110 << _bit;
	
	switch(_port)
	{
		case 'A':
			PORTA &= pattern;
			break;
		
		case 'B':
			PORTB &= pattern;
			
			break;
			
		case 'C':
			PORTC &= pattern;
			break;
		
		case 'H':
			PORTH &= pattern;
			break;
	}
}

void LedDriver::on(unsigned char intensity)
{
	unsigned char pattern = 0b00000001 << _bit;
	
	switch(_port)
	{
		case 'A':
			PORTA |= pattern;
			break;
		
		case 'B':
			PORTB |= pattern;
			
			if (_bit == 7)
			{
				OCR0A = intensity;
			}
			else if (_bit == 5)
			{
				OCR1A = intensity / 255 * 65535;
			}
			break;
			
		case 'C':
			PORTC |= pattern;
			break;
		
		case 'H':
			PORTH |= pattern;
			break;
	}
}