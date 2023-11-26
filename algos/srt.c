#include "../misc.h"
// gcc -shared -fPIC algos/srt.c -o algos/srt.so

void srt(processus *head)
{   affichP *aff=NULL;
    affichP *q=aff;
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
            if(q==NULL||strcmp(q->code,executingProcess->code)!=0){
            affichP *i = malloc(sizeof(affichP));
            strcpy(i->code,executingProcess->code);
            i->ta=executingProcess->date_arr;
            i->te=executingProcess->dur_exec_non_modif_proc;
            i->start = time;
            i->end= time+1;
            i->suiv=NULL;
            
            if(aff==NULL)
            {
           		aff=i;
                q=i;
            }
            else{
            q->suiv=i;
            q=i;
            }
            }else
            {
            q->end++;
            }
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
    GantAndStatistic(aff);
}
/*
 int main()
 {
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    srt(p);
   	return 0;
}
*/