// gcc -shared -fPIC algos/roundbobin.c -o algos/roundrobin.so
#include "../misc.h"
void roundrobin(processus *head)
{   affichP *aff=NULL;
    affichP *q=aff;
    processus *sortedProcesses = sortProcesses(head);
    //temp var that will be used to parse the processes list
    processus *current = sortedProcesses;
    int quantum;
    do{
        printf("\nEnter the quantum value : ");
        scanf("%d", &quantum);
        if (quantum <= 0) {
        printf("Invalid input. Please enter a positive integer >0.\n");
        }
    }while (quantum<=0);
    Queue *readyQueue = createQueue();
    int time = 0; 
    //stop when current is null AND readyqueue is empty!
    while (current != NULL || readyQueue->front != NULL)
    {
        // enter if current's time coincides w/ time, enqueue that process and move on the next
        while (current != NULL && current->date_arr <= time)
        {
            printf("Process %s arrived at time %d\n", current->code, current->date_arr);
            enqueue(readyQueue, current);
            current = current->suiv;
            sortByLastWait(readyQueue);
            stateOfQueue2(readyQueue);
        }
        //take the process at the front of the queue
        processus *executingProcess = dequeue(readyQueue);
        // A- the process taken from the queue is executed B- no process in the queue
        if (executingProcess != NULL)
        {
            if (executingProcess->dur_exec_modif_proc < quantum)
            {if(q==NULL||strcmp(q->code,executingProcess->code)!=0){
                printf("T= %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
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
                }}
                else {
                    q->end=q->end+executingProcess->dur_exec_modif_proc;
                }
                time += executingProcess->dur_exec_modif_proc;
                executingProcess->dur_exec_modif_proc = 0;
            }
            else
            {   if(q==NULL||strcmp(q->code,executingProcess->code)!=0){
                printf("T= %d: Executing process %s for %d units\n", time, executingProcess->code, quantum);
                affichP *i = malloc(sizeof(affichP));
                strcpy(i->code,executingProcess->code);
                i->ta=executingProcess->date_arr;
                i->te=executingProcess->dur_exec_non_modif_proc;
                i->start = time;
                i->end= time+quantum;
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
                q->end=q->end+quantum;
                }
                time += quantum;
                executingProcess->dur_exec_modif_proc -= quantum;
            }
            executingProcess->last_wait=time; 
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
    GantAndStatistic(aff);
}
/*
int main()
 { 
     FILE *file = fopen("pcb.txt", "rt");
     processus *p = enreg_bcp(file);
     fclose(file);
     roundrobin(p);
     return 0;
}
*/