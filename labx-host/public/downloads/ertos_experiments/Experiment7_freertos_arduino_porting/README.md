# Experiment 19: Porting FreeRTOS to Arduino Development Board & Task Scheduling

## Aim
To port FreeRTOS to an Arduino UNO or STM32 development board and create multiple tasks to understand task scheduling and multitasking in a Real Time Operating System (RTOS)

## Description
Porting FreeRTOS kernel to ATmega328P microcontroller, configuring system tick, and executing independent scheduled tasks.

## Theory
FreeRTOS is a lightweight real-time operating system designed for embedded systems with constrained memory footprint. Porting FreeRTOS to the ATmega328P microcontroller on the Arduino UNO board allows developers to run preemptive priority-based multitasking on an 8-bit platform. The FreeRTOS kernel replaces the traditional single-threaded loop() construct with independent task routines, each possessing its own stack, priority, and state machine. Tasks yield control cooperatively using vTaskDelay(), allowing the scheduler to context-switch to ready tasks.
