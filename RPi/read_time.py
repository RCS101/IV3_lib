from IV3 import IV3

ivClock = IV3()
        
# Read the time from the clock
ivClock.read_time()

print('The time is: ', ivClock.time["hour"], ivClock.time["minute"], ivClock.time["second"], ivClock.time["day"], ivClock.time["month"], ivClock.time["year"])
