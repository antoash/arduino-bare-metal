### Serial Communication using USART 

1) Basic concepts         

   - Serial communication: data transfer between devices bit by bit              
   - Synchronous comms: both the receiver and transmitter are in sync with a common clock signal. Data is sent and received continuously.                                
   - Asynchronous comms: the transmitter and receiver are not in sync with a common clock signal. Start & stop bits are required in order to help rx and tx identify when transmission starts and ends.                   
   - USART - Universal Sync/Asynchronous Receiver Transmitter. Arduino UNO has only one USART pin.                        
   - They are responsible for breaking down bytes of data into single bits for transmission. Also handle conversion of individual bits into bytes on the receiving end.                           
   - Data Packet: consists of start bit, data frame, stop bit and parity bit. The start bit indicates the beginning of transmission.                     
   - The data frame is the data to be sent across. Parity bits are used to ensure data received is not corrupt. Stop bit indicate the end of transmission.                                
   - Asynchronous USART -                  
   - Synchronous USART - an extra wire is required for clock.                   
   - MSPIM - Master SPI: set up UART as a master for SPI communication.                 
2) USART relevant concepts          

   When idle, the data transmission line remains high.transmission.                                   
   - Baud Rate -  a transmission per second.                    
   - Timing - time taken in seconds for transfer of a single bit. $t = {1\over B}$                                
   - Start bit - it is used to initiate data transmission. Start bit is always LOW in order to enable communication.                  
   - When RX identifies the falling edge, it begins reading data.                                        
   
   Parity bit - there are 3 options to set a parity bit; odd, even or none. Mainly used to check if the data sent is correct.                      
   - Even parity - when total number of bits of value 1 sent across is even including the parity bit. Compute by performing XOR operation on each bit and finally a 0.                             
   - Odd parity - when the total number of bits of value 1 sent across is odd including the parity bit. Compute by performing XOR operation on each bit and finally a 1.                       
   - Stop bits - drive the transmission line from LOW to HIGH to indicate transmission has completed. Can be a single bit or two bits.
3) Registers                                     
   x - 0 (Only one timer on Arduino UNO)

   **_UDRx_** - USART I/O Data Register x                                   
   - Data to be transmitted/received can be written to this register.                         

   **_UCSRxA_** - USART Control & Status Register x A                      
   - Stores the status of the transmission, each bit represents a status flag like transmit complete, receive complete, frame error, data overrun etc.                  
   - Bit _UDREx_ = 1 indicates that the register _UDRx_ is empty and can receive data. If this bit is not 1, whatever data written will be ignored by the transmitter.         
   
   **_UCSRxB_** - USART Control & Status Register x B         
   - enable features like Receiver/Transmitter to override the default port operation to receive and transmit data, Rx/Tx interrupts, set character size bit.                     
   - Bits _RXENn_ & _TXENn_ enables the receiver and transmitter.         
   
   **_UCSRxC_** - USART Control & Status Register x C         
   - Set USART mode using _UMSELn1 & UMSELn0_ (Async - UART, Sync - USRT, Master SPI).         
   - Set number of stop bits to be inserted by the transmitter using _USBSm_ bit.          
   - Set the character size using _UCSZ01_ & _UCSZ00_ bits.          
   - Set _UDORDx_ bit to 1 for LSB of data to be transmitted first, set it to 0 for MSB transmission first.         
   - Set _UCPHAx_ & _UCPOLx_ bit to specify clock phase & polarity for synchronous transmission which requires a clock: sampling/setup with falling/rising edge.           
   
   **_UBRRxL_ & _UBRRxH_** - USART Baud Rate Registers         
   - A 16bit register where 12bits are used to set the baud rate. The remaining 4 bits are reserved.      

4) Code overview         

   Init Function:         
   &emsp;Define baud rate         
   &emsp;Set frame format - 8 characters, 1 stop bit: _UCSR0C_ = 0b00000110          
   &emsp;Enable Rx/Tx: _UCSR0B_ = 0b00011000          
   &emsp;Set baud rate: _UBRR0_ = 103 = 0x0067         
            
   Send Data Function:         
   &emsp;While UDRE1 != 1, loop         
   &emsp;Set the UDR0 register with data.

   Send String Function:    
   &emsp;Pass string as an argument.                                          
   &emsp;While string != NULL character, use send data function to send each letter.    
   &emsp;Increment the string literal to move to the next letter in the string.     
            
### References         
- [11A. Serial Communications -- USART - YouTube](https://www.youtube.com/watch?v=W5xt6w5EMP0)         
- [UART: A Hardware Communication Protocol Understanding Universal Asynchronous Receiver/Transmitter | Analog Devices](https://www.analog.com/en/resources/analog-dialogue/articles/uart-a-hardware-communication-protocol.html)
- [Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf (microchip.com)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcont-ATmega328P_Datasheet.pdf)
         
            