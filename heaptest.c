#define MAX 8

typedef struct s_tasks{
    int priority;
    int order;
    char name[100];
} t_task;


t_task TASK_ARRAY[MAX];
SIZE = 0;
ORDERCOUNTER = 0;

void swap(i, j)
{
    t_task temp = {0,0,0};
    temp = TASK_ARRAY[i];
    TASK_ARRAY[i] = TASK_ARRAY[j];
    TASK_ARRAY[j] = temp;
}

void heapify_up(int index){

    int parent;
    int should_swap;

    while(index > 0)
    {
        should_swap = 0;
        parent = (index - 1) / 2;
        if (TASK_ARRAY[index].priority < TASK_ARRAY[parent].priority)
            should_swap = 1;
        else if (TASK_ARRAY[index].priority == TASK_ARRAY[parent].priority)
            if (TASK_ARRAY[index].order < TASK_ARRAY[parent].order)
                should_swap = 1;
        if (should_swap)
        {
            swap(index, parent);
            index = parent;
        }
        else
            return;
    }
}

void push(int priority, char name[100]){


    t_task task = {priority, ORDERCOUNTER++, name};
    TASK_ARRAY[SIZE] = task;
    heapify_up(SIZE);
    SIZE++;
    
}

void main(){
    t_task example_tasks[sizeof(t_task)* 100] = {
        {2, "Send email report"},
        {1, "Process emergency alert"},
        {3, "Backup database"},
        {1, "Handle server crash"},
        {2, "User password reset"},
        {3, "Clean temp files"},
        {1, "Security breach log analysis"},
        {2, "Generate analytics dashboard"},
        {3, "Update documentation"},
        {2, "Process payment batch"}
    };
    for (int i = 0; i < sizeof(example_tasks) / sizeof(example_tasks[0]) ; i++){
            push(example_tasks[i].priority, example_tasks[i].name);
    }
}
