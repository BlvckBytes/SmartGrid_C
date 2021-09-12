#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global line buffer, needs to be as big as longest line from STDIN
char line_buf[128] = {'\0'};

/*
    Read a line from STDIN, terminated by EOL or EOF, terminate with NULL
*/
void read_line()
{
    int read_buf_pointer = 0;
    for (int i = 0; i < sizeof(line_buf); i++)
    {
        int c = getchar();

        // Skip carriage returns
        if (c == 13) continue;

        // EOL or EOF
        if (c == 10 || c < 0) break;

        line_buf[read_buf_pointer++] = c;
    }

    // Terminate string
    line_buf[read_buf_pointer] = '\0';
}

/*
    Get next int from stream, either same line or next line
    All other characters get ignored and won't result in errors
*/
int get_int()
{
    static int line_char_pointer = 0;
    
    int start_index = -1;
    int end_index = -1;
    
    // Loop from last unchecked till end
    for (int i = line_char_pointer; i < strlen(line_buf); i++)
    {
        // Is number
        if (line_buf[i] >= 48 && line_buf[i] <= 57)
        {
            if (start_index == -1) start_index = i;
            continue;
        }

        // Number ended
        else if (start_index >= 0)
        {
            end_index = i - 1;
            break;
        }
    }

    // No int left, go to next line
    if (start_index == -1)
    {
        // Read next line into buffer
        read_line();

        // Nothing left to read, -1 as fallback
        if (strlen(line_buf) == 0) return -1;

        // Reset line char pointer and query new line
        line_char_pointer = 0;
        return get_int(line_buf);
    }
    
    // End-index is EOL
    if (end_index == -1) end_index = strlen(line_buf) - 1;

    // Create substring
    char num_buf[end_index - start_index + 2];
    memcpy(num_buf, &line_buf[start_index], sizeof(num_buf));

    // Start at next untouched char
    line_char_pointer = end_index + 1;

    // Parse substring
    return atoi(num_buf);
}

_Bool is_digit(int character) {
    return character >= 48 && character <= 57;
}

int get_int_2() {
    int curr_char;
    _Bool in_number = 0;
    static char digit_buf[128];
    int digit_buf_pointer = 0;

    do {
        curr_char = getchar();
        in_number |= is_digit(curr_char);
        if (is_digit(curr_char)) digit_buf[digit_buf_pointer++] = curr_char;
    } while ((!is_digit(curr_char) && !in_number) || (in_number && is_digit(curr_char)));

    digit_buf[digit_buf_pointer] = '\0';
    return atoi(digit_buf);
}

// Find cheapest slot id
void proc_lvl1()
{
    int num_tasks = get_int();
    int smallest_slot_cost = -1;
    int smallest_slot_id = 0;
    for (int i = 0; i < num_tasks; i++)
    {
        int curr_cost = get_int();
        if (smallest_slot_cost == -1 || curr_cost < smallest_slot_cost)
        {
            smallest_slot_cost = curr_cost;
            smallest_slot_id = i;
        }
    }
    printf("%d", smallest_slot_id);
}

typedef struct CCC_Task
{
    int task_id;
    int dur;
} CCC_Task;

// Find cheapest start task id to put tasks with specified length at
void proc_lvl2()
{
    // Load slots
    int num_slots = get_int_2();
    int slot_prices[num_slots];
    for (int i = 0; i < num_slots; i++)
        slot_prices[i] = get_int_2();

    // Get and print amount of tasks
    int num_tasks = get_int_2();
    printf("%d\n", num_tasks);

    // Loop tasks
    for (int i = 0; i < num_tasks; i++) {
        // Load task
        CCC_Task task = { get_int_2(), get_int_2() };
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