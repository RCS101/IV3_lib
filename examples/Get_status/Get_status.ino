#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read the status of the clock. This tells you which hour mode, night fade mode and brightness
  Serial.print("Hour mode: ");
  Serial.print(IV3.get_hour_mode());
  Serial.print(" Fade mode: ");
  Serial.print(IV3.get_fade_mode());
  Serial.print(" Brightness: ");
  Serial.println(IV3.get_brightness());
  delay(1000);
}
