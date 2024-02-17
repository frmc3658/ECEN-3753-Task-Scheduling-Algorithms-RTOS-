#include "rr.h"
#include "queue.h"
#include <stdio.h>


#define MIN(x, y) ((x) < (y) ? (x) : (y))


void init(struct task_t *task, int *execution, int size)
{
    for(int i = 0; i < size; i++)
    {
        task[i].process_id  = i;
        task[i].execution_time = execution[i];
        task[i].left_to_execute = execution[i];
        task[i].waiting_time = 0;
        task[i].turnaround_time = 0;
    }
}


void round_robin(struct task_t *task, int quantum, int size)
{
    int runTime = 0;
    int taskRuntime = 0;

    // Create queue based on the task array
    struct node_t* queue = create_queue(task, size);

    // Execute the found robin algorithm
    for(int i = 0; i < size; i++)
    {
        // "Execute" the first task
        struct task_t* currentTask = peek(&queue);
        taskRuntime = MIN(currentTask->left_to_execute, quantum);
        currentTask->left_to_execute -= taskRuntime;

        // Pop the current task off the queue
        // when it is finished running
        if(currentTask->left_to_execute == 0)
        {
            pop(&queue);
        }

        // Calculate task wait time and turnaround time
        currentTask->waiting_time = runTime;
        currentTask->turnaround_time = runTime + taskRuntime;
        
        // Update runtime
        runTime += taskRuntime;

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

    // Cleanup
    free(queue->next);
    free(queue);
}


float calculate_average_wait_time(struct task_t *task, int size)
{
    int totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].waiting_time;
    }
    
    return totalTime / size;
}


float calculate_average_turn_around_time(struct task_t *task, int size)
{
    int totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].turnaround_time;
    }
    
    return totalTime / size;
}