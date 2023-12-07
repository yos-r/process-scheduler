#include "../misc.h"
void premptivepriority(processus *head)
{
    viewProcess *view = NULL;
    viewProcess *q = view;
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    Queue *readyQueue = createQueue();
    int time = 0;
    printf("\nPre-emptive priority Scheduling: \n\n");

    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            printf("t= %d Process with priority %d %s arrived and has %d units to execute \n", current->date_arr, current->priorite, current->code, current->dur_exec_modif_proc);
            enqueue(readyQueue, current);
            current = current->suiv;
            sortByPriorityQueue(readyQueue);
        }

        sortByPriorityQueue(readyQueue);
        stateOfQueue3(readyQueue);

        processus *executingProcess = dequeue(readyQueue);

        if (executingProcess != NULL)
        {
            printf("T= %d: executing process %s \n", time, executingProcess->code);
            if (q == NULL || strcmp(q->code, executingProcess->code) != 0)
            {
                viewProcess *i = malloc(sizeof(viewProcess));
                strcpy(i->code, executingProcess->code);
                i->ta = executingProcess->date_arr;
                i->te = executingProcess->dur_exec;
                i->start = time;
                i->end = time + 1;
                i->suiv = NULL;

                if (view == NULL)
                {
                    view = i;
                    q = i;
                }
                else
                {
                    q->suiv = i;
                    q = i;
                }
            }
            else
            {
                q->end++;
            }
            executingProcess->dur_exec_modif_proc -= 1;
            time += 1;

            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf("t=%d , process %s is done with execution\n", time, executingProcess->code);
            }
            else
            {
                enqueue(readyQueue, executingProcess);
            }
        }
        else
        {
            printf("Time %d: CPU idle\n", time);
            time += 1;
        }
    }
    GantAndStatistic(view);
}
/*
int main()
{
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    fclose(file);
    premptivepriority(p);
    return 0;
}
*/