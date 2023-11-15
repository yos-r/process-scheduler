// gcc -shared -fPIC algos/multilevel.c -o algos/multilevel.so

#include "../misc.h"
void multilevel(processus *head)
{
    // sort processes by date of arrival
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int quantum = 3; // need to be customizable
    Queue *readyQueue = createQueue();
    int time = 0; // Simulation time
    printf("\n  Multilevel  scheduling: \n");
    processus *temp;
    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            printf("t= %d Process w/ priority %d %s arrived and has %d units to execute \n", current->date_arr, current->priorite, current->code, current->dur_exec_modif_proc);
            enqueue(readyQueue, current);
            sortByPriorityQueue(readyQueue);
            stateOfQueue3(readyQueue);
            temp = current;
            current = current->suiv;
        }
        // sort the queue by priority
        sortByPriorityQueue(readyQueue);
        // do we need round robin?
        if (checkMulti(readyQueue))
        {
            //gather what processes have the highest priority: build a linked list??
            //execute roundrobin on that list?
            // what about the time?
            processus *liste=buildList(readyQueue);
            displayTab(liste); // display the list of 
            //
            processus *exec = dequeue(readyQueue);
            if (exec->dur_exec_modif_proc < quantum)
            {
                printf("T= %d: Executing process %s for %d units\n", time, exec->code, exec->dur_exec_modif_proc);
                time += exec->dur_exec_modif_proc;
                exec->dur_exec_modif_proc = 0;
            }
            else
            {
                printf("T= %d: Executing process %s for %d units\n", time, exec->code, quantum);
                time += quantum;
                exec->dur_exec_modif_proc -= quantum;
            }

            
            if (exec->dur_exec_modif_proc <= 0)
            {
                printf(" at t= %d Process %s is done with execution\n",time, exec->code);
                
            }
            else
            {
                //enqueue the process when it completes its quantum.
                printf("Process %s still has %d units remaining and is added at the queue \n", exec->code, exec ->dur_exec_modif_proc);
                enqueue(readyQueue, exec);
            }

            

        }
        else //no multilevel, just the usual
        {
            processus *executingProcess = dequeue(readyQueue);

            if (executingProcess != NULL)
            {

                printf("T= %d: executing process %s \n", time, executingProcess->code);
                executingProcess->dur_exec_modif_proc -= 1; // decrement by 1
                time += 1;

                // POST-EXECTUION: EITHER DONE OR ADDED TO QUEUE
                if (executingProcess->dur_exec_modif_proc <= 0)
                {
                    printf("t=%d , process %s is done with execution\n", time, executingProcess->code);
                }
                else
                {
                    // always add to the queue, because sorting will happen
                    enqueue(readyQueue, executingProcess);
                }
            }

            else
            {
                printf("Time %d: CPU idle\n", time);
                time += 1;
            }
        }
    }
}
