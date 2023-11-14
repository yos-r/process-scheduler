#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct processus
{
    char code[30];
    int date_arr;
    int dur_exec_non_modif_proc;
    int dur_exec_modif_proc;
    int priorite;
    int dur_pret;
    int dur_blq;
    int turn;
    int etat;
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
            i->dur_exec_non_modif_proc = dur_exec_non_modif_proc;
            i->dur_exec_modif_proc = dur_exec_non_modif_proc;
            i->priorite = priorite;
            i->etat = 0;
            i->dur_pret = 0;
            i->dur_blq = 0;
            i->suiv = p;
            p = i;
        }
    }
    return p;
}

void afficherListe(processus *head)
{
    struct processus *i = head;
    while (i != NULL)
    {
        printf("Code: %s\n", i->code); //cool
        printf("Date d'arrivee: %d\n", i->date_arr); //cool
        printf("Duree d'execution non modifiee du processus: %d\n", i->dur_exec_non_modif_proc); //cool
        printf("Duree d'execution modifiee du processus: %d\n", i->dur_exec_modif_proc); //cool but need to rename
        printf("Priorite: %d\n", i->priorite); //cool
        printf("Duree de pret: %d\n", i->dur_pret); // useful for metrics but hasn't been used yet
        printf("Duree de blocage: %d\n", i->dur_blq); //might omit
        printf("Etat: %d\n", i->etat); // might omit
        printf("\n");
        i = i->suiv;
    }
}

int main()
{
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    afficherListe(p);
    return 0;
}
