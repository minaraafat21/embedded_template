#include "RCC.h"
#include "MyGpio.h"

#define BTN_PIN         3
#define LED_R     11
#define LED_G   13
#define LED_B    15

void delay_ms(int ms) {
    for (int i = 0; i < ms * 1200; i++);
}

int main() {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOC);

    // btn
    Gpio_Init(GPIO_A, BTN_PIN, GPIO_INPUT, GPIO_PULL_UP);

    // Led pins
    Gpio_Init(GPIO_C, LED_R, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(GPIO_C, LED_G, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(GPIO_C, LED_B, GPIO_OUTPUT, GPIO_PUSH_PULL);

    unsigned char led_state = 0; // Tracks the current LED color state
    unsigned char button_stable = 1; // Tracks if the button is stable

    while (1) {
        // Debouncing
        unsigned char button_state_1 = Gpio_ReadPin(GPIO_A, BTN_PIN);
        delay_ms(30);
        unsigned char button_state_2 = Gpio_ReadPin(GPIO_A, BTN_PIN);

        if (button_state_1 == button_state_2) {
            if (button_state_1 == 0 && button_stable) { // Falling edge
                button_stable = 0; // unstable

                // Cycle through LED colors
                led_state = (led_state + 1) % 8;

                // Update LED output
                Gpio_WritePin(GPIO_C, LED_R, (led_state & 0x1) ? HIGH : LOW);
                Gpio_WritePin(GPIO_C, LED_G, (led_state & 0x2) ? HIGH : LOW);
                Gpio_WritePin(GPIO_C, LED_B, (led_state & 0x4) ? HIGH : LOW);
            } else if (button_state_1 == 1) {
                button_stable = 1; // stable
            }
        }

        delay_ms(10); // Small delay for stability
    }

    return 0;
}