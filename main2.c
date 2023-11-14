#include <stdio.h>
#include <stdlib.h>
#include "genListFile.c" //file  generates the list
#include "misc.c"        // file w/ queues+ sorting functions
// including algorithms
#include "algos/roundrobin.c"
#include "algos/basicfifo.c"
#include "algos/srt.c"

#include <string.h>
#include <ctype.h>

#define maxim 500     // the maximum stop time
#define meth_affich 1 // to choose the display method of the grill either 1 or 2

void titre(void)
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                     ~~ (❁´◡`❁) ~~                    |\n");
    printf("                |                PROCESS SCHEDULER APPLICATION              |\n");
    printf("                 --------------------------------------------------------\n");
}

int main()
{
    int nbrproc, i, n;
    int boucle, choix, decalge, existe, Qt;
    char rep;
    int db, fn, qs, rest, enreg_don = 0;
    char nom_fich[30], N[12], qt[12];
    FILE *pntr;
    processus *bcp, *T;

    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);

    // info res[maxim];
    // code_proc cod[20];

    if (meth_affich == 1)
    {
        decalge = 38;
    }
    else
    {
        decalge = 60;
    }

    titre();

    // char r = getchar();
    boucle = 1;
    printf(" \n                             -------------------------------\n");
    printf("                            |            MAIN MENU          |\n");
    printf("                             -------------------------------\n");
    printf("                            |   1 . Loading data            |\n");
    ;
    printf("                            |   2 . List of data            |\n");
    ;
    printf("                            |   3 . Choice of algorithm     |\n");
    printf("                            |   4 . Exit                    |\n");
    printf("                             -------------------------------\n");

    do
    {
        printf("\t\t\t\t\t your choice : ");
        rep = getchar();

        if (rep != '1' && rep != '2' && rep != '3' && rep != '4')
        {
            printf("\nPlease make a choice between 1 and 4 !!\n");
            boucle = 1;
        }
        else
        {
            boucle = 0;
            printf("\033[2J\033[H");
        }
    } while (boucle == 1);
    do
    {
        boucle = 1;
        if (rep == '3')
        {
            // printf("\n executing basic FIFO from file \n");
            // fifo_scheduling(p);

            // printf("\n executing Round robin w/ quantum =2 from file \n");
            // rr_robin(p, 2);

            printf("\n executing SRT w/ quantum =3 from file \n");
            srtf(p);

            boucle = 0;
        }
    } while (boucle == 1);
    // printf("\033[2J\033[H");
    return 0;
}