#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <unistd.h> // Includes usleep() [13]

int main(void) {
    alt_u32 raw_button_data;
    alt_u32 inverted_button_data;
    alt_u32 last_button_state = 0;

    printf("Pushbutton LED Control System Ready.\n");
    printf("Hardware Debugging Mode Active.\n");

    while (1) {
        // Step 1: Read the physical state of the active-low buttons
        raw_button_data = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

        // Step 2: Mask to 4 bits and invert because KEYs are active-low (0 when pressed)
        // Inverting maps pressed buttons to logical '1' (High) to light up the LEDs
        inverted_button_data = (~raw_button_data) & 0xF;

        // Step 3: Write inverted button state directly to LED outputs
        IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, inverted_button_data);

        // Step 4: Print only on state changes to avoid flooding JTAG console
        if (inverted_button_data != last_button_state) {
            printf("Keys Pressed: Binary: %c%c%c%c | LED Out: 0x%X\n",
                   (inverted_button_data & 0x8) ? '1' : '0',
                   (inverted_button_data & 0x4) ? '1' : '0',
                   (inverted_button_data & 0x2) ? '1' : '0',
                   (inverted_button_data & 0x1) ? '1' : '0',
                   (unsigned int)inverted_button_data);

            last_button_state = inverted_button_data;
        }

        // Step 5: Software Debouncing Delay
        // Blocks execution for 20ms to allow mechanical switch vibrations to settle
        usleep(20000);
    }
    return 0;
}
