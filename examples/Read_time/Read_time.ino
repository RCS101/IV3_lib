#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read the time, this is stored in a structure in IV3
  IV3.read_time();
  // Print the time read from the clock
  Serial.print(IV3.time.day);
  Serial.print(":");
  Serial.print(IV3.time.month);
  Serial.print(":");
  Serial.print(IV3.time.year);
  Serial.print(" ");
  Serial.print(IV3.time.hour);
  Serial.print(":");
  Serial.print(IV3.time.minute);
  Serial.print(":");
  Serial.print(IV3.time.second);
  Serial.println("");
  delay(1000);
}
