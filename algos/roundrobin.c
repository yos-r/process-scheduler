#include "../misc.h"
void roundrobin(processus *head)
{
    viewProcess *view = NULL;
    viewProcess *q = view;
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int quantum;
    printf("\n Round Robin Scheduling: \n\n");
    do
    {
        printf("\nEnter the quantum value : ");
        scanf("%d", &quantum);
        if (quantum <= 0)
        {
            printf("Invalid input. Please enter a positive integer >0.\n");
        }
    } while (quantum <= 0);
    Queue *readyQueue = createQueue();
    int time = 0;
    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            enqueue(readyQueue, current);
            printf("t=%d",current->date_arr);

            current = current->suiv;
            sortByLastWait(readyQueue);

            stateOfQueue2(readyQueue);
        }
        processus *executingProcess = dequeue(readyQueue);
        if (executingProcess != NULL)
        {
            if (executingProcess->dur_exec_modif_proc < quantum)
            {
                if (q == NULL || strcmp(q->code, executingProcess->code) != 0)
                {
                    printf("t= %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
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
                }
                else
                {
                    q->end = q->end + executingProcess->dur_exec_modif_proc;
                }
                time += executingProcess->dur_exec_modif_proc;
                executingProcess->dur_exec_modif_proc = 0;
            }
            else
            {
                if (q == NULL || strcmp(q->code, executingProcess->code) != 0)
                {
                    printf("T= %d: Executing process %s for %d units\n", time, executingProcess->code, quantum);
                    viewProcess *i = malloc(sizeof(viewProcess));
                    strcpy(i->code, executingProcess->code);
                    i->ta = executingProcess->date_arr;
                    i->te = executingProcess->dur_exec;
                    i->start = time;
                    i->end = time + quantum;
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
                    q->end = q->end + quantum;
                }
                time += quantum;
                executingProcess->dur_exec_modif_proc -= quantum;
            }
            executingProcess->last_wait = time;
            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf(" at t= %d Process %s is done with execution\n", time, executingProcess->code);
            }
            else
            {
                printf("Process %s still has %d units remaining and is added at the queue \n", executingProcess->code, executingProcess->dur_exec_modif_proc);
                enqueue(readyQueue, executingProcess);
            }
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
    }
    GantAndStatistic(view);
}
