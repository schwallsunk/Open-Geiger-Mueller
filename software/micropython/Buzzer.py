__author__ = "Saioul Ngoun and Axel Monney"
__copyright__ = "Copyright 2025, NS-ECMF Open Geiger Mueller project"
__license__ = "GPL"
__version__ = "1.0.0"
__status__ = "Production"


from machine import Pin,PWM
from utime import sleep


total = 0 


pin = Pin("LED", Pin.OUT)
pin_B = Pin(14,Pin.OUT)
pin_G = Pin(15,Pin.OUT)
pin_R = Pin(13,Pin.OUT)

switch_1 = Pin(4, Pin.IN, Pin.PULL_UP)
switch_2 = Pin(5, Pin.IN, Pin.PULL_UP)
switch_3 = Pin(6, Pin.IN, Pin.PULL_UP)
switch_4 = Pin(7, Pin.IN, Pin.PULL_UP)

buzzer = Pin(21,Pin.OUT)

hv_tube_plus = Pin(16, Pin.OUT)
hv_tube_neg = Pin(22, Pin.IN)

pwm_hv_plus=PWM(hv_tube_plus)


pin_B.high()
pin_G.high()
pin_R.high()

pwm_hv_plus.freq(6000)
print("HV gets turned on")
pwm_hv_plus.duty_u16(55000)

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
            print(total)
            #pwm_buzz.duty_u16(30000)
        if not switch_3.value():
            #pwm_buzz.duty_u16(0)
            print("button 3")
        if not switch_4.value():
            pwm_hv_plus.duty_u16(0)
            print("HV is off") 
        if not hv_tube_neg.value():
            buzzer.toggle()
            pin_R.toggle()
    except KeyboardInterrupt:
        break
print("Finished.")

