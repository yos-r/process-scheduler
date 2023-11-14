#include "../misc.h"

// #include <stdio.h>
// #include "../genListFile.c"

// typedef struct QueueNode {
//     processus *process;
//     struct QueueNode *next;
// } QueueNode;

// typedef struct {
//     QueueNode *front;
//     QueueNode *rear;
// } Queue;

// // initialize an empty queue
// Queue* createQueue() {
//     Queue *queue = (Queue*)malloc(sizeof(Queue));
//     if (!queue) {
//         fprintf(stderr, "Memory allocation error\n");
//         exit(EXIT_FAILURE);
//     }
//     queue->front = queue->rear = NULL;
//     return queue;
// }

// // add a process to the queue
// void enqueue(Queue *queue, processus *process) {
//     QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
//     if (!newNode) {
//         fprintf(stderr, "Memory allocation error\n");
//         exit(EXIT_FAILURE);
//     }
//     newNode->process = process;
//     newNode->next = NULL;

//     if (queue->rear == NULL) {
//         queue->front = queue->rear = newNode;
//     } else {
//         queue->rear->next = newNode;
//         queue->rear = newNode;
//     }
// }

// // remove and return a process from the queue
// processus* dequeue(Queue *queue) {
//     if (queue->front == NULL) {
//         return NULL;  // Queue is empty
//     }

//     QueueNode *temp = queue->front;
//     processus *process = temp->process;

//     queue->front = temp->next;
//     if (queue->front == NULL) {
//         queue->rear = NULL;  // Last element removed
//     }

//     free(temp);
//     return process;
// }


// // sort the processes by date of arrival
// processus* sortProcesses(processus *head) {
//     processus *current = head;
//     processus *sorted = NULL;

//     while (current != NULL) {
//         processus *next = current->suiv;

//         if (sorted == NULL || current->date_arr < sorted->date_arr) {
//             current->suiv = sorted;
//             sorted = current;
//         } else {
//             processus *sortCurr = sorted;
//             while (sortCurr->suiv != NULL && current->date_arr > sortCurr->suiv->date_arr) {
//                 sortCurr = sortCurr->suiv;
//             }
//             current->suiv = sortCurr->suiv;
//             sortCurr->suiv = current;
//         }

//         current = next;
//     }
//     current=sorted;
//     while (current!= NULL){
//         printf("\n process %s arrived at %d ",current->code, current->date_arr);
//         current=current->suiv;
//     }

//     return sorted;
// }


// FIFO scheduling algorithm with a queue
void test(processus *head) {
    Queue *processQueue = createQueue();
    //sort the process
    processus *sortedProcesses = sortProcesses(head);
    processus *current = sortedProcesses;
    int time = 0;  // Simulation time
    int totalExecutionTime = 0;

    printf("\n FIFO Scheduling:\n");

    while (current != NULL || processQueue->front != NULL) {
        // Check if a process arrives at the current time
        while (current != NULL && current->date_arr <= time) {
            printf("t=%d Process %s arrives and is added to queue  \n",current->date_arr, current->code);
            enqueue(processQueue, current);
            current = current->suiv;
        }
        // Execute the process at the front of the queue
        processus *executingProcess = dequeue(processQueue);
        if (executingProcess != NULL) {
            printf("t %d: Executing process %s for %d units\n", time, executingProcess->code, executingProcess->dur_exec_modif_proc);
            time += executingProcess->dur_exec_modif_proc;
            totalExecutionTime += executingProcess->dur_exec_modif_proc;
        } else {
            printf("t= %d: CPU idle\n", time);
            time++;
        }
        // printf(" \n t=%d CPU IS FREE",time);
    }

    printf("Total CPU time is %d\n", totalExecutionTime);
}





// int main()
// {
//     FILE *file = fopen("pcb.txt", "rt");
//     processus *p = enreg_bcp(file);
//     fclose(file);

//     // afficherListe(p);

//     // Call the FIFO scheduling algorithm
//     // sortProcesses(p);
//     fifo_scheduling(p);

//     return 0;
// }