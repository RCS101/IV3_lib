import board
import digitalio
import time
import busio
import math
from IV3 import IV3, numberWang

led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

ivClock = IV3()
numbs = numberWang()

cnt = 0

while True:
    led.value = True
    time.sleep(0.01)
    led.value = False
    time.sleep(0.01)

    ivClock.user_display(numbs.Wanger(cnt))
    cnt += 1
    if cnt == 10000:
        cnt = 0
