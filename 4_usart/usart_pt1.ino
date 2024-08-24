#define baud_rate     0x0067
#define ubrr0_l       *((volatile uint8_t *) 0xC4)
#define ubrr0_h       *((volatile uint8_t *) 0xC5)
#define ctrl_reg_A    *((volatile uint8_t *) 0xC0)  // USCR0A
#define ctrl_reg_B    *((volatile uint8_t *) 0xC1)  // USCR0B
#define ctrl_reg_C    *((volatile uint8_t *) 0xC2)  // USCR0C
#define data_reg      *((volatile uint8_t *) 0xC6)  // UDR0

void UARTinit() {
  uint8_t high_byte = (baud_rate >> 8) & 0xFF;
  uint8_t low_byte = baud_rate & 0xFF;

  // Set baud rate
  ubrr0_h = high_byte;
  ubrr0_l = low_byte;

  // Enable Rx & Tx
  ctrl_reg_B = ctrl_reg_B | (1 << 3) | (1 << 4);

  // Set data frame format
  ctrl_reg_C = ctrl_reg_C | (1 << 1) | (1 << 2);
}

void sendData(uint8_t data) {
  while (!(ctrl_reg_A & (1 << 5)));  // Loop until data register is empty

  data_reg = data;
}

void sendString(uint8_t *str) {
  
  while(*str != '\0') {
    sendData(*str);
    str++;
  }
}

uint8_t receiveData(void) {

  // Exit loop when RXC0 bit = 0 

  while(!(ctrl_reg_A & (1 << 7))) {
    _delay_ms(1000);
  }

  return data_reg;

}


int main() {

  uint8_t tx_buffer[20] = "Hello there \r\n";
  uint8_t rx_buffer;
  UARTinit();

  sendData('h');
  sendData('e');
  sendData('l');
  sendData('l');
  sendData('o');
  sendData('\r');
  sendData('\n');
  sendString(tx_buffer);
  sendString("Check if this function is working! \r\nHopefully it is hahaha! \r\n");
  sendString("\r\nYou can now send strings thru UART yay!\r\n");

  sendString("Enter Data:\r\n");

  while (1) {
    rx_buffer = receiveData();
    sendData(rx_buffer);
  }

}