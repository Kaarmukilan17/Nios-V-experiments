#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include <unistd.h> // For usleep()

// Alphanumeric active-low segment patterns
#define CHAR_H     0x09
#define CHAR_E     0x06
#define CHAR_L     0x47
#define CHAR_P     0x0C
#define CHAR_BLANK 0x7F

// Define the 8 states of our scrolling text marquee sequence
// This sequence scrolls "HELP" from right to left, blanks the screen, and repeats.
const alt_u8 marquee_states[8][4] = {
    // HEX3        HEX2        HEX1        HEX0
    {CHAR_BLANK, CHAR_BLANK, CHAR_BLANK, CHAR_H},     // State 0: "   H"
    {CHAR_BLANK, CHAR_BLANK, CHAR_H,     CHAR_E},     // State 1: "  HE"
    {CHAR_BLANK, CHAR_H,     CHAR_E,     CHAR_L},     // State 2: " HEL"
    {CHAR_H,     CHAR_E,     CHAR_L,     CHAR_P},     // State 3: "HELP" (All displays active!)
    {CHAR_E,     CHAR_L,     CHAR_P,     CHAR_BLANK}, // State 4: "ELP "
    {CHAR_L,     CHAR_P,     CHAR_BLANK, CHAR_BLANK}, // State 5: "LP  "
    {CHAR_P,     CHAR_BLANK, CHAR_BLANK, CHAR_BLANK}, // State 6: "P   "
    {CHAR_BLANK, CHAR_BLANK, CHAR_BLANK, CHAR_BLANK}  // State 7: "    "
};

// Console representation string for debugging verification
const char* state_strings[8] = {
    "[   ] [   ] [   ] [ H ]",
    "[   ] [   ] [ H ] [ E ]",
    "[   ] [ H ] [ E ] [ L ]",
    "[ H ] [ E ] [ L ] [ P ]",
    "[ E ] [ L ] [ P ] [   ]",
    "[ L ] [ P ] [   ] [   ]",
    "[ P ] [   ] [   ] [   ]",
    "[   ] [   ] [   ] [   ]"
};

int main(void) {
    int state = 0;

    printf("--- Experiment 4: Multi-Display Sequential Character Control ---\n");
    printf("Automated Text Scrolling Sequence Initialized...\n\n");

    while (1) {
        // 1. Output the character pattern to the corresponding register base address
        IOWR_ALTERA_AVALON_PIO_DATA(HEX3_PIO_BASE, marquee_states[state][0]);
        IOWR_ALTERA_AVALON_PIO_DATA(HEX2_PIO_BASE, marquee_states[state][1]);
        IOWR_ALTERA_AVALON_PIO_DATA(HEX1_PIO_BASE, marquee_states[state][2]);
        IOWR_ALTERA_AVALON_PIO_DATA(HEX0_PIO_BASE, marquee_states[state][3]);

        // 2. Print display configuration output to the JTAG UART console
        printf("Display Status: %s (State %d)\n", state_strings[state], state);

        // 3. Move to the next marquee frame state
        state = (state + 1) % 8; // Reset back to state 0 after state 7

        // 4. Delay for 500,000 microseconds (0.5 seconds) before advancing frames
        // This is the clock cycle transition rate of the display sequence
        usleep(500000);
    }
    return 0;
}
