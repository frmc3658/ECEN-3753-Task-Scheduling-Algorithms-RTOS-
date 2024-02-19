#include <stdlib.h>
#include "ctest.h"
#include "fcfs.h"


///-------------------------------------------------
/// @brief  Dataset for the firstcomfirstserved
///         unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(firstcomefirstserved)
{
    struct task_t task[3];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the firstcomefirstserved unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(firstcomefirstserved)
{
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}


///-------------------------------------------------
/// @brief  Validate the process IDs in the
///         firstcomefirstserved dataset
///
/// @retval  None
///-------------------------------------------------
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

///-------------------------------------------------
/// @brief  Validate the wait times in the
///         firstcomefirstserved dataset
///  
/// @retval  None
///-------------------------------------------------
CTEST2(firstcomefirstserved, wait_time_process)
{
    int waitTimes[] = {0, 1, 3};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTimes[i], data->task[i].waiting_time);
    }
}


///-------------------------------------------------
/// @brief  Validate the turnaround times in the
///         firstcomefirstserved dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(firstcomefirstserved, turnaround_time_process)
{
    int turnaroundTimes[] = {1, 3, 6};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(turnaroundTimes[i], data->task[i].turnaround_time);
    }
}


///-------------------------------------------------
/// @brief  Validate that the PIDs are unique in the
///         firstcomefirstserved dataset
///
/// @retval  None
///-------------------------------------------------
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


///-------------------------------------------------
/// @brief  Dataset for the customFCFS unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(customFCFS)
{
    struct task_t task[10];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the customFCFS unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(customFCFS)
{
    int execution[] = {3, 2, 4, 5, 7, 2, 1, 3, 2, 6};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}


///-------------------------------------------------
/// @brief   Validate the wait and turnaround times
///          given a larger task queue
///
/// @retval  None
///-------------------------------------------------
CTEST2(customFCFS, largerTaskQueue_process)
{
    // Hand-calculated wait and turnaround times for the given dataset
    int waitTime[] = {0, 3, 5, 9, 14, 21, 23, 24, 27, 29};
    int turnaroundTime[] = {3, 5, 9, 14, 21, 23, 24, 27, 29, 35};

    // Validate the dataset
    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTime[i], data->task[i].waiting_time);
        ASSERT_EQUAL(turnaroundTime[i], data->task[i].turnaround_time);
        ASSERT_EQUAL(i, data->task[i].process_id);
    }
}


///-------------------------------------------------
/// @brief  Dataset for the customFCFS2 unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(customFCFS2)
{
    struct task_t task[10];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the customFCFS2 unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(customFCFS2)
{
    int execution[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}


///-------------------------------------------------
/// @brief   Validate the wait and turnaround times
///          given a NULL queue
///
/// @retval  None
///-------------------------------------------------
CTEST2(customFCFS2, nullQueue_process)
{
    // Hand-calculated wait and turnaround times for the given dataset
    int waitTime[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int turnaroundTime[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Validate the dataset
    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTime[i], data->task[i].waiting_time);
        ASSERT_EQUAL(turnaroundTime[i], data->task[i].turnaround_time);
        ASSERT_EQUAL(i, data->task[i].process_id);
    }
}
