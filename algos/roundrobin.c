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

void rr_robin(processus *head, int quantum)
{
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;

    Queue *readyQueue = createQueue();
    int time = 0; // Simulation time
    printf("\nRound Robin Scheduling with quantum equal to: %d\n", quantum);

    while (current != NULL || readyQueue->front != NULL)
    {
        // Check if a process arrives at the current time
        while (current != NULL && current->date_arr <= time)
        {
            printf("Process %s arrived at time %d\n", current->code, time);
            enqueue(readyQueue, current);
            current = current->suiv;
        }

        // Execute the process at the front of the ready queue
        processus *executingProcess = dequeue(readyQueue);
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

            // Update process state
            // executingProcess->dur_exec_modif_proc -= quantum;
            // time += quantum;

            if (executingProcess->dur_exec_modif_proc <= 0)
            {
                printf("Process %s is done with execution\n", executingProcess->code);
                // Update process state (if needed)
                // executingProcess->etat = 1;  // Process is completed
                // executingProcess->turn = time - executingProcess->date_arr;
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

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <quantum>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int quantum = atoi(argv[1]); // Convert the command-line argument to an integer
    if (quantum <= 0)
    {
        fprintf(stderr, "Quantum must be a positive integer\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);


    rr_robin(p, quantum);

    return 0;
}