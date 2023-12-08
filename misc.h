#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#ifndef COMMON_H
#define COMMON_H
typedef struct processus
{
    char code[20];
    int date_arr;
    int dur_exec;
    int dur_exec_modif_proc;
    int priorite;
    int last_wait;
    struct processus *suiv;
} processus;

typedef struct Process
{
    char code[20];
    int date_arr;
    int dur_exec;
    int priorite;
} Process;

typedef struct viewProcess
{
    char code[20];
    int ta;
    int te;
    int start;
    int end;
    int trotation;
    int tattente;
    struct viewProcess *suiv;
} viewProcess;

typedef struct QueueNode
{
    processus *process;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

viewProcess *LastOcProcessus(viewProcess *head, char *code)
{
    viewProcess *last = NULL;
    viewProcess *current = head;
    while (current != NULL)
    {
        if (strcmp(current->code, code) == 0)
        {
            last = current;
        }
        current = current->suiv;
    }
    return last;
}
bool existeProcessus(viewProcess *head, char *code)
{
    viewProcess *current = head;
    while (current != NULL)
    {
        if (strcmp(current->code, code) == 0)
        {
            return true;
        }
        current = current->suiv;
    }
    return false;
}
viewProcess *inseretProcess(viewProcess *head, viewProcess *x)
{
    viewProcess *newProcessus = (viewProcess *)malloc(sizeof(viewProcess));
    if (newProcessus == NULL)
    {
        return head;
    }
    strcpy(newProcessus->code, x->code);
    newProcessus->trotation = x->trotation;
    newProcessus->tattente = x->tattente;
    newProcessus->suiv = head;
    return newProcessus;
}
void GantAndStatistic(viewProcess *view)
{
    viewProcess *x = view;
    viewProcess *last = NULL;
    viewProcess *used = NULL;
    printf("+----------------------+--------+--------+\n");
    printf("|       Process        | Start  |  End   |\n");
    printf("+----------------------+--------+--------+\n");
    while (x != NULL)
    {
        printf("| %-20s | %-6d | %-6d |\n", x->code, x->start, x->end);
        if (existeProcessus(used, x->code) == false)
        {
            last = LastOcProcessus(view, x->code);
            last->trotation = last->end - last->ta;
            last->tattente = last->trotation - last->te;
            used = inseretProcess(used, last);
        }
        x = x->suiv;
    }
    printf("+----------------------+--------+--------+\n");
    float TrotationMoy = 0;
    float TattenteMoy = 0;
    int nb = 0;
    x = used;
    while (x != NULL)
    {
        nb++;
        TrotationMoy += x->trotation;
        TattenteMoy += x->tattente;
        printf("%s: rotation time=%d  ,waiting time=%d \n", x->code, x->trotation, x->tattente);
        x = x->suiv;
    }
    TrotationMoy = TrotationMoy / nb;
    TattenteMoy = TattenteMoy / nb;
    printf("Average rotation time=%.2f   Average waiting time=%.2f\n", TrotationMoy, TattenteMoy);
}
//verif file
bool verifFile() {
    FILE *file = fopen("pcb.txt", "r");
    if (file == NULL) {
        perror("Erreur");
        // getch();
        getc;
        return false;
    }
    char ligne[100]; 
	char id[10]; 
    char ids[100][10]; 
    int id_count=0;
	int i,x, y, z;
    while (fgets(ligne, sizeof(ligne), file) != NULL) {
        if (sscanf(ligne,"%[^;];%d;%d;%d\n", id, &x, &y, &z)==4) {
        	printf("%s;%d;%d;%d\n",id,x,y,z);   	
            for (i = 0; i < id_count; i++) {
                if (strcmp(id, ids[i]) == 0) {
                    fclose(file);
                    return false;  //id n'est pas unique
                }
            }
            strcpy(ids[id_count], id);
            id_count++;
        } 
		
    }
    if(id_count==0)
    	{ 
            printf("Your file is empty !!");
            getc;
            return false;
        }
    fclose(file);
    return true;  
}


void generateFile()
{
    FILE *f = fopen("pcb.txt", "w");

    // if (f == NULL)
    // {
    //     printf("Erreur");
    //     return;
    // }
    // int maxProcesses;
    // do
    // {
    //     printf("Enter the maximum number of processes: ");
    //     scanf("%d", &maxProcesses);
    //     if (maxProcesses <= 0)
    //     {
    //         printf("Invalid input. Please enter a positive integer >0.\n");
    //     }
    // } while (maxProcesses <= 0);
    // int maxTA;
    // do
    // {
    //     printf("Enter the maximum number of Arrival Time: ");
    //     scanf("%d", &maxTA);
    //     if (maxTA <= 0)
    //     {
    //         printf("Invalid input. Please enter a positive integer >0.\n");
    //     }
    // } while (maxTA <= 0);
    // int maxTE;
    // do
    // {
    //     printf("Enter the maximum number of Execution Time: ");
    //     scanf("%d", &maxTE);
    //     if (maxTE <= 0)
    //     {
    //         printf("Invalid input. Please enter a positive integer >0.\n");
    //     }
    // } while (maxTE <= 0);
    // int maxPRIO;
    // do
    // {
    //     printf("Enter the maximum number of Priority: ");
    //     scanf("%d", &maxPRIO);
    //     if (maxPRIO <= 0)
    //     {
    //         printf("Invalid input. Please enter a positive integer >0.\n");
    //     }
    // } while (maxPRIO <= 0);
    srand(time(NULL));
    int i;
    int n = (rand() % 30) + 1;
    printf("%d processes generated \n", n);
    for (i = 0; i < n; i++)
    {
        int TA = (rand() % 10);
        int TE = (rand() % 30) + 1;
        int PRIO = (rand() % 5) + 1;
        fprintf(f, "p%d;%d;%d;%d\n", i, TA, TE, PRIO);
    }
    fclose(f);
}
void generateFileParam(int maxNumber, int maxArrival, int maxExec, int maxPrio)
{
    FILE *f = fopen("pcb.txt", "w");

    srand(time(NULL));
    int i;
    int n = (rand() % maxNumber) + 1;
    printf("%d processes generated \n", n);
    for (i = 0; i < n; i++)
    {
        int TA = (rand() % maxArrival);
        int TE = (rand() % maxExec) + 1;
        int PRIO = (rand() % maxPrio) + 1;
        fprintf(f, "p%d;%d;%d;%d\n", i, TA, TE, PRIO);
    }
    fclose(f);
}

processus *enreg_pcb(FILE *file)
{
    processus *p = NULL;
    int date_arr, dur_exec, priorite;
    char *fileRead;
    char ligne[100];
    char id[20];
    while (fgets(ligne, sizeof(ligne), file) != NULL)
    {
        if (sscanf(ligne, "%[^;];%d;%d;%d\n", id, &date_arr, &dur_exec, &priorite) == 4)
        {
            processus *i = (processus *)malloc(sizeof(processus));
            strcpy(i->code, id);
            i->date_arr = date_arr;
            i->last_wait = date_arr;
            i->dur_exec = dur_exec;
            i->dur_exec_modif_proc = dur_exec;
            i->priorite = priorite;
            i->suiv = p;
            p = i;
        }
    }
    return p;
}

void displayTab(processus *tab)
{
    processus *current = tab;
    printf("\n");
    printf("+------------+------------+---------------------------+----------+\n");
    printf("| %-10s | %-10s | %-25s | %-8s |\n", "Process", "Date Arr", "Execution Time", "Priority");
    printf("+------------+------------+---------------------------+----------+\n");
    int i = 0, x, y, z;
    char *id;
    while (current != NULL)
    {
        id = current->code;
        x = current->date_arr;
        y = current->dur_exec;
        z = current->priorite;
        printf("| %-10s | %-10d | %-25d | %-8d |\n", id, x, y, z);
        if (current->suiv == NULL)
            printf("+------------+------------+---------------------------+----------+\n");
        current = current->suiv;
    }
}

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, processus *process)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->process = process;
    newNode->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}
