#include <IV3.h>

IV3_clock IV3;

void setup()
{
  bool night_fade = true; // true sets the fade to occur.

  // Night fade sets the clock brightness to minimum during the hours of 12-7
  // This function can be used to turn this feature on or off.
  IV3.set_night_fade(night_fade);
}

void loop()
{
}
