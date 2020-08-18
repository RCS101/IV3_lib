import board
import digitalio
import time
import busio
from IV3 import IV3

led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

ivClock = IV3()
        
while True:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)

    # Read the time from the clock
    ivClock.read_time()

    print(ivClock.time["hour"], ivClock.time["minute"], ivClock.time["second"], " " ,ivClock.time["day"], ivClock.time["month"], ivClock.time["year"])