processus *dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }

    QueueNode *temp = queue->front;
    processus *process = temp->process;

    queue->front = temp->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    return process;
}

processus *buildList(Queue *queue)
{
    if (queue == NULL || queue->front == NULL)
    {
        return NULL;
    }

    int topPriority = queue->front->process->priorite;
    QueueNode *current = queue->front;

    processus *newListHead = NULL;
    processus *newListTail = NULL;

    while (current != NULL && current->process->priorite == topPriority)
    {
        processus *newNode = (processus *)malloc(sizeof(processus));
        if (!newNode)
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        memcpy(newNode, current->process, sizeof(processus));
        newNode->suiv = NULL;

        if (newListHead == NULL)
        {
            newListHead = newListTail = newNode;
        }
        else
        {
            newListTail->suiv = newNode;
            newListTail = newNode;
        }
        current = current->next;
    }
    return newListHead;
}

processus *sortProcesses(processus *head)
{
    processus *current = head;
    processus *sorted = NULL;

    while (current != NULL)
    {
        processus *next = current->suiv;

        if (sorted == NULL || current->date_arr < sorted->date_arr)
        {
            current->suiv = sorted;
            sorted = current;
        }
        else
        {
            processus *sortCurr = sorted;
            while (sortCurr->suiv != NULL && current->date_arr > sortCurr->suiv->date_arr)
            {
                sortCurr = sortCurr->suiv;
            }
            current->suiv = sortCurr->suiv;
            sortCurr->suiv = current;
        }

        current = next;
    }
    current = sorted;
    while (current != NULL)
    {
        current = current->suiv;
    }
    displayTab(sorted);
    return sorted;
}

