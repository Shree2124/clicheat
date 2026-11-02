# Experiment 15: Interfacing 16x2 Alphanumeric LCD with LPC2148

## Aim
Interfacing of LCD with an embedded core (LPC 2148)

## Description
8-bit HD44780 LCD driver interfacing with LPC2148: command latching, data transmission, and string rendering.

## Theory
A 16x2 alphanumeric LCD display interfaces with the LPC2148 using 8 data lines (D0-D7) and 3 control lines: RS (Register Select - 0 for command, 1 for data), RW (Read/Write - grounded for write), and EN (Enable - high-to-low pulse to latch data). Commands initialize display mode (0x38 for 8-bit, 2-line mode), display ON cursor OFF (0x0C), clear screen (0x01), and set DDRAM address (0x80 line 1, 0xC0 line 2). The LPC2148 drives the LCD by asserting RS, placing data on Port 0, and pulsing EN with sufficient setup and hold time.
