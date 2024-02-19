#include "fcfs.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>


void init(struct task_t* task, int* execution, int size)
{
    for(int i = 0; i < size; i++)
    {
        task[i].process_id  = i;
        task[i].execution_time = execution[i];
    }
}


void first_come_first_served(struct task_t* task, int size)
{
    #ifdef DEBUG
    int runTime = 0;

    // Create queue based on the task array
    struct node_t* queue = create_queue(task, size);
    struct node_t* topNode = queue->next;

    // Pop off the front item until there are no more tasks
    for(int i = 0; i < size; i++)
    {
        // "Execute" the first task
        struct task_t* currentTask = peek(&topNode);

        // Pop the head from the queue
        pop(&topNode);

        // Calculate task wait time and turnaround time
        currentTask->waiting_time = runTime;
        currentTask->turnaround_time = runTime + currentTask->execution_time;
        
        // Update runtime
        runTime += currentTask->execution_time;

        // Print times to console
        printf("\nTask[%d] Wait Time: %d\n", i, currentTask->waiting_time);
        printf("Task[%d] Turnaround Time: %d\n", i, currentTask->turnaround_time);
    }

    // Calculate average times
    float avgWaitTime = calculate_average_wait_time(task, size);
    float avgTurnaroundTime = calculate_average_turn_around_time(task, size);

    // Print average times
    printf("Average Wait Time: %f\n", avgWaitTime);
    printf("Average Turnaround Time: %f\n", avgTurnaroundTime);

    free(queue);
    #endif

    int runTime = 0;

    // Construct a task queue from the task array
    struct node_t* queue = create_queue(task, size);
    struct task_t* currentTask;

    while(!is_empty(&queue))
    {
        // "Execute" the first task
        currentTask = peek(&queue);
        currentTask->waiting_time = runTime;
        runTime += currentTask->execution_time;
        currentTask->turnaround_time = runTime;

        pop(&queue);

        // Print times to console
        printf("\nTask[%d] Wait Time: %d\n", currentTask->process_id, currentTask->waiting_time);
        printf("Task[%d] Turnaround Time: %d\n", currentTask->process_id, currentTask->turnaround_time);
    }
    
    // Calculate average times
    float avgWaitTime = calculate_average_wait_time(task, size);
    float avgTurnaroundTime = calculate_average_turn_around_time(task, size);

    // Print average times
    printf("Average Wait Time: %f\n", avgWaitTime);
    printf("Average Turnaround Time: %f\n", avgTurnaroundTime);

    // Cleanup
    free(queue->next);
    free(queue);
}


float calculate_average_wait_time(struct task_t* task, int size)
{
    float totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].waiting_time;
    }
    
    return totalTime / size;
}


float calculate_average_turn_around_time(struct task_t* task, int size)
{
    float totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].turnaround_time;
    }
    
    return totalTime / size;
}