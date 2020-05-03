#include <IV3.h>

IV3_clock IV3;

void setup()
{
  Serial.begin(9600);
}

// brightness is on a scale of 1-20. Manual push button changes are in steps of 3.
int brightness = 1;

void loop()
{
  IV3.set_brightness(brightness);
  brightness++;
  Serial.println(brightness);
  if(brightness==20)
    brightness = 0;
  delay(100);
}
