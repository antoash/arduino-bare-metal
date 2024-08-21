#include "avr/io.h"

/*
Blink an external LED.
When button is pressed, LED will NOT glow.
When button is NOT pressed, LED will glow.

Conversion:
Bit 7 = 0b10000000 = 128

1) Set PIN8 (PB0) as input. Set PORTB bit 0 = 1 to enable pull up resistor. Connect to button.
2) Set PIN7 (PD7) as output. 
3) Read PIN8 in a loop. When PIN8 is HIGH, read PIND register. If PIND bit 0 = 1, LED will glow (PIN7 is HIGH).
4) End

PIN configuration:
1) DDRD bit 7 = 1
2) PORTD bit 7 = 1
3) DDRB bit 0 = 0
4) PORTB bit 0 = 1 (Pull up enable)
5) PINB bit 0 - read 
*/

#define Port_D      *((volatile byte *) 0x2B) 
#define Data_Dir_D  *((volatile byte *) 0x2A)
#define Port_B      *((volatile byte *) 0x25)
#define PIN_B       *((volatile byte *) 0x23)
#define Data_Dir_B  *((volatile byte *) 0x24)

int main() {

Data_Dir_D = 128;
Data_Dir_B = 0;
Port_B = 1;

while (1) {
  if (PIN_B == 0) {
    Port_D = 0;
  }
  else if (PIN_B == 1) {
    Port_D = 128;
  }
  else {Port_D = 0;}

}

}







