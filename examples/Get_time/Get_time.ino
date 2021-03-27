#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read the time, this is stored in a structure in IV3
  IV3.get_time();
  // Print the time read from the clock
  IV3.print_time();
  
  delay(1000);
}
