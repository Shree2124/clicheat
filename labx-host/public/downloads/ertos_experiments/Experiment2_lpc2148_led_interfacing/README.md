# Experiment 14: Interfacing of LED with LPC2148 Microcontroller

## Aim
Interfacing of LED with an embedded core (LPC 2148)

## Description
General Purpose I/O pin control on LPC2148: PINSEL, IO0DIR, IO0SET, and IO0CLR for LED blinking and binary ripple counters.

## Theory
The LPC2148 is an ARM7TDMI-S based 32-bit microcontroller with two 32-bit general-purpose I/O ports (Port 0 and Port 1). GPIO pins are controlled by registers: PINSEL (Pin Function Select), IOxDIR (Direction register: 1 for Output, 0 for Input), IOxSET (Set pin high), and IOxCLR (Clear pin low). An LED connected in active-high or active-low configuration is toggled with software delay loops. In this experiment, Port 0 pins (P0.10 - P0.17) drive an 8-LED bar display, demonstrating single-pin blinking, alternating blinking, and binary counter sequences.
