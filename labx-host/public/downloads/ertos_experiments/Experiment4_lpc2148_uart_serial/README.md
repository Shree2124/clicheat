# Experiment 16: Serial Communication using UART0 on LPC2148

## Aim
Serial communication between controller boards or any other device (UART on LPC 2148)

## Description
Full-duplex asynchronous serial transceiver configuration on LPC2148: baud rate generation, FIFOs, and character echo.

## Theory
LPC2148 features two asynchronous serial ports (UART0 and UART1). UART communication requires setting the baud rate generator using U0LCR (Line Control Register, DLAB=1), U0DLL, and U0DLM divider latches based on PCLK (Peripheral Clock). Data transmission occurs by polling the Transmit Holding Register Empty (THRE) flag in U0LSR and writing bytes to U0THR. Data reception polls the Receiver Data Ready (RDR) flag and reads from U0RBR. Setting word length to 8 bits, 1 stop bit, and no parity establishes standard 9600-8-N-1 serial framing.
