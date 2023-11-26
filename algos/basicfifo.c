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
            i->te=executingProcess->dur_exec_modif_proc;
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
	 
	affichP *x = aff;
	printf("+----------------------+--------+--------+\n");
	printf("|       Process        | Start  |  End   |\n");
	printf("+----------------------+--------+--------+\n");

	while (x != NULL) {
   		printf("| %-20s | %-6d | %-6d |\n", x->code, x->start, x->end);
    	x->trotation=x->end-x->ta;
    	x->tattente=x->trotation-x->te;
    	x = x->suiv;
	}
	printf("+----------------------+--------+--------+\n");


	float TrotationMoy=0;
	float TattenteMoy=0;
	int nb=0;
	x = aff;
	while (x != NULL) {
		nb++;
		TrotationMoy+= x->trotation;
	    TattenteMoy+= x->tattente;
	    x = x->suiv;
	}
	TrotationMoy=TrotationMoy/nb;
	TattenteMoy=TattenteMoy/nb;
	printf("Average rotation time=%.2f   Average waiting time=%.2f\n",TrotationMoy,TattenteMoy);
}

/*
 int main()
 {
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    basicfifo(p);
   	return 0;
}*/
