/*
 * Experiment 14: Interfacing of LED with Embedded Core (LPC 2148)
 * Demonstrates Port 0 GPIO Pin Configuration, Set, Clear, and Patterns
 */

#include <LPC214x.h>

#include 

void Delay(void)
{
    unsigned int i, j;

    for (i = 0; i < 500; i++)
    {
        for (j = 0; j < 500; j++);
    }
}

int main(void)
{
    // Select GPIO function for P0.10
    PINSEL0 &= ~(3U << 20);

    // Configure P0.10 as output
    IO0DIR |= (1U << 10);

    while (1)
    {
        // Turn LED ON
        IO0SET = (1U << 10);
        Delay();

        // Turn LED OFF
        IO0CLR = (1U << 10);
        Delay();
    }
}

/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
The LPC2148 is an ARM7TDMI-S based 32-bit microcontroller with two 32-bit
general-purpose I/O ports (Port 0 and Port 1). GPIO pins are controlled by
registers: PINSEL (Pin Function Select), IOxDIR (Direction register: 1 for
Output, 0 for Input), IOxSET (Set pin high), and IOxCLR (Clear pin low).
An LED connected in active-high or active-low configuration is toggled
with software delay loops. In this experiment, Port 0 pins (P0.10 - P0.17)
drive an 8-LED bar display, demonstrating single-pin blinking, alternating
blinking, and binary counter sequences.
============================================================================
*/
