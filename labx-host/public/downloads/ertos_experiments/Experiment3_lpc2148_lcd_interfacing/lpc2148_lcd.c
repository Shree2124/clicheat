/*
 * Experiment 15: Interfacing 16x2 Alphanumeric LCD with LPC2148
 * 8-Bit Interface: Data on P0.0-P0.7, Control on P0.8(RS), P0.9(RW), P0.10(EN)
 */

#include <LPC214x.h>

#include 

#define RS (1U << 8)
#define EN (1U << 9)
#define DATA_MASK (0xFU << 12)

void delay(void)
{
    unsigned int i;
    for (i = 0; i < 50000; i++);
}

void lcd_pulse(void)
{
    IO0SET = EN;
    delay();
    IO0CLR = EN;
    delay();
}

void lcd_nibble(unsigned int data)
{
    IO0CLR = DATA_MASK;
    IO0SET = ((data & 0x0F) << 12);
    lcd_pulse();
}

void lcd_command(unsigned int cmd)
{
    IO0CLR = RS;
    lcd_nibble(cmd >> 4);
    lcd_nibble(cmd);
    delay();
}

void lcd_data(unsigned int data)
{
    IO0SET = RS;
    lcd_nibble(data >> 4);
    lcd_nibble(data);
    delay();
}

void lcd_string(char *str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init(void)
{
    IO0CLR = RS | EN | DATA_MASK;

    delay();

    lcd_nibble(0x03);
    delay();
    lcd_nibble(0x03);
    delay();
    lcd_nibble(0x03);
    delay();

    lcd_nibble(0x02);  // Select 4-bit mode

    lcd_command(0x28); // 2 lines, 5x8 font
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x06); // Increment cursor
    lcd_command(0x01); // Clear display
    delay();
}

int main(void)
{
    PINSEL0 = 0x00000000;
    IO0DIR |= RS | EN | DATA_MASK;

    lcd_init();

    lcd_command(0x80);
    lcd_string("WELCOME");

    lcd_command(0xC0);
    lcd_string("LPC2148 LCD");

    while (1)
    {
        // Keep the message displayed
    }
}

/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
A 16x2 alphanumeric LCD display interfaces with the LPC2148 using 8 data
lines (D0-D7) and 3 control lines: RS (Register Select - 0 for command, 1
for data), RW (Read/Write - grounded for write), and EN (Enable -
high-to-low pulse to latch data). Commands initialize display mode (0x38
for 8-bit, 2-line mode), display ON cursor OFF (0x0C), clear screen
(0x01), and set DDRAM address (0x80 line 1, 0xC0 line 2). The LPC2148
drives the LCD by asserting RS, placing data on Port 0, and pulsing EN
with sufficient setup and hold time.
============================================================================
*/
