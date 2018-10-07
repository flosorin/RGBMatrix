#include "RGBMatrix.h"

/* Constructor: initialize pins */
RGBMatrix::RGBMatrix()
{
  DDRD = DDRD | B11111100;
  pinMode(AP, OUTPUT);
  pinMode(BP, OUTPUT);
  pinMode(CP, OUTPUT);
  pinMode(OEP, OUTPUT);
  pinMode(LP, OUTPUT);
  pinMode(ClkP, OUTPUT);

  digitalWrite(AP, LOW);
  digitalWrite(BP, LOW);
  digitalWrite(CP, LOW);
  digitalWrite(LP, LOW);
  digitalWrite(OEP, LOW);
}

/* Set all LEDs off */
void RGBMatrix::clearDisplay()
{
  for (int i = 0; i < 16; i++)
  {
    buffRed[i] = 0;
    buffGreen[i] = 0;
    buffBlue[i] = 0;
  }
}

/* Send buffers content to panel, must be called in loop() */
void RGBMatrix::updateDisplay() 
{
  for (byte row = 0; row < 8; row++) 
  {
    for (int i = 0; i < 64; i++)  
    {
      bitWrite(RGBValues, 2, buffRed[row] & (mask << (63 - i)));
      bitWrite(RGBValues, 3, buffBlue[row] & (mask << (63 - i)));
      bitWrite(RGBValues, 4, buffGreen[row] & (mask << (63 - i)));
      bitWrite(RGBValues, 5, buffRed[row + 8] & (mask << (63 - i)));
      bitWrite(RGBValues, 6, buffBlue[row + 8] & (mask << (63 - i)));
      bitWrite(RGBValues, 7, buffGreen[row + 8] & (mask << (63 - i)));
      PORTD = RGBValues;

      /* Flash clock to mark data sent */
      digitalWrite(ClkP, HIGH);
      digitalWrite(ClkP, LOW);
    }
    
    digitalWrite(OEP, HIGH);
    digitalWrite(LP, HIGH);

    /* Select new row */
    digitalWrite(AP, !!(row & B00000001));
    digitalWrite(BP, !!(row & B00000010));
    digitalWrite(CP, !!(row & B00000100));
    digitalWrite(LP, LOW);
    digitalWrite(OEP, LOW);
  }
}

/* Set a led on with an RGB color */
void RGBMatrix::drawPixel(int row, int column, const bool& red, const bool& green, const bool& blue)
{
  convertCoordinates(row, column);
  
  if (red)
  {
    buffRed[row] |= (mask << (63 - column));
  }
  else
  {
     buffRed[row] &= ~(mask << (63 - column));
  }
  if (green)
  {
    buffGreen[row] |= (mask << (63 - column));
  }
  else
  {
    buffGreen[row] &= ~(mask << (63 - column));
  }
  if (blue)
  {
    buffBlue[row] |= (mask << (63 - column));
  }
  else
  {
    buffBlue[row] &= ~(mask << (63 - column));
  }
}

/* Turn a led off */
void RGBMatrix::clearPixel(int row, int column)
{
  drawPixel(row, column, 0, 0, 0);
}

/* Set a whole line on with an RGB color */
void RGBMatrix::drawLine(int row, const bool& red, const bool& green, const bool& blue)
{
  for (int column = 0; column < 32; column++)
  {
    drawPixel(row, column, red, green, blue);
  }
}

/* Set a whole line off */
void RGBMatrix::clearLine(int row) 
{
  for (int column = 0; column < 32; column++)
  {
    clearPixel(row, column);
  }
}

/* Set a whole column on with an RGB color */
void RGBMatrix::drawColumn(int column, const bool& red, const bool& green, const bool& blue)
{
  for (int row = 0; row < 32; row++)
  {
    drawPixel(row, column, red, green, blue);
  }
}

/* Set a whole column off */
void RGBMatrix::clearColumn(int column) 
{
  for (int row = 0; row < 32; row++)
  {
    clearPixel(row, column);
  }
}

/* Adapts the coordinates to the matrix addressing system */
void RGBMatrix::convertCoordinates(int& row, int& column)
{
  if (row >= 0 && row < 8)
  {
    if (column >= 16 && column < 32)
    {
      column += 16;
    }
  }
  else if (row >= 8 && row < 16)
  {
    row -= 8;

    if (column >= 0 && column < 16)
    {
      column += 16;
    }
    else if (column >= 16 && column < 32)
    {
      column += 32;
    }
  }
  else if (row >= 16 && row < 24)
  {
    row -= 8;

    if (column >= 16 && column < 32)
    {
      column += 16;
    }
  }
  else if (row >= 24 && row < 32)
  {
    row -= 16;

    if (column >= 0 && column < 16)
    {
      column += 16;
    }
    else if (column >= 16 && column < 32)
    {
      column += 32;
    }
  }
}

