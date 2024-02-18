#include <stdlib.h>
#include "ctest.h"
#include "rr.h"


CTEST_DATA(roundrobin)
{
    struct task_t task[3];
    int size;
};


CTEST_SETUP(roundrobin)
{
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}


CTEST2(roundrobin, test_process)
{
    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}


/*
 * @brief   Validate the wait times of each task
 * @retval  None
 */
CTEST2(roundrobin, wait_time_process)
{
    int waitTimes[] = {0, 1, 3};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTimes[i], data->task[i].waiting_time);
    }
}


/*
 * @brief   Validate the turnaround times of each task
 * @retval  None
 */
CTEST2(roundrobin, turnaround_time_process)
{
    int turnaroundTimes[] = {1, 3, 6};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(turnaroundTimes[i], data->task[i].turnaround_time);
    }
}


/*
 * @brief   Validate that the PID of each task is unique
 * @retval  None
 */
CTEST2(roundrobin, uniquePID_process)
{
    int PIDs[3];

    // Get the process_id of each task
    for(int i = 0; i < data->size; i++)
    {
        PIDs[i] = data->task[i].process_id;
    }

    // Assert that each PID is unique
    for(int i = 0; i < data->size - 1; i++)
    {
        for(int j = i + 1; j < data->size; j++)
        {
            ASSERT_NOT_EQUAL(PIDs[i], PIDs[j]);
        }
    }
}


CTEST2(roundrobin, leftToExecute_process)
{
    int leftToExecute[] = {0, 0, 0};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(leftToExecute[i], data->task[i].left_to_execute);
    }
}


CTEST_DATA(customRR)
{
    struct task_t task[3];
    int size;
};


CTEST_SETUP(customRR)
{
    int execution[] = {3, 2, 4};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}


CTEST2(customRR, differentExeTimes_process)
{
    int waitTimes[] = {4, 2, 5};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTimes[i], data->task[i].waiting_time);
    }
}


CTEST_DATA(customRR2)
{
    struct task_t task[10];
    int size;
};


CTEST_SETUP(customRR2)
{
    int execution[] = {3, 2, 4, 5, 7, 2, 1, 3, 2, 6};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 3;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}


CTEST2(customRR2, differentExeTimes_process)
{
    int turnaround[] = {3, 5 ,26, 28, 35, 16, 17, 20, 22, 34};
    int wait[] = {0, 3, 22, 23, 28, 14, 16, 17, 20, 28};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(wait[i], data->task[i].waiting_time);
    }

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(turnaround[i], data->task[i].turnaround_time);
    }
}