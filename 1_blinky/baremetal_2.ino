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
#define DataDir_B         *((volatile byte*) 0x24) 
#define GPIO_PORT_B_PIN_5 *(( volatile byte* ) 0x25)

int main() {

DataDir_B = 32;  

while(1) {
  GPIO_PORT_B_PIN_5 = 32;
  _delay_ms(7000);
  GPIO_PORT_B_PIN_5 = 0;
  _delay_ms(6000);  
  }

}