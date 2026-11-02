/*
 * Experiment 18: Binary and Counting Semaphores for Task Synchronization in FreeRTOS
 * Demonstrates xSemaphoreCreateBinary and xSemaphoreCreateCounting on Arduino / AVR
 */

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
SemaphoreHandle_t BinarySem;
SemaphoreHandle_t CountSem;

//---------------- Binary Semaphore ----------------//

void BinaryGiveTask(void *pvParameters)
{
  while (1)
  {
    Serial.println("Task1: Giving Binary Semaphore");
    xSemaphoreGive(BinarySem);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void BinaryTakeTask(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(BinarySem, portMAX_DELAY) == pdTRUE)
    {
      Serial.println("Task2: Binary Semaphore Received");
    }
  }
}
//---------------- Counting Semaphore ----------------//
void CountGiveTask(void *pvParameters)
{
  while (1)
  {
    xSemaphoreGive(CountSem);
    Serial.println("Task3: Counting Semaphore Given");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
void CountTakeTask(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(CountSem, portMAX_DELAY) == pdTRUE)
    {
      Serial.println("Task4: Counting Semaphore Taken");
    }

    vTaskDelay(1500 / portTICK_PERIOD_MS);
  }
}
void setup()
{
  Serial.begin(9600);
  BinarySem = xSemaphoreCreateBinary();
  CountSem = xSemaphoreCreateCounting(5, 0);
  xTaskCreate(BinaryGiveTask,
              "Task1",
              128,
              NULL,
              1,
              NULL);
  xTaskCreate(BinaryTakeTask,
              "Task2",
              128,
              NULL,
              1,
              NULL);
  xTaskCreate(CountGiveTask,
              "Task3",
              128,
              NULL,
              1,
              NULL);
  xTaskCreate(CountTakeTask,
              "Task4",
              128,
              NULL,
              1,
              NULL);
  vTaskStartScheduler();
}
void loop()
{
}

/*
============================================================================
EXPERIMENT THEORY (from Embedded Systems & RTOS Laboratory Submission):
============================================================================
FreeRTOS is a lightweight open source Real time Operating system (RTOS)
made for use in embedded systems. It helps manage multiple tasks schedules
them properly allows tasks to work together smoothly and share resources
without conflict. Semaphores are synchronization mechanisms used to
coordinate tasks. A Binary Semaphore has a maximum count of 1, functioning
similarly to a mutex flag to signal events between tasks or ISRs using
xSemaphoreCreateBinary, xSemaphoreTake, and xSemaphoreGive. A Counting
Semaphore has a count >= 1 (xSemaphoreCreateCounting), tracking multiple
available units of a shared resource or counting events. When tasks take
the semaphore, the count decrements; when tasks release the resource, the
count increments.
============================================================================
*/
