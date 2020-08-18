import math
import smbus

class IV3:
    def __init__(self):
        print("Init IV3")
        self.channel = 1
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
            "minute": 22,
            "second": 30
        }
        
        # Initialise I2C
        self.bus = smbus.SMBus(self.channel)

    def _I2C_write(self, data):
        cmd = data.pop(0)    
        self.bus.write_i2c_block_data(self.I2C_Address, cmd, data)       
        
    def _I2C_read(self, reg, num):
        return self.bus.read_i2c_block_data(self.I2C_Address, reg, num)

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
        rx = self._I2C_read(self.READ_TIME, 6)
        
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
        rx = self._I2C_read(self.GET_STATUS, 1)
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

       
