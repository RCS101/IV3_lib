import board
import digitalio
import time
import busio
from IV3 import IV3

led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

ivClock = IV3()

# Read the 24h mode status from the clock
mode = ivClock.get_hour_mode()
print(mode)

# Change the mode to the opposite
if mode == True:
    ivClock.set_hour_mode(False)
else:
    ivClock.set_hour_mode(True)
        
while True:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)