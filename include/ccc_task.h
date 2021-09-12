#ifndef CCC_TASK_H_
#define CCC_TASK_H_

typedef struct CCC_Task
{
    int task_id;
    int power;
    int start_interval;
    int end_interval;
} CCC_Task;

#endif