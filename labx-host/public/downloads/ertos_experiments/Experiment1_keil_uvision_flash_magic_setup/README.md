# Experiment 13: Installation and Verification of Keil uVision & Flash Magic Toolchains

## Aim
Installation of Keil uVision IDE and Flash Magic ISP flashing utility, and verifying ARM7 microcontroller project setup.

## Description
ARM7TDMI-S microcontroller toolchain configuration, PLL clocking, and Flash Magic ISP programming verification.

## Theory
Keil uVision is an integrated development environment (IDE) that provides code editing, compilation, simulation, and debugging for ARM-based microcontrollers like the LPC2148. Flash Magic is a dedicated In-System Programming (ISP) tool used to burn compiled Intel HEX binaries into the LPC2148 on-chip flash memory via UART serial interface. The toolchain workflow requires configuring the LPC2148 device database, selecting the ARM target oscillator frequency (12.0 MHz), generating a HEX binary via Armcc / Armclang, and flashing over COM port with ISP handshaking.
