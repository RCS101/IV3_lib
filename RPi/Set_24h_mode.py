from IV3 import IV3

ivClock = IV3()

# Read the 24h mode status from the clock
mode = ivClock.get_hour_mode()
print(mode)

# Change the mode to the opposite
if mode == True:
    ivClock.set_hour_mode(False)
else:
    ivClock.set_hour_mode(True)
