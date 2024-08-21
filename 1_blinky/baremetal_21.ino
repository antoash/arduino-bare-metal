#include "avr/io.h"
/*
Conversions:
0x24 - 0b00011000 - 36
0x25 - 0b00011001 - 37

Steps:
PIN 13 - PORTB 5:
DDRB, address 0x24. Set 6th bit HIGH. GPIO Output Mode.

PORTB, address 0x25. Set 6th bit HIGH
delay(2000)
PORTB, address 0x25. Set 6th bit  LOW
delay(500)
*/

int main() {

// setting up the address 
volatile byte *data_direction_reg = 36; // 0x24 = 36
volatile byte *port_b =  37; // 0x25 = 37

*data_direction_reg = 32;  // GPIO output mode


while(1) {
  *port_b = 32; // PIN 13 is HIGH
  _delay_ms(5000);
  *port_b = 0; // PIN 13 is LOW
  _delay_ms(5000);

  }

}