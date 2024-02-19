#include "fcfs.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>


///-------------------------------------------------
/// @brief  Initializes the First Come First Served
///         unit tests
///
/// @param[in] task The task queue array
/// @param[in] execution Array containing the
///                      execution times of each
///                      task
/// @param[in] size Size of the task queue array
///
/// @return Average wait time of all tasks in 
///         the queue
///-------------------------------------------------
void init(struct task_t* task, int* execution, int size)
{
    for(int i = 0; i < size; i++)
    {
        task[i].process_id  = i;
        task[i].execution_time = execution[i];
    }
}


///-------------------------------------------------
/// @brief  First Come First Served scheduler algorithm
///
/// @param[in] task The task queue array
/// @param[in] size Size of the task queue array
///
/// @return None
///-------------------------------------------------
void first_come_first_served(struct task_t* task, int size)
{
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


///-------------------------------------------------
/// @brief  Calculate the average wait time of
///         the tasks in the queue
///
/// @param[in] task The task queue array
/// @param[in] size Size of the task queue array
///
/// @return Average wait time of all tasks in 
///         the queue
///-------------------------------------------------
float calculate_average_wait_time(struct task_t* task, int size)
{
    float totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].waiting_time;
    }
    
    return totalTime / size;
}


///-------------------------------------------------
/// @brief  Calculate the average turnaround time of
///         the tasks in the queue
///
/// @return None
///-------------------------------------------------
float calculate_average_turn_around_time(struct task_t* task, int size)
{
    float totalTime = 0;

    for(int i = 0; i < size; i++)
    {
        totalTime += task[i].turnaround_time;
    }
    
    return totalTime / size;
}