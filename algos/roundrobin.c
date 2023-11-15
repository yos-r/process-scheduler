// #include "../genListFile.c"
// #include "../misc.c"

#include "../misc.h"
void roundrobin(processus *head)
{
    //sort processes by date of arrival
    processus *sortedProcesses = sortProcesses(head);
    //temp var that will be used to parse the processes list
    processus *current = sortedProcesses;
    int quantum=3; //need to be customizable
    Queue *readyQueue = createQueue();
    int time = 0; // Simulation time
    printf("\n Round Robin Scheduling with quantum equal to: %d\n", quantum);

    //stop when current is null AND readyqueue is empty!
    while (current != NULL || readyQueue->front != NULL)
    {
        // enter if current's time coincides w/ time, enqueue that process and move on the next
        while (current != NULL && current->date_arr <= time)
        {
            printf("Process %s arrived at time %d\n", current->code, current->date_arr);
            enqueue(readyQueue, current);
            current = current->suiv;
        }

        //take the process at the front of the queue
        processus *executingProcess = dequeue(readyQueue);
        // A- the process taken from the queue is executed B- no process in the queue
        if (executingProcess != NULL)
        {
            if (executingProcess->dur_exec_modif_proc < quantum)
            {
                printf("T= %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
                time += executingProcess->dur_exec_modif_proc;
                executingProcess->dur_exec_modif_proc = 0;
            }
            else
            {
                printf("T= %d: Executing process %s for %d units\n", time, executingProcess->code, quantum);
                time += quantum;
                executingProcess->dur_exec_modif_proc -= quantum;
            }

            
            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf(" at t= %d Process %s is done with execution\n",time, executingProcess->code);
                
            }
            else
            {
                //enqueue the process when it completes its quantum.
                printf("Process %s still has %d units remaining and is added at the queue \n", executingProcess->code, executingProcess->dur_exec_modif_proc);
                enqueue(readyQueue, executingProcess);
            }
        }
        else
        {
            //no process in the readyQueue!
            printf("Time %d: CPU idle\n", time);
            time++;
        }
    }
}

// USE MAIN if you want cmd args

// int main(int argc, char *argv[])
// {

//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <quantum>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     int quantum = atoi(argv[1]); // Convert the command-line argument to an integer
//     if (quantum <= 0)
//     {
//         fprintf(stderr, "Quantum must be a positive integer\n");
//         return EXIT_FAILURE;
//     }

//     FILE *file = fopen("pcb.txt", "rt");
//     processus *p = enreg_bcp(file);
//     fclose(file);

//     rr_robin(p, quantum);

//     return 0;
// }