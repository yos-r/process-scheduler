#include "../misc.h"
// gcc -shared -fPIC algos/basicfifo.c -o algos/basicfifo.so

// FIFO scheduling algorithm with a queue

void basicfifo(processus *head)
{
    affichP *aff=NULL;
    affichP *q=aff;
    Queue *processQueue = createQueue();
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int time = 0;
    printf("\n FIFO Scheduling:\n");

    while (current != NULL || processQueue->front != NULL)
    {
        while (current != NULL && current->date_arr <= time)
        {
            enqueue(processQueue, current);
            current = current->suiv;
            stateOfQueue2(processQueue);
        }
        processus *executingProcess = dequeue(processQueue);
        if (executingProcess != NULL)
        {
            printf("t %d: executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);           
        
		    affichP *i = malloc(sizeof(affichP));
            strcpy(i->code,executingProcess->code);
            i->ta=executingProcess->date_arr;
            i->te=executingProcess->dur_exec_non_modif_proc;
            i->start = time;
            i->end= time+executingProcess->dur_exec_modif_proc;
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
            time += executingProcess->dur_exec_modif_proc;
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
    }
    GantAndStatistic(aff);
}


 int main()
 {
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    basicfifo(p);
   	return 0;
}
