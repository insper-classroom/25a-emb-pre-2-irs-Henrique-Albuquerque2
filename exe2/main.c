#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int LED_PIN  = 4;
int BTN_PIN  = 28;

volatile int g_status = 0;

void gpio_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {         // fall edge
        g_status = 1;
    } 
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);
  gpio_set_irq_enabled_with_callback(BTN_PIN, 
                                     GPIO_IRQ_EDGE_FALL, 
                                     true,
                                     &gpio_callback);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  int led_status = 0;
  while (true) {
    if (g_status){
      g_status = 0; // clean IRS flag
      led_status = !led_status;
      gpio_put(LED_PIN, led_status);
    }
  }
}