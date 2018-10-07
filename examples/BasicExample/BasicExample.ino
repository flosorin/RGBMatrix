#include <RGBMatrix.h>

RGBMatrix screen = RGBMatrix();

void setup()
{
  // Draw pixel of each color at random location (index start at 0 as in arrays)
  screen.drawPixel(2, 4, 1, 0, 0);   // Red pixel on third line, 5th column
  screen.drawPixel(8, 30, 0, 1, 0);  // Green pixel on 9th line, 31th column
  screen.drawPixel(16, 10, 0, 0, 1); // Blue pixel on 17th line, 11th column
  screen.drawPixel(18, 22, 1, 1, 0); // Yellow pixel on 19th line, 23th column
  screen.drawPixel(21, 6, 0, 1, 1);  // Cyan pixel on 22nd line, 7th column
  screen.drawPixel(29, 16, 1, 0, 1); // Purple pixel on 30th line, 17th column
  screen.drawPixel(27, 27, 1, 1, 1); // White pixel on 28th line, 28th column

  // Draw lines and columns at the edges of the matrix
  screen.drawLine(0, 1, 0, 0); // First line in red
  screen.drawLine(31, 0, 1, 0); // Last line in green
  screen.drawColumn(0, 0, 0, 1); // First column in blue
  screen.drawColumn(31, 1, 1, 1); // Last column in white

  // You can also clear pixels
  // screen.clearPixel(27, 27); // Clear the pixel on 28th line, 28th column
  // screen.clearLine(0); // Clear the first line 
  // screen.clearColumn(31); // Clear the last column
}

void loop()
{
  screen.updateDisplay(); 
}
