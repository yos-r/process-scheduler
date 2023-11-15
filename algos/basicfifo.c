#include "../misc.h"
// gcc -shared -fPIC algos/basicfifo.c -o algos/basicfifo.so


// FIFO scheduling algorithm with a queue
void basicfifo(processus *head)
{
    Queue *processQueue = createQueue();
    // sort the process
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
            printf("t %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
            time += executingProcess->dur_exec_modif_proc;
            totalExecutionTime += executingProcess->dur_exec_modif_proc;
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
    }

    printf("Total CPU time is %d\n", totalExecutionTime);
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