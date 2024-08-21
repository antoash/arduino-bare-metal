/* 
Blink an external LED.

Rewriting the code using bitwise operations.
*/

#define Port_D      *((volatile byte *) 0x2B) 
#define Data_Dir_D  *((volatile byte *) 0x2A)
#define Port_B      *((volatile byte *) 0x25)
#define PIN_B       *((volatile byte *) 0x23)
#define Data_Dir_B  *((volatile byte *) 0x24)

int main() {

Data_Dir_D = Data_Dir_B | (1 << 7); // 0b10000000
Data_Dir_B = B00000000; 
Port_B = Port_B | (1 << 0); // 0b00000001


while (1) {
  int pin_status = (PIN_B & (1 << 0)) >> 0;
  if (pin_status == 0) {
    Port_D = B00000000;
  }
  else if (pin_status == 1) {
    Port_D = Port_D | (1 << 7);
  }
  else Port_D = B00000000;

}

}