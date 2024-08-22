bool LED_STATE = true;

void setup () {
  pinMode(13, OUTPUT);
  
  cli();

  // RESET registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Set timer start value
  TCNT1 = 0; 

  // Set prescalar value
  TCCR1B = TCCR1B | (1 << 2); // 256

  // Enable compare match mode 
  TIMSK1 = TIMSK1 | (1 << 1);

  // Set tick value for comparison
  OCR1A = 31250;  

  sei();

  Serial.begin(9600);
}


void loop() {
  uint32_t tick = TCNT1;
  Serial.println(tick);

}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;

  LED_STATE = !LED_STATE;
  digitalWrite(13, LED_STATE);


}