#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos dos LEDs
const uint LED_RED = 13;   // LED Vermelho
const uint LED_GREEN = 11; // LED Verde
const uint LED_BLUE = 12;  // LED Azul

// Cálculo dos períodos baseados nas frequências desejadas
const uint16_t PERIOD_RED = 125000;   // 1 kHz → 125 MHz / 1kHz
const uint16_t PERIOD_GREEN = 12500;  // 10 kHz → 125 MHz / 10kHz
const uint16_t PERIOD_BLUE = 500;     // Independente, pode ajustar

const float DIVIDER_PWM = 1.0; // Divisor de clock do PWM

// Duty Cycle inicial (5%)
uint16_t led_level_red = PERIOD_RED * 5 / 100;
uint16_t led_level_green = PERIOD_GREEN * 5 / 100;
uint16_t led_level_blue = PERIOD_BLUE * 5 / 100;

// Configuração do PWM
void setup_pwm(uint gpio, uint16_t period) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice, DIVIDER_PWM);
    pwm_set_wrap(slice, period);
    pwm_set_gpio_level(gpio, period * 5 / 100); // Começa com 5%
    pwm_set_enabled(slice, true);
    printf("PWM Configurado - Pino: %d | Slice: %d | Período: %d\n", gpio, slice, period);
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Aguarde inicialização da serial

    // Configura PWM para cada LED
    setup_pwm(LED_RED, PERIOD_RED);
    setup_pwm(LED_GREEN, PERIOD_GREEN);
    setup_pwm(LED_BLUE, PERIOD_BLUE);

    // Exibir os slices no terminal
    printf("Slice RED: %d | Slice GREEN: %d | Slice BLUE: %d\n",
           pwm_gpio_to_slice_num(LED_RED),
           pwm_gpio_to_slice_num(LED_GREEN),
           pwm_gpio_to_slice_num(LED_BLUE));

    uint8_t direction_red = 1;
    uint8_t direction_blue = 1;

    while (true) {
        pwm_set_gpio_level(LED_RED, led_level_red);
        pwm_set_gpio_level(LED_GREEN, led_level_green);
        pwm_set_gpio_level(LED_BLUE, led_level_blue);

        printf("Red: %d / %d | Green: %d / %d | Blue: %d / %d\n",
               led_level_red, PERIOD_RED,
               led_level_green, PERIOD_GREEN,
               led_level_blue, PERIOD_BLUE);

        sleep_ms(2000);

        // Controla o Duty Cycle do LED vermelho
        if (direction_red) {
            led_level_red += PERIOD_RED * 5 / 100;
            if (led_level_red >= PERIOD_RED) {
                direction_red = 0;
            }
        } else {
            led_level_red -= PERIOD_RED * 5 / 100;
            if (led_level_red <= PERIOD_RED * 5 / 100) {
                direction_red = 1;
            }
        }

        // Controla o Duty Cycle do LED azul
        if (direction_blue) {
            led_level_blue += PERIOD_BLUE * 5 / 100;
            if (led_level_blue >= PERIOD_BLUE) {
                direction_blue = 0;
            }
        } else {
            led_level_blue -= PERIOD_BLUE * 5 / 100;
            if (led_level_blue <= PERIOD_BLUE * 5 / 100) {
                direction_blue = 1;
            }
        }
    }

    return 0;
}
