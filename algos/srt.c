#include <stdio.h>
#include "../genListFile.c"

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
        printf("\n process %s arrived at %d ", current->code, current->date_arr);
        current = current->suiv;
    }

    return sorted;
}

void sortByDurExecNonModifProcQueue(Queue *queue)
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
            if (ptr1->process->dur_exec_non_modif_proc > ptr1->next->process->dur_exec_non_modif_proc)
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
void testSortQueue()
{
    Queue *readyQueue = createQueue();
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);

    processus *q = p;
    while (q != NULL)
    {
        enqueue(readyQueue, q);
        q = q->suiv;
    }
    // queue *test = readyQueue;
    sortByDurExecNonModifProcQueue(readyQueue);
    QueueNode *first = readyQueue->front;
    while (first != NULL)
    {
        printf("\nprocess at queue number %s w/ exec time %d \n", first->process->code,first->process->dur_exec_non_modif_proc);
        first = first->next;
    }
}
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

int main()
{
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    // afficherListe(p);
    // Call the FIFO scheduling algorithm
    // sortProcesses(p);
    srtf(p);
    // testSortQueue();
    return 0;
}