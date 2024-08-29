### Timers
1) Timers available       

   There are three timers available on the Arduino board.     
   _TIM0, TIM2_ - 8 bit timer, counts upto 255.                                     
   _TIM1_ - 16 bit timer, counts upto 65535.                    
3) Important concepts to know              
   - Tick - counter increment                   
   - Frequency F: the number of pulses produced in a single second. F = 1/T = pulse/second                            
   - Time period T: duration of a single pulse in seconds. Inverse of frequency.                        
   - System clock: a continuous signal oscillating between HIGH and LOW state at a constant interval.     
        The clock frequency for the Arduino Uno is the 16MHz quartz crystal by default. It produces 16 million clock pulses per second/a pulse every 62.5 nano seconds.                             
   - Prescalar: divides the clock frequency by a constant factor. A prescalar of 8 reduces the 16MHz clock into 2MHz.              
        Frequency decreases as prescalar increases. The number of pulses produced per second decreases.             
   - Time period for each pulse increases. The duration of a single pulse becomes larger.                      
4) What are the interrupts available?                 
   **Compare Match:** a value is stored in a separate register.               
   &emsp;When the timer value is equal to stored value, an interrupt is triggered.                                 
   &emsp;Useful for events that occur periodically at a set interval like data captured from a sensor.       
   **Compare Match Overflow:**                
   &emsp;Triggered when the timer overflows.                           
   &emsp;An overflow is when the timer passes back to zero after counting to the max value possible.                            
   &emsp;It is 255 for an 8bit timer and 65526 for a16bit timer.                    
   **Input capture interrupt:**                
   &emsp;Can only be implemented on TIMER 1.                 
   &emsp;An input to a pin is read and stored each time a particular external event occurs on that pin.                        
   &emsp;Useful for precise measurement of pulses or frequency of signal.                     
5) Registers relevant to this example               

   x - 0, 1, 2 (corresponding to TIM0, TIM1, TIM2)              
   _**TCCRxA**_ - Timerx/Counter x Control Register  B.                        
	   &emsp;by default, all bits are 1 which enables PWM signal on pins 9 & 10.               
	   &emsp;This is essentially set by analogWrite() function. Set all the bits to 0 to disable PWM on pins 9 &10.                   
   **_TCCRxB_** - Timerx/Counter x Control Register B.               
	   &emsp;only the first three bits are relevant for this example.                 
	   &emsp;_CS02, CS01, CS00_ - Clock select bits. Set the a prescalar value.           
   **_TCNTx_** - Timer/Counter x                         
	   &emsp;16 bit register with two components _TCNTxH & TCNTxL_        
	   &emsp;This register holds the current counter tick value while the timer is running.                           
	   &emsp;Read the current value/Write to it to set the timer's starting value.                               
   **_OCRxA_** - Output Compare Register x A                      
	   &emsp;16 bit register with two components _OCRxAH & OCRxAL_           
	   &emsp;One of the two Output Compare Registers available for TIMER 1.                                            
	   &emsp;Stores the tick value that is continuously compared with the counter value in _TCNTx_.                              
   **_TIMSKx_** - Timer/Counter x Interrupt Mask Register              
	   &emsp;only Bit 1 - _OCIE1A_ is relevant.                     
	   &emsp;When _OCIE1A_ is 1, output compare match interrupt is enabled for Output Compare register A _OCRxA_.                  
              
6) Example scenario and calculations      
   ***An interrupt is required to toggle an LED at 500ms.***                   
   
   - System clock frequency = 16MHz (16 million cycles per second)                     
   - Time period of a single cycle = 1/F = 62.5ns (time taken for a clock cycle)                         
   - The timer is 16bits so the max resolution is 0 to 65535.                                                      
   - Max time duration before counter resets: 62.5ns x 65536 = 4.095ms < 500ms             
   Only possible variable is the time period, so we utilize the prescalar.                  
         
   By using a prescalar, frequency decreases, time period increases which can increase the duration of the time counted by the timer.               
   
   - Prescalar = 8             
   - Frequency = 16M/8 = 2MHz                         
   - Time period = 50us                         
   - Max time duration before counter resets: 50us x 65536 = 0.032s < 500ms                         

   A prescalar of 8 won't suffice.

   - Prescalar = 256                            
   - Frequency = ${16M\over256} = 0.0625MHz$             
   - Time period =  16us                      
   - Max time duration before counter resets: ${16us \times 65536} = 1.048s > 500ms$           
   - This configuration enables the counter to go from 0 to 65536 in 1.048 seconds.                         
   
   Finding the number of counter ticks to reach 500ms:               
   &emsp;1.048s -> 65536                                         
   &emsp;0.5s   ->  x   
  &emsp; $x = {{0.5 \times 65536} \over 1.048} = 31250 ticks$                     
               
7) Pseudocode             
   - Set PIN 13 in OUTPUT mode.             
   - Reset _TCCR1A_ & _TCCR1B_.                          
   - Set prescalar: _TCCR1B_ = 0b00000100 = 5                        
   - Enable compare match mode A: _TIMSK1_ = 0b00000010 = 2              
   - Set output compare value as calculated: 31250 
   - Set the Interrupt Service Routine for TIMER 1 Compare Register A when timer reaches _OCRxA_ value to toggle LED state.                     
                
   

### References
- [Timer Interrupt ISR + Examples | Arduino101 | Set Registers & Modes - YouTube](https://youtu.be/Uv9UeYUsA8A?si=0B-ytqofBCjJdeX7)
- [Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (microchip.com)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
