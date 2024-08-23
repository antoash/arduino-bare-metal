## Blink an external LED.

| Button  | LED |
| ------- | --- |
| ON      | OFF |
| OFF     | ON  |

externalBlinky_pt1 - basic implementation  
externalBlinky_pt2 - implementation using bitwise operations

## Bitwise Operations
_Variables that are used in the following examples._
```C
int x = 5; //  0b00000101
int y = 11; // 0b00001011
int z = 0;
```

## AND 
Perform AND operation on each bit. Carry overs are not considered (1 & 1 = 1)
```C
/*
  0b00000101
& 0b00001011
  ----------
  0b00000001
*/
z = x & y; // 0x00000001
```
Results in 1.

## OR 
Perform OR operation on each bit.
```C
/*
  0b00000101
| 0b00001011
  ----------
  0b00001111
*/

z = x | y; // 0x00001111
```
Results in 15.

## XOR 
1 _xor_ 0 OR 0 _xor_ 1 = 1 else 0
```c
/*
    0b00000101
xor 0b00001011
	----------
	0b00001110

*/

z = x ^ y; // 0x00001110
```
Result = 14.

## Left Shift
Append zeros to the end of the byte. The result is double the original value.
```c
/*
0b00000101 << 1
----------
0b000001010
*/
z = x << 1; // 5x2
```
Result = 10.

## Right Shift
Append zeros to the start of the byte. The result is half the original value.
```C
/*
z = x >> 1
0b00000101 >> 1
----------
0b000000101
*/
z = x >> 1; // 5/2
```
Result = 2.

## Bit Set
Set the nth bit
```
reg = reg | (1 << n)
```

## Bit Reset
Reset 5th bit: n = 5
```
reg = reg & ~(1 << n)
```
Every other bit is left alone. Only the fifth 5th bit is reset. 

## Bit Status
Get the status of the 5th bit.
```
pin5_status = (reg & (1 << 5)) >> 5
```
Returns 0/1 depending on the status.

## Byte Splitting
Split 16 bits into two 8 bit words
```c
high_byte = reg >> 8 & 0xFF;
low_byte = reg & 0xFF;
```


## References:
[C bitwise operators 🔣 (youtube.com)](https://www.youtube.com/watch?v=BGeOwlIGRGI)
[Getting Started with Baremetal Arduino C Programming | No IDE Required [Linux SDK] (youtube.com)](https://www.youtube.com/watch?v=j4xw8QomkXs)


