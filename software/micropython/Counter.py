__author__ = "Saioul Ngoun and Axel Monney"
__copyright__ = "Copyright 2025, NS-ECMF Open Geiger Mueller project"
__license__ = "GPL"
__version__ = "1.0.0"
__status__ = "Production"



from machine import Pin,PWM,Timer
from utime import sleep
import micropython

micropython.alloc_emergency_exception_buf(100)
PERIOD_OF_COUNTER = 500

# Setup of counter values and arrays

total = 0 

floating_avg_arr = [0,0,0,0,0,0,0,0,0,0]

# General setup of I/O pins in which direction which pins operate

pin = Pin("LED", Pin.OUT)
pin_R = Pin(13,Pin.OUT)
pin_G = Pin(15,Pin.OUT)
pin_B = Pin(14,Pin.OUT)

# Ensure initial state of RGB LED pins
pin_B.high() 
pin_G.high()
pin_R.high()




switch_1 = Pin(4, Pin.IN, Pin.PULL_UP)
switch_2 = Pin(5, Pin.IN, Pin.PULL_UP)
switch_3 = Pin(6, Pin.IN, Pin.PULL_UP)
switch_4 = Pin(7, Pin.IN, Pin.PULL_UP)

buzzer = Pin(21,Pin.OUT)

hv_tube_plus = Pin(16, Pin.OUT) # PWM of switching HV transformer transistor
hv_tube_neg = Pin(22, Pin.IN) # Output that falls low if ionization is detected


# Setup of HV switching PSU timing
pwm_hv_plus=PWM(hv_tube_plus)   # Setup of PWM pin for the HV transformer to ensure the HV supply of the tube
pwm_hv_plus.freq(6000) # frequency of PWM signal
print("HV gets turned on")
pwm_hv_plus.duty_u16(55705) # Duty cycle of PWM signal


# Interrupt function for counting ionizations in tube
def handle_interrupt(Pin):
    global total
    total = total+1
    buzzer.toggle()

def handle_counter(Pin):
    global total
    global floating_avg_arr
    floating_avg_arr.pop(0)
    floating_avg_arr.append(total)
    total = 0

tim = Timer(-1,period=PERIOD_OF_COUNTER, mode=Timer.PERIODIC, callback=handle_counter)
tim.init(period=PERIOD_OF_COUNTER, mode=Timer.PERIODIC, callback=handle_counter)
# Interrupt handle setup for ionization
irq_ionization = hv_tube_neg.irq(trigger=Pin.IRQ_FALLING, handler=handle_interrupt)



def count():
    global floating_avg_arr
    total_counts = sum(floating_avg_arr)
    counts_per_second = total_counts/(len(floating_avg_arr)*PERIOD_OF_COUNTER/1000)
    return counts_per_second

    #pwm.deinit()

while True:
    try:
        if not switch_1.value():
            print("button is pressed")
            pin_B.toggle()
            sleep(0.2) # sleep 1sec
            pin_G.toggle()
            sleep(0.2)
            pin_R.toggle()
            print("Done with my light spiel")
        if not switch_2.value():
            print("Button 2")
            cps=count()
            print(total)
            print("Total CPS is:")
            print(cps)
            #pwm_buzz.duty_u16(30000)
        if not switch_3.value():
            #pwm_buzz.duty_u16(0)
            print("button 3")
        if not switch_4.value():
            pwm_hv_plus.duty_u16(0)
            print("HV is off") 
    except KeyboardInterrupt:
        break
print("Finished.")

