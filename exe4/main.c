#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>


const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;

volatile int status = 0;

volatile int status_r = 0;
volatile int status_g = 0;

void btn_callback(uint gpio, uint32_t events) {
  status = 1;
  if (events == 0x4){ 
    if (gpio == BTN_PIN_R){
      status_r = 1;
    }
  }
  if (events == 0x8){
    if (gpio == BTN_PIN_G){
      status_g = 1;
    }
  }
}

int main() {
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  stdio_init_all();
  int led_r = 0;
  int led_g = 0;

  while (true) {
    if (status){
      status = 0;
      if (status_r){
        status_r = 0;
        led_r = !led_r;
        gpio_put(LED_PIN_R, led_r);
      }
      if (status_g){
        status_g = 0;
        led_g = !led_g;
        gpio_put(LED_PIN_G, led_g);
      }
    }
  }
}
