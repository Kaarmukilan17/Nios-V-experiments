#include <stdio.h>
#include "system.h"
#include "alt_types.h"                 // Standard Altera data types [18]
#include "altera_avalon_pio_regs.h"    // Register access macros (IORD/IOWR)
#include <unistd.h>                    // Includes usleep() [19]

// Active-low decoding table (Segments: Bit 6=G, 5=F, 4=E, 3=D, 2=C, 1=B, 0=A)
const alt_u8 hex_decode[20] = {
    0x40, // '0' -> Binary 0100 0000 (Segment G is off, all others on)
    0x79, // '1' -> Binary 0111 1001 (Segments B and C are on, all others off)
    0x24, // '2' -> Binary 0010 0100
    0x30, // '3' -> Binary 0011 0000
    0x19, // '4' -> Binary 0001 1001
    0x12, // '5' -> Binary 0001 0010
    0x02, // '6' -> Binary 0000 0010
    0x78, // '7' -> Binary 0111 1000
    0x00, // '8' -> Binary 0000 0000 (All segments turned on)
    0x10, // '9' -> Binary 0001 0000
    0x08, // 'A' -> Binary 0000 1000
    0x03, // 'b' -> Binary 0000 0011
    0x46, // 'C' -> Binary 0100 0110
    0x21, // 'd' -> Binary 0010 0001
    0x06, // 'E' -> Binary 0000 0110
    0x0E  // 'F' -> Binary 0000 1110
};

int main(void) {
    alt_u32 switch_raw_data;
    alt_u32 processed_nibble;
    alt_u32 last_switch_state = 0xFFFFFFFF; // Set out-of-range to force initial print

    printf("--- Experiment 3: Seven-Segment Interface Control System ---\n");
    printf("Adjust SW0 - SW3 to control the HEX0 Display.\n\n");

    while (1) {
        // 1. Read the physical state of the slide switches
        switch_raw_data = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_PIO_BASE);

        // 2. Extract and mask to the lowest 4 bits (SW3 to SW0)
        processed_nibble = switch_raw_data & 0xF;

        // 3. Write the decoded active-low byte directly to the HEX0 display register
        IOWR_ALTERA_AVALON_PIO_DATA(HEX0_PIO_BASE, hex_decode[processed_nibble]);

        // 4. Update the JTAG UART console only on changes (prevents flooding)
        if (processed_nibble != last_switch_state) {
            printf("[STATUS UPDATE] Switches: Binary %c%c%c%c (Decimal %d) -> HEX0 Display: '%X'\n",
                   (processed_nibble & 0x8) ? '1' : '0',  // SW3
                   (processed_nibble & 0x4) ? '1' : '0',  // SW2
                   (processed_nibble & 0x2) ? '1' : '0',  // SW1
                   (processed_nibble & 0x1) ? '1' : '0',  // SW0
                   (int)processed_nibble,
                   (unsigned int)processed_nibble);

            last_switch_state = processed_nibble;
        }

        // 5. Short software loop delay (20ms) to throttle CPU loading
        usleep(20000);
    }
    return 0;
}
