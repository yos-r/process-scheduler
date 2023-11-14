void srtf(processus *head)
{
    int quantum = 3;
    processus *sortedProcesses = sortProcesses(head);
    Queue *readyQueue = createQueue();

    int time = 0; // Simulation time
    printf("\n Shortest Remaining Time First (SRTF):\n");

    // Process the list starting from the process with the lowest date_arr
    processus *current = sortedProcesses;
    while (current != NULL || readyQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            printf("Process %s arrived at time %d\n", current->code, time);
            enqueue(readyQueue, current);
            current = current->suiv;
        }
        // need to tsort the queue by

        sortByDurExecNonModifProcQueue(readyQueue);

        processus *executingProcess = dequeue(readyQueue);

        // Execute the process in the queue w/ the smallest remaining time

        if (executingProcess != NULL)
        {
            if (executingProcess->dur_exec_modif_proc < quantum)
            {
                printf("Time %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
                time += executingProcess->dur_exec_modif_proc;
                executingProcess->dur_exec_modif_proc = 0;
            }
            else
            {
                printf("Time %d: Executing process %s for %d units\n", time, executingProcess->code, quantum);
                time += quantum;
                executingProcess->dur_exec_modif_proc -= quantum;
            }
            // did it end? 1- yes 2-no , add to the queue
            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf("Process %s is done with execution\n", executingProcess->code);
            }
            else
            {
                printf("Process %s still has %d units remaining\n", executingProcess->code, executingProcess->dur_exec_modif_proc);
                // Add the process back to the ready queue if it has more to execute
                enqueue(readyQueue, executingProcess);
            }
        }
        else
        {
            printf("Time %d: CPU idle\n", time);
            time++;
        }
    }
}

