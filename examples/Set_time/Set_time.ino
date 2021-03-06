#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);

  // Set the time struct
  IV3.time.year = 21;
  IV3.time.month = 3;
  IV3.time.day = 27;
  IV3.time.hour = 12;
  IV3.time.minute = 23;
  IV3.time.second = 45;

  // Tell the clock what time it is
  IV3.set_time();
}

void loop()
{
  // Read the time, this is stored in a structure in IV3
  IV3.get_time();
  // Print the time read from the clock
  IV3.print_time();
  delay(1000);
}
