#include "../misc.h"
void multilevel(processus *p)
{
    displayTab(p);
    printf("\nMULTILEVEL Scheduling: \n\n");
    int executedTime = 0;
    viewProcess *view = NULL;
    viewProcess *q = view;
    int countP = countProcesses(p);
    Process *processTable = convertListToTable(p, countP);
    int quantum;
    do
    {
        printf("\nEnter the quantum value : ");
        scanf("%d", &quantum);
        if (quantum <= 0)
        {
            printf("Invalid input. Please enter a positive integer >0.\n");
        }
    } while (quantum <= 0);
    qsort(processTable, countP, sizeof(Process), compareArrivalTime);
    int time = 0;
    int i;
    int highestPriorityPosition = -1;
    int highestPriority = 0;
    while (!allProcessesCompleted(processTable, countP))
    {
        highestPriorityPosition = -1;
        for (i = 0; i < countP; ++i)
        {

            if (processTable[i].dur_exec > 0 && processTable[i].date_arr <= time && processTable[i].priorite > highestPriority)
            {
                highestPriorityPosition = i;
                highestPriority = processTable[i].priorite;
            }
        }
        if (highestPriorityPosition == -1)
        {
            for (i = 0; i < countP; ++i)
            {
                if (processTable[i].dur_exec > 0 && processTable[i].date_arr <= time && processTable[i].priorite == highestPriority)
                {
                    highestPriorityPosition = i;
                    break;
                }
            }
        }

        if (highestPriorityPosition != -1)
        {

            printf("t= %d: executing process %s \n", time, processTable[highestPriorityPosition].code);
            if (q == NULL || strcmp(q->code, processTable[highestPriorityPosition].code) != 0)
            {
                viewProcess *i = malloc(sizeof(viewProcess));
                strcpy(i->code, processTable[highestPriorityPosition].code);
                i->ta = processTable[highestPriorityPosition].date_arr;
                i->te = processTable[highestPriorityPosition].dur_exec;
                i->start = time;
                i->end = time + 1;
                i->suiv = NULL;
                executedTime = 1;
                if (view == NULL)
                {
                    view = i;
                    q = i;
                }
                else
                {
                    q->suiv = i;
                    q = i;
                }
            }
            else
            {
                executedTime++;
                q->end++;
            }
            processTable[highestPriorityPosition].dur_exec--;
            if (processTable[highestPriorityPosition].dur_exec <= 0)
            {
                printf("t=%d , process %s is done with execution\n", time, processTable[highestPriorityPosition].code);
                highestPriority = 0;
            }
            if (processTable[highestPriorityPosition].priorite == highestPriority && executedTime == quantum && processTable[highestPriorityPosition].dur_exec > 0)
            {
                Process temp = processTable[highestPriorityPosition];
                for (i = highestPriorityPosition; i < countP - 1; ++i)
                {
                    processTable[i] = processTable[i + 1];
                }
                processTable[countP - 1] = temp;
            }
        }
        else
        {
            printf("t= %d: CPU idle\n", time);
        }
        time++;
    }

    free(processTable);
    GantAndStatistic(view);
}
/*
int main()
{
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    fclose(file);
    multilevel(p);
    return 0;
}
*/