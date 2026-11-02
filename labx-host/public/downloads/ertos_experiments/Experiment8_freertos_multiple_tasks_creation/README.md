# Experiment 20: Creating Multiple Tasks in FreeRTOS with Priority Preemption

## Aim
To create Multiple Task using free RTOS On an Arduino UNO and understanding the multitasking capabilities of RTOS

## Description
Multi-task instantiation in FreeRTOS: assigning priority tiers, preemptive context switches, and telemetry logging.

## Theory
Multitasking in FreeRTOS enables the concurrent execution of multiple independent operational threads on a single core microcontroller. The FreeRTOS preemptive scheduler enforces priority-based task switching, ensuring that the highest priority ready task always gains execution control. In this experiment, three distinct tasks (Sensor Reading Task, Display/Telemetry Task, and Heartbeat Monitor Task) are instantiated with varying priorities to demonstrate how priority inversion is avoided and how tasks cleanly share CPU cycles.
