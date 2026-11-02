/*
 * Experiment 19: Porting FreeRTOS to Arduino UNO (ATmega328P) Development Board
 * Demonstrates Kernel Porting, Preemptive Task Scheduling & vTaskDelay()
 */

#include <Arduino_FreeRTOS.h>

// Function Prototypes
void TaskBlink(void *pvParameters);
void TaskSerial(void *pvParameters);

void setup()
{
// Initialize LED pin
pinMode(LED_BUILTIN, OUTPUT);

// Initialize Serial Monitor
Serial.begin(9600);

while (!Serial)
{
; // Wait for Serial (safe for boards that need it)
}

Serial.println("FreeRTOS Demo Started");

// Create Blink Task
xTaskCreate(
TaskBlink,
"Blink Task",
128,
NULL,
1,
NULL);

// Create Serial Task
xTaskCreate(
TaskSerial,
"Serial Task",
128,
NULL,
1,
NULL);

// Scheduler starts automatically after setup() exits.
}

void loop()
{
// Empty
}

//-------------------------------
// Task 1: Blink LED
//-------------------------------
void TaskBlink(void *pvParameters)
{
(void)pvParameters;

while (1)
{
digitalWrite(LED_BUILTIN, HIGH);
vTaskDelay(500 / portTICK_PERIOD_MS);

digitalWrite(LED_BUILTIN, LOW);
vTaskDelay(500 / portTICK_PERIOD_MS);
}
}

//-------------------------------
// Task 2: Serial Printing
//-------------------------------
void TaskSerial(void *pvParameters)
{
(void)pvParameters;

while (1)
{
Serial.println("FreeRTOS is Running...");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}


/* --- Line 50: Execution & Theory Division --- */

/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
FreeRTOS is a lightweight real-time operating system designed for embedded
systems with constrained memory footprint. Porting FreeRTOS to the
ATmega328P microcontroller on the Arduino UNO board allows developers to
run preemptive priority-based multitasking on an 8-bit platform. The
FreeRTOS kernel replaces the traditional single-threaded loop() construct
with independent task routines, each possessing its own stack, priority,
and state machine. Tasks yield control cooperatively using vTaskDelay(),
allowing the scheduler to context-switch to ready tasks.
============================================================================
*/
