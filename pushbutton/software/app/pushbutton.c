#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include <unistd.h> // For usleep()

int main(void) {
    alt_u32 raw_button_data;
    alt_u32 inverted_button_data;
    alt_u32 last_button_state = 0xFFFFFFFF; // Force print on first loop

    printf("3-Bit Pushbutton & LED Control Initialized.\n");
    printf("Please press KEY1, KEY2, or KEY3 (KEY0 is System Reset).\n");

    while (1) {
        // 1. Read physical buttons (3-bits wide)
        raw_button_data = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

        // 2. Invert and mask to 3 bits (binary 111 = 0x7)
        // Active-low: 0 when pressed, 1 when unpressed.
        // Inverting turns pressed buttons into logical '1's.
        inverted_button_data = (~raw_button_data) & 0x7;

        // 3. Write directly to drive LEDR0, LEDR1, LEDR2
        IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, inverted_button_data);

        // 4. Print to JTAG UART console only when state changes
        if (inverted_button_data != last_button_state) {
            printf("Keys Held: Binary: %c%c%c | LED Output: 0x%X\n",
                   (inverted_button_data & 0x4) ? '1' : '0',  // KEY3
                   (inverted_button_data & 0x2) ? '1' : '0',  // KEY2
                   (inverted_button_data & 0x1) ? '1' : '0',  // KEY1
                   (unsigned int)inverted_button_data);

            last_button_state = inverted_button_data;
        }

        // 5. Software debounce delay
        usleep(20000);
    }
    return 0;
}
