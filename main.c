#include <stdio.h>
#include <string.h>

#include "include/stdparse.h"
#include "include/ccc_task.h"

// Find cheapest slot id
void proc_lvl1()
{
    int num_tasks = stdp_int();
    int smallest_slot_cost = -1;
    int smallest_slot_id = 0;
    for (int i = 0; i < num_tasks; i++)
    {
        int curr_cost = stdp_int();
        if (smallest_slot_cost == -1 || curr_cost < smallest_slot_cost)
        {
            smallest_slot_cost = curr_cost;
            smallest_slot_id = i;
        }
    }
    printf("%d", smallest_slot_id);
}

// Find cheapest start task id to put tasks with specified length at
void proc_lvl2()
{
    // Load slots
    int num_slots = stdp_int();
    int slot_prices[num_slots];
    for (int i = 0; i < num_slots; i++)
        slot_prices[i] = stdp_int();

    // Get and print amount of tasks
    int num_tasks = stdp_int();
    printf("%d\n", num_tasks);

    // Loop tasks
    for (int i = 0; i < num_tasks; i++) {
        // Load task
        CCC_Task task = { stdp_int(), stdp_int() };
        int curr_price = -1;
        int curr_begin = -1;

        // Top offset loop
        for (int j = 0; j <= num_slots - task.dur; j++) {

            // Task length accumulator
            int acc = 0;
            for (int k = j; k < j + task.dur; k++)
                acc += slot_prices[k];

            // Save next best result
            if (curr_price == -1 || acc < curr_price) {
                curr_price = acc;
                curr_begin = j;
            }
        }

        // Print task's result
        printf("%d %d\n", task.task_id, curr_begin);
    }
}

int main(void)
{
    proc_lvl2();
    return 0;
}