#ifndef __IV3__
#define __IV3__

#include <Arduino.h>

#define SET_TIME        0
#define READ_TIME       1
#define CLOCK_MODE      2
#define USER_DISPLAY    3
#define HOUR_MODE       4
#define SET_BRIGHTNESS  5
#define NIGHT_FADE      6
#define GET_STATUS      7
#define SFT_RST         0xFF

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} TIME_STRUCT;

class IV3_clock
{
private:
  uint8_t I2C_address = 0x16;
	uint8_t IV3_status;

	void i2c_trans(uint8_t* data, uint8_t length);

public:
  TIME_STRUCT time;

	// Constructor
	IV3_clock(){};

  void set_time(void);
  void read_time(void);
  void clock_mode(void);
  void user_display(uint8_t *data);
  void set_hour_mode(bool mode);
  void set_brightness(uint8_t brightness);
  void set_night_fade(bool fade);
  void reset(void);
	void get_status(void);
	bool get_hour_mode(void);
	bool get_fade_mode(void);
	uint8_t get_brightness(void);
};



#endif
