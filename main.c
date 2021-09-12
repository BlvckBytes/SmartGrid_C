#include <stdio.h>
#include <string.h>

#include "include/stdparse.h"
#include "include/ccc_task.h"
#include "include/ccc_minute.h"

// Find cheapest slot id
void proc_lvl1(void)
{
    int num_tasks = stdp_num();
    int smallest_slot_cost = -1;
    int smallest_slot_id = 0;
    for (int i = 0; i < num_tasks; i++)
    {
        int curr_cost = stdp_num();
        if (smallest_slot_cost == -1 || curr_cost < smallest_slot_cost)
        {
            smallest_slot_cost = curr_cost;
            smallest_slot_id = i;
        }
    }
    printf("%d", smallest_slot_id);
}

// Find cheapest start task id to put tasks with specified length at
void proc_lvl2(void)
{
    // Load slots
    int num_slots = stdp_num();
    int slot_prices[num_slots];
    for (int i = 0; i < num_slots; i++)
        slot_prices[i] = stdp_num();

    // Get and print amount of tasks
    int num_tasks = stdp_num();
    printf("%d\n", num_tasks);

    // Loop tasks
    for (int i = 0; i < num_tasks; i++)
    {
        // Load task
        CCC_Task task = { stdp_num(), stdp_num(), 0, 0 };
        int curr_price = -1;
        int curr_begin = -1;

        // Top offset loop
        for (int j = 0; j <= num_slots - task.power; j++)
        {

            // Task length accumulator
            int acc = 0;
            for (int k = j; k < j + task.power; k++)
                acc += slot_prices[k];

            // Save next best result
            if (curr_price == -1 || acc < curr_price)
            {
                curr_price = acc;
                curr_begin = j;
            }
        }

        // Print task's result
        printf("%d %d\n", task.task_id, curr_begin);
    }
}

void proc_lvl3(void)
{
    // Parse minutes and their price
    int num_minutes = stdp_num();
    int minutes[num_minutes];
    for (int i = 0; i < num_minutes; i++)
        minutes[i] = stdp_num();

    int num_tasks = stdp_num();
    printf("%d\n", num_tasks);

    for (int i = 0; i < num_tasks; i++)
    {
        CCC_Task task = { stdp_num(), stdp_num(), stdp_num(), stdp_num() };

        int lowest_id = -1;
        for (int i = task.start_interval; i <= task.end_interval; i++)
        {
            if (lowest_id == -1 || minutes[i] < minutes[lowest_id])
                lowest_id = i;
        }

        printf("%d %d %d\n", task.task_id, lowest_id, task.power);
    }
}

// Compare task interval spans
int compare_task_span (const void *a, const void *b) {
    return (((CCC_Task *)a)->end_interval - ((CCC_Task *)a)->start_interval) - 
    (((CCC_Task *)b)->end_interval - ((CCC_Task *)b)->start_interval);
}

void proc_lvl4(void)
{
    int max_power = stdp_num(); // max/minute
    long max_bill = stdp_num(); //max bill
    int max_concurrent = stdp_num(); // max tasks at a time

    // Parse minutes
    int num_minutes = stdp_num();
    CCC_Minute minutes[num_minutes];
    for (int i = 0; i < num_minutes; i++)
        minutes[i] = (CCC_Minute) { stdp_num(), max_power };

    // Parse tasks
    int num_tasks = stdp_num();
    CCC_Task tasks[num_tasks];
    for (int i = 0; i < num_tasks; i++)
        tasks[i] = (CCC_Task) { stdp_num(), stdp_num(), stdp_num(), stdp_num() };
    printf("%d\n", num_tasks);

    // Sort to lowest span first
    qsort(tasks, num_tasks, sizeof(CCC_Task), compare_task_span);

    for (int i = 0; i < num_tasks; i++)
    {
        CCC_Task *task = &tasks[i];
        printf("%d ", task->task_id);

        while (task->power > 0)
        {
            if (max_bill < 0) {
                fprintf(stderr, "ERROR! Price higher than bill allows!\n");
                break;
            }

            int lowest_id = -1;
            for (int j = task->start_interval; j <= task->end_interval; j++)
            {
                if (minutes[j].power_left <= 0) continue;

                if (lowest_id == -1 || minutes[j].price < minutes[lowest_id].price)
                    lowest_id = j;
            }

            if (lowest_id < 0) {
                fprintf(stderr, "ERROR! Could not find a remaining slot for task %d!\n", task->task_id);
                break;
            }

            CCC_Minute *target = &minutes[lowest_id];
                
            // This minute has enough resources left
            if (task->power <= target->power_left)
            {
                target->power_left -= task->power;
                printf("%d %d", lowest_id, task->power);
                max_bill -= task->power * target->price;
                task->power = 0;
            }

            // Use as much as available and continue
            else
            {
                task->power -= target->power_left;
                printf("%d %d ", lowest_id, target->power_left);
                max_bill -= target->power_left * target->price;
                target->power_left = 0;
            }
        }

        printf("\n");
    }
}

int main(void)
{
    proc_lvl4();
    return 0;
}