void stateOfQueue(Queue *queue)
{
    QueueNode *current = queue->front;

    printf("stateOfQueue: |");
    while (current != NULL)
    {
        printf(" %s (%d remaining) |", current->process->code, current->process->dur_exec_modif_proc);
        current = current->next;
    }
    printf("\n");
}

void stateOfQueue3(Queue *queue)
{
    QueueNode *current = queue->front;

    printf("stateOfQueue: |");
    while (current != NULL)
    {
        printf(" %s (%d) |", current->process->code, current->process->priorite);
        current = current->next;
    }
    printf("\n");
}

void stateOfQueue2(Queue *queue)
{
    QueueNode *current = queue->front;

    printf("stateOfQueue: |");
    while (current != NULL)
    {
        printf(" %s |", current->process->code);
        current = current->next;
    }
    printf("\n");
}

void sortByDurExecModifProcQueue(Queue *queue)
{
    int swapped;
    QueueNode *ptr1;
    QueueNode *lptr = NULL;

    if (queue->front == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = queue->front;

        while (ptr1->next != lptr)
        {
            if (ptr1->process->dur_exec_modif_proc > ptr1->next->process->dur_exec_modif_proc)
            {
                processus *tempProcess = ptr1->process;
                ptr1->process = ptr1->next->process;
                ptr1->next->process = tempProcess;

                swapped = 1;
            }
            else
            {
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}

void sortByPriorityQueue(Queue *queue)
{
    if (queue->front == NULL || queue->front->next == NULL)
        return;

    QueueNode *current, *compare, *min;

    for (current = queue->front; current->next != NULL; current = current->next)
    {
        min = current;
        for (compare = current->next; compare != NULL; compare = compare->next)
        {
            if (compare->process->priorite >= min->process->priorite)
            {
                min = compare;
            }
        }

        if (min != current)
        {
            processus *tempProcess = current->process;
            current->process = min->process;
            min->process = tempProcess;
        }
    }
}

void sortByLastWait(Queue *queue)
{
    int swapped;
    QueueNode *ptr1;
    QueueNode *lptr = NULL;

    if (queue->front == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = queue->front;

        while (ptr1->next != lptr)
        {
            if (ptr1->process->last_wait > ptr1->next->process->last_wait)
            {
                processus *tempProcess = ptr1->process;
                ptr1->process = ptr1->next->process;
                ptr1->next->process = tempProcess;

                swapped = 1;
            }
            else
            {
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}

int compareArrivalTime(const void *a, const void *b) {
    return ((const Process *)a)->date_arr - ((const Process *)b)->date_arr;
}
Process *convertListToTable(processus *head, int countP)
{
    Process *processTable = (Process *)malloc(countP * sizeof(Process));
    int i;
    processus *current = head;

    for (i = 0; i < countP && current != NULL; ++i)
    {
        snprintf(processTable[i].code, sizeof(processTable[i].code), "%s", current->code);
        processTable[i].date_arr = current->date_arr;
        processTable[i].dur_exec = current->dur_exec;
        processTable[i].priorite = current->priorite;
        current = current->suiv;
    }
    return processTable;
}
int allProcessesCompleted(Process *p, int countP)
{
    int i;
    for (i = 0; i < countP; ++i)
    {
        if (p[i].dur_exec > 0)
        {
            return 0;
        }
    }
    return 1;
}

int countProcesses(processus *head)
{
    int count = 0;
    processus *current = head;

    while (current != NULL)
    {
        count++;
        current = current->suiv;
    }
    return count;
}

#endif
