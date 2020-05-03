#include "IV3.h"
#include "Wire.h"

void IV3_clock::set_time(void)
{
  uint8_t TX[7] = {SET_TIME, time.year, time.month, time.day, time.hour, time.minute, time.second};
  Wire.begin();
  Wire.beginTransmission(I2C_address);

  for(int i=0;i<7;i++)
		Wire.write(TX[i]);

	Wire.endTransmission();
}

void IV3_clock::read_time(void)
{
  uint8_t RX[6];
  uint8_t i;
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(READ_TIME);
	Wire.endTransmission();
  delay(10);

  Wire.requestFrom(I2C_address, 6);
  while(Wire.available())
  {
    RX[i] = Wire.read();
    i++;
  }

  time.year = RX[0];
  time.month = RX[1];
  time.day  = RX[2];
  time.hour = RX[3];
  time.minute = RX[4];
  time.second = RX[5];
}

void IV3_clock::clock_mode(void)
{
  Wire.begin();
  Wire.beginTransmission(I2C_address);
  Wire.write(CLOCK_MODE);
  Wire.endTransmission();
}

void IV3_clock::user_display(uint8_t *data)
{
  uint8_t TX[5];
  uint8_t i;

  TX[0] = USER_DISPLAY;
  for(i=0;i<4;i++)
    TX[i+1] = data[i];
  Wire.begin();
  Wire.beginTransmission(I2C_address);
  for(i=0;i<5;i++)
		Wire.write(TX[i]);
  Wire.endTransmission();
}

void IV3_clock::set_hour_mode(bool mode)
{
  uint8_t TX[2];

  TX[0] = HOUR_MODE;
  if(mode == true)
    TX[1] = 1;
  else
    TX[1] = 0;
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(TX[0]);
  Wire.write(TX[1]);
  Wire.endTransmission();
}

void IV3_clock::set_brightness(uint8_t brightness)
{
  uint8_t TX[2];

  brightness;

  TX[0] = SET_BRIGHTNESS;
  TX[1] = brightness;
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(TX[0]);
  Wire.write(TX[1]);
  Wire.endTransmission();
}

void IV3_clock::set_night_fade(bool mode)
{
  uint8_t TX[2];

  TX[0] = NIGHT_FADE;
  if(mode == true)
    TX[1] = 1;
  else
    TX[1] = 0;
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(TX[0]);
  Wire.write(TX[1]);
  Wire.endTransmission();
}

void IV3_clock::reset(void)
{
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(SFT_RST);
  Wire.endTransmission();
}

void IV3_clock::get_status(void)
{
  Wire.begin();
  Wire.beginTransmission(I2C_address);
	Wire.write(GET_STATUS);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(I2C_address, 1);
  while(Wire.available())
  {
    IV3_status = Wire.read();
  }
}

bool IV3_clock::get_hour_mode(void)
{
  this->get_status();
  if((IV3_status & 0x80) == 0x80)
    return true;
  else
    return false;
}

bool IV3_clock::get_fade_mode(void)
{
  this->get_status();
  if((IV3_status & 0x40) == 0x40)
    return true;
  else
    return false;
}

uint8_t IV3_clock::get_brightness(void)
{
  this->get_status();
  IV3_status &= 0x1F;
  return IV3_status;
}
