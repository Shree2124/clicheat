/*
 * Experiment 16: Serial Communication between Controller Boards (UART0 on LPC2148)
 * Configures 9600 Baud, 8 Data Bits, 1 Stop Bit, No Parity (9600-8-N-1)
 */

#include <LPC214x.h>

#include 

void UART0_Init(void)
{
    // Configure P0.0 as TXD0 and P0.1 as RXD0
    PINSEL0 |= 0x00000005;

    // Configure UART0
    U0LCR = 0x83;       // 8-bit data, 1 stop bit, no parity, DLAB = 1
    U0DLL = 97;         // Baud-rate divisor for nominal 9600 bps
    U0DLM = 0x00;       // Upper byte of divisor
    U0LCR = 0x03;       // DLAB = 0, UART configuration enabled
}

void UART0_TxChar(char ch)
{
    // Wait until the Transmit Holding Register is empty
    while (!(U0LSR & 0x20));

    // Send the character
    U0THR = ch;
}

void UART0_TxString(char *str)
{
    // Transmit each character until the string ends
    while (*str)
    {
        UART0_TxChar(*str++);
    }
}

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
    UART0_Init();

    while (1)
    {
        UART0_TxString("VPPCOE\r\n");
        Delay();
    }
}

/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
LPC2148 features two asynchronous serial ports (UART0 and UART1). UART
communication requires setting the baud rate generator using U0LCR (Line
Control Register, DLAB=1), U0DLL, and U0DLM divider latches based on PCLK
(Peripheral Clock). Data transmission occurs by polling the Transmit
Holding Register Empty (THRE) flag in U0LSR and writing bytes to U0THR.
Data reception polls the Receiver Data Ready (RDR) flag and reads from
U0RBR. Setting word length to 8 bits, 1 stop bit, and no parity
establishes standard 9600-8-N-1 serial framing.
============================================================================
*/
