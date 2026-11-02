# Experiment 17: Power Management & Low-Power Modes in LPC2148

## Aim
To implement power management techniques in the LPC2148 embedded controller by configuring its power saving modes to reduce power consumption.

## Description
LPC2148 power saving techniques configuring PCON register Idle Mode with external interrupt (EINT0) wake-up.

## Theory
To implement power management techniques in the LPC2148 embedded controller by configuring its power-saving modes to reduce power consumption. Power management in the LPC2148 is controlled via the PCON (Power Control) and PCONP (Power Control for Peripherals) registers. LPC2148 supports Idle Mode (PCON=0x01) where the CPU clock stops while peripherals continue running, and Power Down Mode (PCON=0x02) where both CPU and oscillator are halted. An external interrupt (EINT0 on P0.16) is configured via the Vectored Interrupt Controller (VIC) to wake the microcontroller from low-power state, toggle a status LED, and resume operation.
