# Experiment 18: Task Synchronization using Binary and Counting Semaphores in FreeRTOS

## Aim
To illustrate the use of Binary Semaphore and Counting Semaphore for Task Synchronization using FreeRTOS

## Description
Synchronization of producer and worker tasks using FreeRTOS binary signaling and counting semaphore resource pools.

## Theory
FreeRTOS is a lightweight open source Real time Operating system (RTOS) made for use in embedded systems. It helps manage multiple tasks schedules them properly allows tasks to work together smoothly and share resources without conflict. Semaphores are synchronization mechanisms used to coordinate tasks. A Binary Semaphore has a maximum count of 1, functioning similarly to a mutex flag to signal events between tasks or ISRs using xSemaphoreCreateBinary, xSemaphoreTake, and xSemaphoreGive. A Counting Semaphore has a count >= 1 (xSemaphoreCreateCounting), tracking multiple available units of a shared resource or counting events. When tasks take the semaphore, the count decrements; when tasks release the resource, the count increments.
