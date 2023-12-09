#include "../misc.h"
void basicfifo(processus *head)
{
    viewProcess *view = NULL;
    viewProcess *q = view;
    Queue *processQueue = createQueue();
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int time = 0;
    printf("\n FIFO Scheduling: \n\n");

    while (current != NULL || processQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            enqueue(processQueue, current);
            printf("t=%d",current->date_arr);
            current = current->suiv;
            stateOfQueue2(processQueue);
        }
        processus *executingProcess = dequeue(processQueue);
        if (executingProcess != NULL)
        {
            printf("t %d: executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
            viewProcess *i = malloc(sizeof(viewProcess));
            strcpy(i->code, executingProcess->code);
            i->ta = executingProcess->date_arr;
            i->te = executingProcess->dur_exec;
            i->start = time;
            i->end = time + executingProcess->dur_exec_modif_proc;
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
            time += executingProcess->dur_exec_modif_proc;
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
    }
    GantAndStatistic(view);
}
