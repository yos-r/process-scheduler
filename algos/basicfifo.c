#include "../misc.h"
// gcc -shared -fPIC algos/basicfifo.c -o algos/basicfifo.so

// FIFO scheduling algorithm with a queue
void basicfifo(processus *head)
{
    Queue *processQueue = createQueue();
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int time = 0; // Simulation time
    int totalExecutionTime = 0;

    printf("\n FIFO Scheduling:\n");

    while (current != NULL || processQueue->front != NULL)
    {
        // check if a process arrives at the current time
        while (current != NULL && current->date_arr <= time)
        {

            printf("t=%d Process %s arrives and is added to queue  \n", current->date_arr, current->code);

            enqueue(processQueue, current);
            current = current->suiv;
            stateOfQueue2(processQueue);
        }
        // execute the process at the front of the queue
        processus *executingProcess = dequeue(processQueue);
        if (executingProcess != NULL)
        {
            printf("t %d: executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
            time += executingProcess->dur_exec_modif_proc;
            totalExecutionTime += executingProcess->dur_exec_modif_proc;
            // printf("\n t %d: process %s is done ",time, executingProcess->code);
            executingProcess->fin = time; // mark the time it ended
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
    }
    printf("\n PERFORMANCE METRICS （￣︶￣）↗ ");
    processus *metric = sortedProcesses;
    afficherListe(sortedProcesses);
    int totalturnaround = 0;
    int totalwaiting = 0;
    int n = 0;

    while (metric != NULL)
    {
        n++;
        int turnaround = metric->fin - metric->date_arr;
        totalturnaround += turnaround;
        int waitingtime = turnaround - metric->dur_exec_non_modif_proc;
        totalwaiting += waitingtime;
        printf("\n process %s arrived at %d and left at %d, turnaround is: %d , wait time is %d\n",
               metric->code, metric->date_arr, metric->fin, turnaround, waitingtime);
        metric = metric->suiv;
    }
    float avgturnaround = totalturnaround / n;
    float avgwaiting = totalwaiting / n;

    printf("\n For the %d executed processes, avg waiting time is %f and avg. turnaround is %f", n, avgwaiting, avgturnaround);
    printf("\nTotal CPU utilization time is %d\n", totalExecutionTime);
}

// int main()
// {
//     FILE *file = fopen("pcb.txt", "rt");
//     processus *p = enreg_bcp(file);
//     fclose(file);

//     // afficherListe(p);

//     // Call the FIFO scheduling algorithm
//     // sortProcesses(p);
//     fifo_scheduling(p);

//     return 0;
// }