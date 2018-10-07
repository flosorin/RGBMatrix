#include "Arduino.h"

/*
   Arduino library to allow controlling RGB LED panel 32x32 scan rate 1/8
   Panel needs to be continuosly redrawn in order to power LEDs.

   Pins:
   R1,R2 - red led for upper & lower half
   G1,G2 - green led for upper & lower half
   B1,B2 - blue led for upper & lower half

   A,B,C - row selector = 2^3 = 8 rows (2 upper & 2 lower halves x 8 = 32 rows)

   CLOCK - clock (flash to notify panel that bits has been sent)
   LP    - latch/strobe (notify panel that row has been sent)
   OE    - output enable

   Simple procedure:

   1) Clock in data for entire row (use R1,G1,B1,R2,G2,B2 for data and CLK for clock)
   2) OE high
   3) Select line address (A,B,C)
   4) LAT high
   5) LAT low
   6) OE low
   
   -- Pinout --

   Colors pins are all connected to port D, starting from PD2 to PD7 (Arduino Uno pin 2 to 7), in the order R1,G1,B1,R2,G2,B2.

   A, B, C are connected to A0, A1, A2 respectively.

   Clock to pin 9, OEP to pin 10, LP to pin 11.
*/

class RGBMatrix
{
  public:
    RGBMatrix(); // Constructor : initialize pins

    void clearDisplay(); // Set all LEDs off
    void updateDisplay(); // Send buffers content to panel, must be called in loop() 
    
    void drawPixel(int row, int column, const bool& red, const bool& green, const bool& blue); // Set a led on with an RGB color
    void clearPixel(int row, int column); // Turn a led off
    
    void drawLine(int row, const bool& red, const bool& green, const bool& blue); // Set a whole line on with an RGB color
    void clearLine(int row); // Set a whole line off
    
    void drawColumn(int column, const bool& red, const bool& green, const bool& blue); // Set a whole column on with an RGB color
    void clearColumn(int column); // Set a whole column off
      
  private :

    void convertCoordinates(int &row, int &column); // Adapt the coordinates to the matrix addressing system
    
    /* Row selector 0-7 */
    int AP = A0;           // A Pin
    int BP = A1;           // B Pin
    int CP = A2;           // C Pin
    
    /* Control pins */
    int OEP = 10;         // OE Pin
    int LP = 11;          // Latch Pin
    int ClkP = 9;         // Clock Pin
    
    /* Buffers for RGB colors and mask for led selection */
    uint64_t buffRed[16] = { 0 };
    uint64_t buffGreen[16] = { 0 };
    uint64_t buffBlue[16] = { 0 };
    uint64_t mask = 0x0000000000000001;
    
    byte RGBValues = B00000011;

};
