#include "Arduino.h"
#include <stdio.h>
#include <hardware/adc.h>
#include "pico/stdlib.h"

const uint led_pin = 18;
const uint tare_pin = 5;
const uint en_pin = 4; // reserved for something
const uint sensor_pin = 26;

const int tare_counter_limit = 2048;
static int tare_counter = 0;
static uint16_t tare_value = 0.0;

bool calibrateTare() {
    if(tare_counter == tare_counter_limit) {
        return false;
    }

    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    Serial.printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
    Serial.println(result);

    if(result > tare_value) {
        tare_value = result;
    }

    tare_counter++;

    return true;
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("started");

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    gpio_put(led_pin, true);

    adc_init();
    adc_gpio_init(sensor_pin);
    adc_select_input(0);

    //gpio_put(led_pin, true);
}

void loop() {
    bool isCalibrating = calibrateTare();
    Serial.println(isCalibrating);

    if(isCalibrating) {
        delay(100);
        return;
    }
    //const float conversion_factor = 3.3f / (1 << 12);
    //uint16_t result = adc_read();
   // Serial.printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
}

void setup1() {

}

void loop1() {
    if(tare_counter != tare_counter_limit) {
        return;
    }
}