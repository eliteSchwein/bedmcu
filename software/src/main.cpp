#include "Arduino.h"
#include <stdio.h>
#include <hardware/adc.h>
#include "pico/stdlib.h"
const uint led_pin = 4;
const uint tare_pin = 5;
const uint en_pin = 18; // tare input
const uint sensor_pin = 26;
static uint16_t tare_value = 0.0;
bool en_state = false;
void calibrateTare() {

    /*const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    //Serial.printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
    //Serial.printf("voltage: %f V\n", result, result * conversion_factor);
    Serial.println(result);
    if(result > tare_value) {
        tare_value = result;
    }
    tare_counter++;
    */
    tare_value = 0.0;
    for(int i = 0; i<1000; i++){
        uint16_t result = adc_read();

        if(result > tare_value){
            tare_value = result;
        }
    }
    tare_value = tare_value +10;
    Serial.println(tare_value);
}
void setup() {
    Serial.begin(115200);
    //while (!Serial);
    Serial.println("started");
    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_init(tare_pin);
    gpio_set_dir(tare_pin, GPIO_IN);
    gpio_init(en_pin);
    gpio_set_dir(en_pin, GPIO_OUT);
    adc_init();

    adc_gpio_init(sensor_pin);

    adc_select_input(0);
    delay(1000);
    calibrateTare();
}
void loop() {
    uint16_t result = adc_read();
    //bool test = gpio_get(en_pin);
    bool test = false;
    if(test){
        if(!en_state){
            calibrateTare();
            en_state = true;
            delay(100);
        }
    }else en_state = false;
    //Serial.println(result);
    if(result > tare_value){
        gpio_put(led_pin, true);
        gpio_put(en_pin, true);
    }else{
        gpio_put(led_pin, false);
        gpio_put(en_pin, false);
    }

    //const float conversion_factor = 3.3f / (1 << 12);
    //uint16_t result = adc_read();
    // Serial.printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
}
void setup1() {
}
void loop1() {
    /*if(tare_counter != tare_counter_limit) {
        return;
    }*/
}