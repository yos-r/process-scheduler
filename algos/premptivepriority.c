// gcc -shared -fPIC algos/premptivepriority.c -o algos/premptivepriority.so

#include "../misc.h"
void premptivepriority(processus *head)
{
    //sort processes by date of arrival
    processus *sortedProcesses = sortProcesses(head);
    //temp var that will be used to parse the processes list
    processus *current = sortedProcesses;
    int quantum=3; //need to be customizable
    Queue *readyQueue = createQueue();
    int time = 0; // Simulation time
    displayTab(sortedProcesses);
    printf("\n Pre-emptive priority scheduling: \n");

    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            printf("t= %d Process w/ priority %d %s arrived and has %d units to execute \n", current->date_arr,current->priorite, current->code, current->dur_exec_modif_proc);
            enqueue(readyQueue, current);
            current = current->suiv;
            sortByPriorityQueue(readyQueue);
            stateOfQueue3(readyQueue);
        }
        // sort the queue by shortest remaning time
        sortByPriorityQueue(readyQueue);

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