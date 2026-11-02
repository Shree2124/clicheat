# Experiment 21: Multitasking Real-Time IPC using Message Queue, Event Group & Semaphore

## Aim
To develop a multitasking real-time application using FreeRTOS and demonstrate inter-process communication using Message Queue, Event Group, and Semaphore

## Description
Safe inter-process communication in FreeRTOS using FIFO Message Queues, Mutex Serial protection, and Event Groups.

## Theory
Inter-Process Communication (IPC) is a vital RTOS mechanism that allows asynchronously executing tasks to safely exchange data and synchronization events without memory corruption or race conditions. FreeRTOS provides Message Queues (xQueueCreate, xQueueSend, xQueueReceive) for thread-safe FIFO passing of data packets, Event Groups (xEventGroupCreate, xEventGroupSetBits, xEventGroupWaitBits) for compound multi-task flag synchronization, and Semaphores/Mutexes for mutually exclusive hardware bus access. In this experiment, a producer task sends data packets through a queue while an event group signals synchronization milestones.
