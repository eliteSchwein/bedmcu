#include "pico/stdlib.h"
#include "pico/binary_info.h"

int main() {

    const uint led_pin = 18;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Loop forever
    while (true) {
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
}