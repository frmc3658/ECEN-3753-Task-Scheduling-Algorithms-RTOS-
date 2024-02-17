#include <stdlib.h>
#include "ctest.h"
#include "fcfs.h"

// Note: the name in the first parameter slot must match all tests in that group
CTEST_DATA(firstcomefirstserved)
{
    struct task_t task[3];
    int size;
};

CTEST_SETUP(firstcomefirstserved)
{
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(firstcomefirstserved, test_process)
{
    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

/********************************
 *      Custom Unit Tests       *
 ********************************/

/*
 * @brief   Validate the wait times of each task
 * @retval  None
 */
CTEST2(firstcomefirstserved, wait_time_process)
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
CTEST2(firstcomefirstserved, turnaround_time_process)
{
    int turnaroundTimes[] = {1, 3, 6};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(turnaroundTimes[i], data->task[i].turnaround_time);
    }
}


/*
 * @brief   Validate that thePID of each task is unique
 * @retval  None
 */
CTEST2(firstcomefirstserved, uniquePID_process)
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