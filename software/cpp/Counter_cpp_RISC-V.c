// __author__ = "Saioul Ngoun and Axel Monney"
// __copyright__ = "Copyright 2025, Open Geiger Mueller project"
// __license__ = "GPL"
// __version__ = "1.0.0"
// __status__ = "Production"




#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

const uint16_t PERIOD_INTEGRATION_COUNTS = 1000U;  // Interrupt period in ms within which the counts are being averaged for
const uint8_t HV_TUBE_INT_PIN = 22U; // Geiger tube interrupt for ionization counting
const uint8_t HV_TUBE_PSU_PIN = 16U; // HV tube high voltage (HV) switching power supply stimulus pin
const uint8_t BUZZER_PIN = 21U; // Pin on which Piezo buzzer is hooked up to
const uint8_t LED_R_PIN = 13U; // Pin for the red color of the RGB LED
const uint8_t LED_G_PIN = 14U; // Pin for the green color of the RGB LED
const uint8_t LED_B_PIN = 15U; // Pin for the blue color of the RGB LED
const uint8_t SWITCH_1_PIN = 4U; // Pin for the switch 1 labelled SW1 on PCB
const uint8_t SWITCH_2_PIN = 5U; // Pin for the switch 2 labelled SW2 on PCB 
const uint8_t SWITCH_3_PIN = 6U; // Pin for the switch 3 labelled SW3 on PCB
const uint8_t SWITCH_4_PIN = 7U; // Pin for the switch 4 labelled SW4 on PCB 

uint16_t counts_array_moving_avg[10]; // Moving window array for averaged cps value
volatile uint16_t counter = 0;
volatile bool Buzzer_state = 0;
static repeating_timer_t timer; // struct used for the repeating measurement timer interrupt
volatile bool Flag_thread_lock = false;
volatile uint8_t counter_location = 0;

void counter_callback(){
    irq_set_enabled(IO_IRQ_BANK0,false);
    counter++;
    Buzzer_state = !Buzzer_state;
    gpio_put(BUZZER_PIN,Buzzer_state);
    irq_set_enabled(IO_IRQ_BANK0,true);
}

void print_measurements(uint16_t *buf,
                const uint size_buf){
  for(uint i=0; i<size_buf;i++){
    printf("%u,",*(buf+i));
    }
  printf("\n");
}

void print_bequerel(uint16_t *buf,
                const uint size_buf){
    uint32_t total_count = 0;
    double total_activity = 0.;
    for(uint i=0; i<size_buf;i++){
    total_count=*(buf+i)+total_count;
    }
    total_activity = total_count/(size_buf*(PERIOD_INTEGRATION_COUNTS/1000));
    printf("The total acitvity in of the sample is %e Bq",total_activity);
    printf("\n");
    printf("The total amount of decays in of the sample over the last 10 seconds are %u decays",total_count);
    printf("\n");
    }

bool alarm_callback(repeating_timer_t *t) {
    if (counter_location < 10){
        counter_location++;
        counts_array_moving_avg[counter_location] = counter;
    }
    else{
        counts_array_moving_avg[0] = counter;
        counter_location = 0;
    }
    counter = 0;
    return true;
}

int main()
{
    stdio_init_all();

    // Setup of all GPIOs
    gpio_set_irq_callback(&counter_callback);
    gpio_set_irq_enabled(HV_TUBE_INT_PIN, GPIO_IRQ_EDGE_FALL, true);
    gpio_init(BUZZER_PIN); gpio_set_dir(BUZZER_PIN, GPIO_OUT);gpio_put(BUZZER_PIN,1);
    gpio_set_function(HV_TUBE_PSU_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(HV_TUBE_PSU_PIN); // find out to which slice Pin16 is connected to => should be slice 0
    pwm_set_wrap(slice_num, 25000); // Setting period lenght in clock cycles here for cpu clocked at 150MHz
    pwm_set_chan_level(slice_num, 0, 21500); // When to break circuit 
    pwm_set_enabled(slice_num, true);
    printf("HV is on!\n");
    gpio_init(LED_R_PIN); gpio_set_dir(LED_R_PIN, GPIO_OUT);gpio_put(LED_R_PIN,0);
    gpio_init(LED_G_PIN); gpio_set_dir(LED_G_PIN, GPIO_OUT);gpio_put(LED_G_PIN,0);
    gpio_init(LED_B_PIN); gpio_set_dir(LED_B_PIN, GPIO_OUT);gpio_put(LED_B_PIN,1);
    gpio_init(SWITCH_1_PIN); gpio_set_dir(SWITCH_1_PIN, GPIO_IN);gpio_pull_up(SWITCH_1_PIN);
    gpio_init(SWITCH_2_PIN); gpio_set_dir(SWITCH_2_PIN, GPIO_IN);gpio_pull_up(SWITCH_2_PIN);
    gpio_init(SWITCH_3_PIN); gpio_set_dir(SWITCH_3_PIN, GPIO_IN);gpio_pull_up(SWITCH_3_PIN);
    gpio_init(SWITCH_4_PIN); gpio_set_dir(SWITCH_4_PIN, GPIO_IN);gpio_pull_up(SWITCH_4_PIN);
    gpio_init(HV_TUBE_INT_PIN); gpio_set_dir(HV_TUBE_INT_PIN, GPIO_IN);gpio_pull_up(SWITCH_4_PIN);
    irq_set_enabled(IO_IRQ_BANK0,true);
    add_repeating_timer_ms(PERIOD_INTEGRATION_COUNTS, alarm_callback, NULL, &timer);

    while (true) {
        if(!gpio_get(SWITCH_1_PIN)){
        print_measurements(counts_array_moving_avg,10);
        sleep_ms(1000);
        }
        if(!gpio_get(SWITCH_2_PIN)){
        print_bequerel(counts_array_moving_avg,10);
        sleep_ms(1000);
        }
        tight_loop_contents();
    }
    cancel_repeating_timer (&timer);
}
