/*
 * Experiment 20: Creating Multiple Tasks using FreeRTOS on Arduino UNO
 * Demonstrates Priority-Based Preemption and Task State Transitions
 */

#include <Arduino_FreeRTOS.h>

// Task declarations
void task1(void *pvParameters);
void task2(void *pvParameters);

void setup()
{
Serial.begin(9600);

Serial.println("FreeRTOS Started");

// Create Task 1 with priority 1
xTaskCreate(
task1,
"Task 1",
128,
NULL,
1,
NULL
);

// Create Task 2 with priority 2
xTaskCreate(
task2,
"Task 2",
128,
NULL,
2,
NULL
);
}

void loop()
{
// Keep empty because FreeRTOS tasks are running
}

void task1(void *pvParameters)
{
while (1)
{
Serial.println("Task 1 is running");

// Wait for 1 second
vTaskDelay(pdMS_TO_TICKS(1000));
}
}

void task2(void *pvParameters)
{
while (1)
{
Serial.println("Task 2 is running");

// Wait for 2 seconds
vTaskDelay(pdMS_TO_TICKS(2000));
}
}
/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
Multitasking in FreeRTOS enables the concurrent execution of multiple
independent operational threads on a single core microcontroller. The
FreeRTOS preemptive scheduler enforces priority-based task switching,
ensuring that the highest priority ready task always gains execution
control. In this experiment, three distinct tasks (Sensor Reading Task,
Display/Telemetry Task, and Heartbeat Monitor Task) are instantiated with
varying priorities to demonstrate how priority inversion is avoided and
how tasks cleanly share CPU cycles.
============================================================================
*/
