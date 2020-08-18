import math
import board
import busio
import time
from digitalio import DigitalInOut, Direction, Pull

class IV3:
    def __init__(self):
        print("Init IV3")
        self.i2c = busio.I2C(board.SCL, board.SDA)
        self.I2C_Address = 0x16
        self.SET_TIME = 0
        self.READ_TIME = 1
        self.CLOCK_MODE = 2
        self.USER_DISPLAY = 3
        self.HOUR_MODE = 4
        self.SET_BRIGHTNESS = 5
        self.NIGHT_FADE = 6
        self.GET_STATUS = 7
        self.SFT_RST = 255

        self.IV3_status = 0

        self.time = {
            "year": 2020,
            "month": 6,
            "day": 28,
            "hour": 16,
            "minute": 41,
            "second": 30
        }

    def _I2C_write(self, data):
        self.i2c.unlock()
        while not self.i2c.try_lock():
            pass
        var = bytearray(data)
        self.i2c.writeto(self.I2C_Address, var)
        self.i2c.unlock()

    def _I2C_read(self, data):
        self.i2c.unlock()
        while not self.i2c.try_lock():
            pass
        self.i2c.readfrom_into(self.I2C_Address, data) ## Read data
        self.i2c.unlock()


    # User methods
    def set_time(self):
        cmd = [self.SET_TIME]
        cmd.append(self.time["year"])
        cmd.append(self.time["month"])
        cmd.append(self.time["day"])
        cmd.append(self.time["hour"])
        cmd.append(self.time["minute"])
        cmd.append(self.time["second"])

        # Write the time to the clock
        self._I2C_write(cmd)

    def read_time(self):
        cmd = [self.READ_TIME]

        self._I2C_write(cmd)

        rx = bytearray(6)
        self._I2C_read(rx)
        
        self.time["year"] = rx[0]
        self.time["month"] = rx[1]
        self.time["day"] = rx[2]
        self.time["hour"] = rx[3]
        self.time["minute"] = rx[4]
        self.time["second"] = rx[5]

    def clock_mode(self):
        self._I2C_write(CLOCK_MODE)

    def user_display(self, data):
        cmd = [self.USER_DISPLAY]

        for i in range(4):
            cmd.append(data[i])
        
        self._I2C_write(cmd)

    def set_hour_mode(self, mode):
        cmd = [self.HOUR_MODE]

        if mode == True:
            cmd.append(1)
        else:
            cmd.append(0)

        self._I2C_write(cmd)

    def set_brightness(self, brightness):
        cmd = [self.SET_BRIGHTNESS]

        if brightness > 20:
            brightness = 20
        elif brightness <= 0:
            brightness = 1

        cmd.append(brightness)

        self._I2C_write(cmd)

    def set_night_fade(self, mode):
        cmd = [self.NIGHT_FADE]

        if mode == True:
            cmd.append(1)
        else:
            cmd.append(0)

        self._I2C_write(cmd)

    def reset(self):
        _I2C_write(self.SFT_RST)

    def get_status(self):
        cmd = [self.GET_STATUS]
        rx = bytearray(1)

        self._I2C_write(cmd)
        self._I2C_read(rx)
        self.IV3_status = rx[0]


    def get_hour_mode(self):   
        
        self.get_status()
        if (self.IV3_status & 0x80) == 0x80:
            return True
        else:
            return False

    def get_fade_mode(self):
        self.get_status()

        if (self.IV3_status & 0x40) == 0x40:
            return True
        else:
            return False

    def get_brightness(self):
        self.get_status()
        return (self.IV3_status & 0x1F)


class numberWang:
    def __init__(self):
        self.switcheroo = {
            1: 0x06,
            2: 0x5B,
            3: 0x4F,
            4: 0x66,
            5: 0x6D,
            6: 0x7D,
            7: 0x07,
            8: 0x7F,
            9: 0x6F,
            0: 0x3F
        }

    def Wanger(self, x):
        wang = [self.switcheroo[math.floor(x / 1000)]]
        wang.append(self.switcheroo[math.floor((x/100)%10)])
        wang.append(self.switcheroo[math.floor((x/10)%10)])
        wang.append(self.switcheroo[math.floor(x % 10)])
        return wang

       