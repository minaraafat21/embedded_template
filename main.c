#include "RCC.h"
#include "MyGpio.h"

#define BIN 3

const uint8 sev_seg_numbers[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void delay_ms(int ms) {
    for (int i = 0; i < (ms * 1200); i++) {}}

void display_number(uint8 number) {
    for (uint8 i = 0; i < 7; i++) {
        Gpio_WritePin(GPIO_B, i, (sev_seg_numbers[number] >> i) & 0x01);
    }
}

void clear_display() {
    for (uint8 i = 0; i < 7; i++) {
        Gpio_WritePin(GPIO_B, i, LOW);
    }
    Gpio_WritePin(GPIO_B, 8, HIGH); 
    Gpio_WritePin(GPIO_B, 9, HIGH);  
}

int main() {
    uint8 counter = 10; // counter from 10 to 50
    Rcc_Init();
    Rcc_Enable(RCC_GPIOB);

    for (uint8 i = 0; i < 10; i++) {
        Gpio_Init(GPIO_B, i, GPIO_OUTPUT, GPIO_PUSH_PULL);
    }

    while (1) {

        for (int i = 0; i < 50; i++) { // 50 x 20 ms
            clear_display();
            Gpio_WritePin(GPIO_B, 9, HIGH);
            Gpio_WritePin(GPIO_B, 8, LOW);
            display_number(counter / 10);
            delay_ms(10);

            clear_display();
            Gpio_WritePin(GPIO_B, 9, LOW);
            Gpio_WritePin(GPIO_B, 8, HIGH);
            display_number(counter % 10);
            delay_ms(10);
        }

        counter++;
        if (counter >= 50) {
            counter = 10;

        }
    }

    return 0;
}
