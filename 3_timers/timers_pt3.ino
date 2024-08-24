#define data_dir_B        *((volatile uint8_t *) 0x24)
#define data_reg_B        *((volatile uint8_t *) 0x25)
#define port_B            *((volatile uint8_t *) 0x23)  

#define tccr1_A           *((volatile uint8_t *) 0x80)
#define tccr1_B           *((volatile uint8_t *) 0x81)
#define timsk_1           *((volatile uint8_t *) 0x6F) 

#define ubrr0_l             *((volatile uint8_t *) 0xC4)
#define ubrr0_h             *((volatile uint8_t *) 0xC5)
#define ctrl_reg_A          *((volatile uint8_t *) 0xC0)  // USCR0A
#define ctrl_reg_B          *((volatile uint8_t *) 0xC1)  // USCR0B
#define ctrl_reg_C          *((volatile uint8_t *) 0xC2)  // USCR0C
#define usart_data_reg      *((volatile uint8_t *) 0xC6)  // UDR0

#define baud_rate           0x0067

void uartInit() {

  uint8_t high_byte = (baud_rate >> 8) & 0xFF;
  uint8_t low_byte = baud_rate & 0xFF;

  ubrr0_h = high_byte;
  ubrr0_l = low_byte;

  ctrl_reg_B |= (1 << 3) | (1 << 2);

  ctrl_reg_C |= (1 << 1) | (1 << 2);
}

void sendData(uint8_t Data) {

  while (!(ctrl_reg_A & (1 << 5)));
  usart_data_reg = Data;

}

void sendString(uint8_t *str) {

  while (*str != '\0') {
    sendData(*str);
    str++;
  }

}

void timerInit () {
  cli();

  tccr1_A = 0;
  tccr1_B = 0;
  
  TCNT1 = 0; 

  tccr1_B = tccr1_B | (1 << 2); // 256 
  timsk_1 = timsk_1 | (1 << 1); 
  OCR1A =  31250; 
  sei();

}

int main() {
  
  uint8_t tick = 0;
  data_dir_B |= (1 << 5);

  uartInit();
  timerInit();

  sendString("\r\nInitializing USART & TIMER \r\n");

  while (1) {

  }

}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  port_B |= (1 << 5);
}
