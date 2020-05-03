#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);
  bool hourMode12 = true; // True puts it into 12h mode, false into 24h mode

  // Set Clock into 12h mode from default 24h
  IV3.set_hour_mode(hourMode12);
}

void loop()
{
}
