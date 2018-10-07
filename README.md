# RGBMatrix

Arduino library to allow controlling RGB LED panel 32x32 scan rate 1/8.
Panel needs to be continuosly redrawn in order to power LEDs.

## How does it works

### Pins

R1,R2 - red led for upper & lower half
G1,G2 - green led for upper & lower half
B1,B2 - blue led for upper & lower half

A,B,C - row selector = 2^3 = 8 rows (2 upper & 2 lower halves x 8 = 32 rows)

CLOCK - clock (flash to notify panel that bits has been sent)
LP    - latch/strobe (notify panel that row has been sent)
OE    - output enable

### Procedure

1) Clock in data for entire row (use R1,G1,B1,R2,G2,B2 for data and CLK for clock)
2) OE high
3) Select line address (A,B,C)
4) LAT high
5) LAT low
6) OE low
   
## Pinout

Colors pins are all connected to port D, starting from PD2 to PD7 (Arduino Uno pin 2 to 7), in the order R1,G1,B1,R2,G2,B2.

A, B, C are connected to A0, A1, A2 respectively.

Clock to pin 9, OEP to pin 10, LP to pin 11.