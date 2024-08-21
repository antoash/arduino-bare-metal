### _Files_   
blinky_pt1 - basic code implementation  
blinky_pt2 - with preprocessor directive #define

### _Process flow_
1) Identifying the address of ports and data registers.   
	`Pin 13 - PORTB 5th bit       `

	`PORTB (data register, HIGH=1, LOW=0) - 0x25, bit 5 HIGH     `           
	
    `DDRB (data direction, input=0, output=1) - 0x24, bit 5 HIGH`                          
	
    `PINB (Port B input pins) - 0x23 (read only)             `        
2) Understand referencing and dereferencing in pointers:      

```c                  
   int a = 89;                                                         
   int *ptr = &a; 
   *ptr = 30;
   byte ddrb = 0x25;
   *ddrb = 32;
```  

3) What is volatile keyword in C?                                  
   Prevents optimization by the compiler. For example, if an unused variable is initialized, the compiler will ignore it in order to optimize for efficiency. However, using the volatile keyword, it will always initialize.                          
   Similarly, it prevents caching. When initialized with a particular value, the value is read from memory each time it is accessed.   
   [Volatile Keyword in C - javatpoint](https://www.javatpoint.com/volatile-keyword-in-c)    
   [c# - What is the "volatile" keyword used for? - Stack Overflow](https://stackoverflow.com/questions/3430757/what-is-the-volatile-keyword-used-for)     
   
   ```c
   volatile byte* ddrb = 0x25;
   *ddrb = 32;
    ```


4) Code and implement!

    ```c
    int main() {

        volatile byte *data_direction_reg = 36; // 0x24 = 36
        volatile byte *data_reg_b = 37 // 0x25 = 37
        *data_direction_reg = 32; // PORTB bit 5 (PIN 13) in output state
        while(1) {           
            *data_reg_b = 32; // PIN 13 is HIGH   
            _delay_ms(5000);    
            *data_reg_b = 0; // PIN 13 is LOW    
            _delay_ms(1000);    
        }   
    }   
    ```
5) Simplifying the code with preprocessor macros:       

    ```c
    #define GPIO_PORT_B_PIN_5 *(( volatile byte* ) 0x25)
    #define GPIO_PORT_B_PIN_5 *(( volatile byte* ) 0x25)
    
    int main() {
    
    DataDir_B = 32;  // GPIO in output mode
    
    while(1) {
      GPIO_PORT_B_PIN_5 = 32; // PIN 13 is HIGH
      _delay_ms(5000);
      GPIO_PORT_B_PIN_5 = 0; // PIN 13 is LOW
      _delay_ms(5000);
      }
    }
    ```

### _References_
- [Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (microchip.com)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)   
- [Bare-Metal MCU #1 - Intro to registers - YouTube](https://www.youtube.com/watch?v=tBq3sO1Z-7o&list=PLNyfXcjhOAwOF-7S-ZoW2wuQ6Y-4hfjMR)   
- [Bare-Metal MCU #2 - Set Registers by Memory Address (youtube.com)](https://www.youtube.com/watch?v=W8REqKlGzDY&list=PLNyfXcjhOAwOF-7S-ZoW2wuQ6Y-4hfjMR&index=2) 
