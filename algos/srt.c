#include "../misc.h"
// gcc -shared -fPIC algos/srt.c -o algos/srt.so

void srt(processus *head)
{
    // no need for quantum in SRT
    //  int quantum = 3;
    processus *sortedProcesses = sortProcesses(head);
    Queue *readyQueue = createQueue();
    int time = 0; // Simulation time

    printf("\n Shortest Remaining Time First (SRTF):\n");

    processus *current = sortedProcesses; // sort list of processes by date of arrival

    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            printf("t= %d Process %s arrived and has %d units to execute \n", current->date_arr, current->code, current->dur_exec_modif_proc);
            enqueue(readyQueue, current);
            current = current->suiv;
            sortByDurExecModifProcQueue(readyQueue);
            stateOfQueue(readyQueue);
        }
        // sort the queue by shortest remaning time
        sortByDurExecModifProcQueue(readyQueue);

        // might add small func to display the queue?

        processus *executingProcess = dequeue(readyQueue);

        // Execute the process in the queue w/ the smallest remaining time

        if (executingProcess != NULL)
        {
            printf("T= %d: executing process %s \n", time, executingProcess->code);
            executingProcess->dur_exec_modif_proc -= 1; // decrement by 1
            time += 1;
            // printf("T= %d: process %s has %d units left\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);

            
            // did it end? 1- yes 2-no , add to the queue
            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf("t=%d , process %s is done with execution\n", time, executingProcess->code);
            }
            else
            {
                // printf("t=%d , process %s still has %d units remaining\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
                // add the process back to the ready queue if it has more to execute
                enqueue(readyQueue, executingProcess);
            }
        }
        else
        {
            printf("Time %d: CPU idle\n", time);
            time+=1;
        }
    }
}
