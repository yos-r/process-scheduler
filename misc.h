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
    float trotation;
    float tattente;
    struct affP *suiv;
} affichP;



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
            processus *i = malloc(sizeof(processus));
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

void entete()
{
    
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(218);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(194);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(191);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf("  Process");
    printf(" ");
    putchar(179);
    printf(" ");
    printf("Date of arr");
    putchar(179);
    printf(" ");
    printf("Executi time ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Priority ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(195);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(180);
}

void milieu(char *a, int b, int c, int d)
{
    int aa = strlen(a);
    int bb;
    int cc;
    int dd;
    int i;

    if (b >= 10)
        bb = 2;
    else
        bb = 1;

    if (c >= 10)
        cc = 2;
    else
        cc = 1;

    if (d >= 10)
        dd = 2;
    else
        dd = 1;

    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for (i = 1; i <= (9 - aa) / 2; i++)
        printf(" ");
    printf("%s", a);
    for (i = 1; i <= ((9 - aa) / 2) + (9 - aa) % 2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");

    if (bb == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", b);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 4; i++)
            printf(" ");
        printf("%d", b);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if (cc == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", c);
        for (i = 1; i <= 6; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", c);
        for (i = 1; i <= 5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if (dd == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", d);
        for (i = 1; i <= 5; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", d);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }
    printf(" ");
    putchar(179);
    printf(" ");
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(195);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(197);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(180);
}
void fin_tab(char *a, int b, int c, int d)
{
    int aa = strlen(a), i;
    int bb;
    int cc;
    int dd;
    if (b >= 10)
        bb = 2;
    else
        bb = 1;

    if (c >= 10)
        cc = 2;
    else
        cc = 1;

    if (d >= 10)
        dd = 2;
    else
        dd = 1;

    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for (i = 1; i <= (9 - aa) / 2; i++)
        printf(" ");
    printf("%s", a);
    for (i = 1; i <= ((9 - aa) / 2) + (9 - aa) % 2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");

    if (bb == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", b);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 4; i++)
            printf(" ");
        printf("%d", b);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if (cc == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", c);
        for (i = 1; i <= 6; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", c);
        for (i = 1; i <= 5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if (dd == 1)
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", d);
        for (i = 1; i <= 5; i++)
            printf(" ");
    }
    else
    {
        for (i = 1; i <= 5; i++)
            printf(" ");
        printf("%d", d);
        for (i = 1; i <= 4; i++)
            printf(" ");
    }
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(192);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(193);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(196);
    putchar(217);
}

void showFile(int nb)
{
    printf("\n\t\t               List of file data  : \n");
    printf("\n");
    entete();
    FILE *file = fopen("pcb.txt", "r");
    if (file == NULL)
    {
        perror("Erreur");
        //used to be getch() for windows
        getc;
    }
    char ligne[100];
    char id[10];
    char ids[100][10];
    int i = 0, x, y, z;
    while (fgets(ligne, sizeof(ligne), file) != NULL)
    {
        if (sscanf(ligne, "%[^;];%d;%d;%d\n", id, &x, &y, &z) == 4)
        {
            i++;
            if (i != nb)
            {
                printf("\n");
                milieu(id, x, y, z);
            }
            else
            {
                printf("\n");
                fin_tab(id, x, y, z);
            }
        }
    }
}



void displayTab(processus *tab)
{
    processus *current = tab;
    printf("\n");
    entete();
    int i = 0, x, y, z;
    char *id;
    while (current != NULL)
    {
        id = current->code;
        x = current->date_arr;
        y = current->dur_exec_non_modif_proc;
        z = current->priorite;
        printf("\n");
        if (current->suiv != NULL)
            milieu(id, x, y, z);
        else
            fin_tab(id, x, y, z);
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
            if (ptr1->process->priorite < ptr1->next->process->priorite)
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