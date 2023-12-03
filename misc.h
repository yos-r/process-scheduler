// deals w/ queues, structs, file formatting
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#ifndef COMMON_H
#define COMMON_H

// #include "genListFile.c"
// #include "displayAll.h"

typedef struct affichP
{
    char code[30];
    int ta;
    int te;
    int start; 
    int end;
    int trotation;
    int tattente;
    struct affichP *suiv;
} affichP;
affichP* LastOcProcessus(affichP* head, char* code) {
    affichP* last = NULL;
    affichP* courant = head;
    while (courant != NULL) {
        if (strcmp(courant->code, code) == 0) {
            last = courant;
        }
        courant = courant->suiv;
    }
    return last;
}
bool existeProcessus(affichP* head, char* code) {
    affichP* courant = head;
    while (courant != NULL) {
        if (strcmp(courant->code,code) == 0) {
            return true;
        }
        courant = courant->suiv;
    }
    return false;
}
affichP* insererProcessus(affichP* head, affichP* x) {
    affichP* newProcessus = (affichP*) malloc(sizeof(affichP));
    if (newProcessus == NULL) {
        return head;
    }
    strcpy(newProcessus->code, x->code);
    newProcessus->trotation = x->trotation;
    newProcessus->tattente = x->tattente;
    newProcessus->suiv = head;
    return newProcessus;
}
void GantAndStatistic(affichP *aff)
{
affichP *x = aff;
    affichP *last=NULL;
    affichP *used=NULL;
	printf("+----------------------+--------+--------+\n");
	printf("|       Process        | Start  |  End   |\n");
	printf("+----------------------+--------+--------+\n");
	while (x != NULL) {
   	    printf("| %-20s | %-6d | %-6d |\n", x->code, x->start, x->end);
        if(existeProcessus(used,x->code)==false)
        {
        last=LastOcProcessus(aff,x->code);
    	last->trotation=last->end-last->ta;
    	last->tattente=last->trotation-last->te;
        used=insererProcessus(used,last);
       }
        x = x->suiv;
	}
	printf("+----------------------+--------+--------+\n");
	float TrotationMoy=0;
	float TattenteMoy=0;
	int nb=0;
	x = used;
	while (x != NULL) {
		nb++;
		TrotationMoy+= x->trotation;
	    TattenteMoy+= x->tattente;
        printf("%s: rotation time=%d  ,waiting time=%d \n",x->code,x->trotation,x->tattente);
	    x = x->suiv;
	}
	TrotationMoy=TrotationMoy/nb;
	TattenteMoy=TattenteMoy/nb;
	printf("Average rotation time=%.2f   Average waiting time=%.2f\n",TrotationMoy,TattenteMoy);
}
//function that generates a random pcb.txt
void generateFile() {
    FILE *f = fopen("pcb.txt", "w");

    if (f == NULL) {
        perror("Erreur");
        return;
    }
    int maxProcesses;
    do{
        printf("Enter the maximum number of processes: ");
        scanf("%d", &maxProcesses);
        if (maxProcesses <= 0) {
        printf("Invalid input. Please enter a positive integer >0.\n");
        }
    }while (maxProcesses<=0);
    int maxTA;
    do{
        printf("Enter the maximum number of TA: ");
        scanf("%d", &maxTA);
        if (maxTA <= 0) {
        printf("Invalid input. Please enter a positive integer >0.\n");
        }
    }while (maxTA<=0);
    int maxTE;
    do{
        printf("Enter the maximum number of TE: ");
        scanf("%d", &maxTE);
        if (maxTE <= 0) {
        printf("Invalid input. Please enter a positive integer >0.\n");
        }
    }while (maxTE<=0);
    int maxPRIO;
    do{
        printf("Enter the maximum number of Priority: ");
        scanf("%d", &maxPRIO);
        if (maxPRIO <= 0) {
        printf("Invalid input. Please enter a positive integer >0.\n");
        }
    }while (maxPRIO<=0);
    srand(time(NULL));
	int i;
    int n=(rand()%maxProcesses)+1;
    printf("%d processes generated \n",n); //print the number of processes randomly generated
    for (i = 0; i < n; i++) {
   		int x=(rand()%maxTA); 
        int y=(rand()%maxTE)+1;
        int z=(rand()%maxPRIO)+1;
        fprintf(f,"p%d;%d;%d;%d\n",i,x,y,z);
    }
    fclose(f);
}

typedef struct processus
{
    char code[30];
    int date_arr;                // very important
    int dur_exec_non_modif_proc; // very important
    int dur_exec_modif_proc;     // useful for checking if process is done
    int priorite;                // very imporant
    // metrics :
    int dur_pret; // total waiting time !
    int debut;
    int fin;
    int last_wait; 

    int dur_blq; // might omit
    int turn;    // might omit
    int etat;    // is it needed?
    struct processus *suiv;
} processus;

