// same code but without pinMode() & digitalWrite

#define data_dir_B *((volatile uint8_t *) 0x24)
#define data_reg_B *((volatile uint8_t *) 0x25)
#define port_B     *((volatile uint8_t *) 0x23)  
#define tccr1_A    *((volatile uint8_t *) 0x80)
#define tccr1_B    *((volatile uint8_t *) 0x81)
#define timsk_1    *((volatile uint8_t *) 0x6F) 

int main() {
  Serial.begin(9600);
  
  cli();

  // PIN 13 in OUTPUT mode
  data_dir_B |= (1 << 5);
  
  // RESET registers
  data_reg_B = 0;
  tccr1_A = 0;
  tccr1_B = 0;
  
  // Set timer start value
  TCNT1 = 0; 

  // Set prescalar value
  tccr1_B = tccr1_B | (1 << 2); // 256 

  // Enable compare match mode for register A
  timsk_1 = timsk_1 | (1 << 1); 

  // Output Compare tick value
  OCR1A =  31250; 

  sei();
  Serial.begin(9600);

  while (1) {
  uint32_t tick = TCNT1;
  Serial.println(tick);
  }
 
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;

  port_B |= (1 << 5);

}
