//#include <stdio.h>
//#include "system.h"
//#include "altera_avalon_pio_regs.h"
//#include <unistd.h> // for usleep
//
//int main(void) {
//    alt_u32 count = 0;
//
//    printf("LED Binary Counter System Initialized.\n");
//
//    while (1) {
//        // Write the current 4-bit count to the physical LEDs
//        IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, count);
//
//        // Print the current value to the JTAG UART console
//        printf("LED State: 0x%X (Binary: %c%c%c%c)\n",
//               (unsigned int)count,
//               (count & 0x8) ? '1' : '0',
//               (count & 0x4) ? '1' : '0',
//               (count & 0x2) ? '1' : '0',
//               (count & 0x1) ? '1' : '0');
//
//        // Increment count and mask it to 4 bits (wraps from 15 back to 0)
//        count = (count + 1) & 0xF; // 0xF is 1111 in binary
//
//        // Delay for 500,000 microseconds (0.5 seconds)
//        // You can increase or decrease this to change the blinking speed
//        usleep(500000);
//    }
//    return 0;
//}


//------------------- SWITCH TO LED - NO UART...

//#include "system.h"
//#include "altera_avalon_pio_regs.h"
//#include <unistd.h> // for usleep
//
//int main(void) {
//    alt_u32 switch_data;
//
//    while (1) {
//        // Read the physical state of the switches (bypassing data cache)
//        switch_data = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_PIO_BASE);
//
//        // Write that state directly to drive the board LEDs
//        IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, switch_data);
//
//        // Add a small delay to prevent excessive CPU polling (e.g., 50ms)
//        usleep(50000);
//    }
//    return 0;
//}
//---- LED SWITCH UART-------

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <unistd.h> // for usleep

int main(void) {
    alt_u32 switch_data;
    // Initialize with an impossible value to force an initial change print
    alt_u32 last_switch_data = 0xFFFFFFFF;
    printf("Switch & LED Control System Initialized.\n");
    while (1) {
        // Read the physical state of the switches (bypassing data cache)
        switch_data = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_PIO_BASE);
        // Write that state directly to drive the board LEDs
        IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, switch_data);
        // Check if the switches have changed since the last poll
        if (switch_data != last_switch_data) {
            // Print the status update to stdout (the active UART)
            printf("Switch State Changed: 0x%X\n", (unsigned int)switch_data);
            // Keep track of the current state
            last_switch_data = switch_data;
        }// Add a small delay to prevent excessive CPU polling (e.g., 50ms)
        usleep(50000);
    }
    return 0;
}