processus *enreg_bcp(FILE *file)
{
    processus *p = NULL;
    int date_arr, dur_exec_non_modif_proc, priorite;
    char *fileRead;
    char ligne[100];
    char id[30];
    char *part;
    while (fgets(ligne, sizeof(ligne), file) != NULL)
    {
        if (sscanf(ligne, "%[^;];%d;%d;%d\n", id, &date_arr, &dur_exec_non_modif_proc, &priorite) == 4)
        {
            processus *i = (processus *) malloc(sizeof(processus));
            strcpy(i->code, id);

            i->date_arr = date_arr;
            i->last_wait=date_arr;
            i->dur_exec_non_modif_proc = dur_exec_non_modif_proc;
            i->dur_exec_modif_proc = dur_exec_non_modif_proc;
            i->priorite = priorite;
            i->etat = 0;
            i->dur_pret = 0;
            i->dur_blq = 0;
            i->suiv = p;
            i->fin=-1;
            p = i;
        }
    }
    return p;
}
//test
void afficherListe(processus *head)
{
    struct processus *i = head;
    while (i != NULL)
    {
        printf("Code: %s\n", i->code);                                                           // cool
        printf("date of arrival %d\n", i->date_arr);                                             // cool
        printf("execution time: %d\n", i->dur_exec_non_modif_proc); // cool
        printf("time left %d\n", i->dur_exec_modif_proc);         // cool but need to rename
        printf("priority: %d\n", i->priorite);                                                   // cool
        // printf("Duree de pret: %d\n", i->dur_pret);                                              // useful for metrics but hasn't been used yet
        // printf("Duree de blocage: %d\n", i->dur_blq);                                            // might omit
        printf("finish time: %d\n", i->fin);  
        // printf("finish time: %d\n", i->);                                                           // might omit
        printf("\n");
        i = i->suiv;
    }
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
        y = current->dur_exec_non_modif_proc;
        z = current->priorite;
        printf("| %-10s | %-10d | %-25d | %-8d |\n", id, x, y, z);
        if (current->suiv == NULL)
            printf("+------------+------------+---------------------------+----------+\n");
        current = current->suiv;
    }
}
// types to deal w/ queues: node, queue, creation, insertion and deletion
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

// initialize an empty queue
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

// add a process to the queue
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
        return NULL; // Queue is empty
    }

    QueueNode *temp = queue->front;
    processus *process = temp->process;

    queue->front = temp->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL; // Last element removed
    }

    free(temp);
    return process;
}

//MULTILEVEL:check if processes in the ready queue share the top priority: will need round robin 
bool checkMulti(Queue *queue)
{
    QueueNode *current = queue->front; // get the front
    int topPriority = current->process->priorite;
    if (current->next != NULL && current->next->process->priorite == topPriority)
    {
        printf("\n will need roundrobin between processes of priority %d \n", topPriority);
        return true;
    } // need round robin
    else
        return false;
}
// build list of these processes : | need to order take into account last time it was paused
processus *buildList(Queue *queue)
{
    // Check if the queue is empty
    if (queue == NULL || queue->front == NULL)
    {
        return NULL;
    }

    int topPriority = queue->front->process->priorite;
    QueueNode *current = queue->front;

    // Create the head of the new linked list
    processus *newListHead = NULL;
    processus *newListTail = NULL;

    while (current != NULL && current->process->priorite == topPriority)
    {
        // Create a new processus node
        processus *newNode = (processus *)malloc(sizeof(processus));
        if (!newNode)
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        // copy the processus data
        memcpy(newNode, current->process, sizeof(processus));
        newNode->suiv = NULL;

        // Add the new node to the linked list
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
// simple funct that orders processes by date of arrival.
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
        // printf("\n process %s arrived at %d and has %d units to execute", current->code, current->date_arr, current->dur_exec_modif_proc);
        current = current->suiv;
    }
    displayTab(sorted);
    return sorted;
}

//display display of queue (based on order of arrival)
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
// queue display for premptive priority
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
// queue display for roundrobin and fifo (sorted by order of arrival)
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

//functions to sort the ready queue (by srt or by priority)
void sortByDurExecModifProcQueue(Queue *queue)
{
    int swapped;
    QueueNode *ptr1;
    QueueNode *lptr = NULL;

    /* Checking for an empty queue */
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
                // Swap the nodes
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
/*
void sortByPriorityQueue(Queue *queue)
{
    int swapped;
    QueueNode *ptr1;
    QueueNode *lptr = NULL;

    // checking for an empty queue
    if (queue->front == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = queue->front;

        while (ptr1->next != lptr)
        {
            if (ptr1->process->priorite <= ptr1->next->process->priorite)
            {
                // Swap the nodes
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
*/
void sortByPriorityQueue(Queue *queue)
{
    // checking for an empty queue or a single element
    if (queue->front == NULL || queue->front->next == NULL)
        return;

    QueueNode *current, *compare, *min;

    for (current = queue->front; current->next != NULL; current = current->next)
    {
        min = current;

        // Find the minimum element in the unsorted part of the list
        for (compare = current->next; compare != NULL; compare = compare->next)
        {
            if (compare->process->priorite >= min->process->priorite)
            {
                min = compare;
            }
        }

        // Swap the found minimum element with the current element
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

    /* Checking for an empty queue */
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
                // Swap the nodes
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
#endif