#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"
#include "math.h"

// Task handles
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;
TaskHandle_t Task3_Handle;
TaskHandle_t Task4_Handle;

// Queue handle
QueueHandle_t xQueue;

// Task 1: Periodically sends data to a queue
void Task1(void *pvParameters) {
    int counter = 0;
    for (;;) {
        counter++;
        printf("Task 1: Sending data %d to the queue.\n", counter);
        if (xQueueSend(xQueue, &counter, pdMS_TO_TICKS(100)) != pdPASS) {
            printf("Task 1: Failed to send data to the queue.\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// Task 2: Receives data from the queue and performs mathematical operations
void Task2(void *pvParameters) {
    int receivedData;
    for (;;) {
        if (xQueueReceive(xQueue, &receivedData, pdMS_TO_TICKS(500)) == pdPASS) {
            printf("Task 2: Received data %d from the queue.\n", receivedData);
            double result = sqrt((double)receivedData);
            printf("Task 2: Calculated square root: %.2f\n", result);
        } else {
            printf("Task 2: No data received from the queue.\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// Task 3: Controls the execution of Task 4 based on a condition
void Task3(void *pvParameters) {
    for (;;) {
        printf("Task 3: Suspending Task 4.\n");
        vTaskSuspend(Task4_Handle);
        vTaskDelay(pdMS_TO_TICKS(3000)); // Suspend Task 4 for 3 seconds

        printf("Task 3: Resuming Task 4.\n");
        vTaskResume(Task4_Handle);
        vTaskDelay(pdMS_TO_TICKS(3000)); // Allow Task 4 to run for 3 seconds
    }
}

// Task 4: Performs periodic logging
void Task4(void *pvParameters) {
    for (;;) {
        printf("Task 4: Performing periodic logging.\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

int main(void) {
    // Create a queue capable of holding 5 integers
    xQueue = xQueueCreate(5, sizeof(int));
    if (xQueue == NULL) {
        printf("Failed to create the queue.\n");
        return -1;
    }

    // Create tasks
    xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, &Task1_Handle);
    xTaskCreate(Task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &Task2_Handle);
    xTaskCreate(Task3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, &Task3_Handle);
    xTaskCreate(Task4, "Task4", configMINIMAL_STACK_SIZE, NULL, 1, &Task4_Handle);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    return 0;
}

