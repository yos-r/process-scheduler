#include <stdio.h>
#include <conio.h> // doesn't work on linux
#include <stdlib.h>

// #include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define maxim 500 //the maximum stop time
#define meth_affich 1 //to choose the display method of the grill either 1 or 2

typedef struct comment
{
    int elu;
    int pret;
    int ent_sor;
    int blq;
}
comment;

typedef struct processus
{
    char code[30];
    int date_arr;
    int dur_exec;
    int dur_exec_modif_proc;
    int dur_non_modif_es;
    int dur_modif_es;
    int priorite; 
    int dur_pret;
    int dur_blq;
    int turn;
    int etat;
    comment cmt[maxim];
    struct processus *suiv;//it's a recursive structure which consists in declaring a pointer having the same parameters note name and pointer followed
}
processus ;

typedef struct info
{
    int elu;
    int pret;
    int ent_sor;
    int blq;
}
info;

typedef struct code_proc
{
    char cd[30];
}
code_proc;

///////////////////////////////////////////Verification and comparison functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verif_bcp(char nom_fich[])
{
    FILE *p=fopen(nom_fich,"rt");
    int c,cmpt_poin_vrg=0,cmpt_lign=0;
    char ch[100];


    if(p==NULL)
    {
        printf("Unable to open the file!!");
        fclose(p);

        getch();

        return 0;
    }
    else
    {
        p=fopen(nom_fich,"rt");

        while(fgets(ch,sizeof(ch),p)!=NULL)
        {
            if(strcmp(ch,"\n")!=0)
                cmpt_lign++;
        }
        fclose(p);
printf("%d",cmpt_lign);
getch();

        p=fopen(nom_fich,"rt");

        while((c=fgetc(p))!=EOF)
        {
            if(c==';')
            {
                cmpt_poin_vrg++;
            }
            else
            {
                if(c==' ')
                {
                    printf("Your file contains spaces that should be avoided !!");
                    fclose(p);
                    getch();
                    return 0;
                }
            }
        }
        fclose(p);

        if(cmpt_lign==0)
        {
            printf("Your file is empty !!");
            getch();
            return 0;
        }
        else
        {
            if(cmpt_poin_vrg!=(4*cmpt_lign))
            {
                printf("Semicolons are misplaced in this file !!");
                getch();
                return 0;
            }
            else
                return 1;
        }


    }
}

int verif_nombre(char nb[],int a)
{
    char *p  ;
    int erreur=0;

    p=nb;

    while (*p!=NULL)
    {
        if (isdigit(*p))//si le caractere point� est un chiffre digital
        {
            p++;
        }
        else
        {
            erreur=1;
            break;
        }
    }

    if(erreur==0)
    {
        if(a==1)
        {
            if(atoi(nb)>maxim||atoi(nb)==0)
            {
                printf("\nGive a non-zero stopping time that does not exceed %d !!",maxim);
                return 0;
            }
            else
                return atoi(nb);
        }
        else
        {
            if(atoi(nb)==0)
            {
                printf("\nGive a non-zero quantum !!");
                return 0;
            }
            else
                return atoi(nb);

        }
    }
    else
    {
        printf("Give a positive and correct number !!");
        return 0;
    }
    return 0;
}

int verif_occur_code(char nom_fich[])
{
    int cpt_ocur,j,i=0;
    code_proc cod[20];
    char *nom_code;
    FILE *p;

    p=fopen(nom_fich,"rt");//read if you want to read the file or write if you want to write to the file

    while(fscanf(p,"%s",cod[i].cd)!=EOF)
    {
        nom_code = strtok (cod[i].cd,";");

        strcpy(cod[i].cd,nom_code);

        i++;
    }
    strcpy(cod[i].cd,"stop");

    fclose(p);

    i=0;

    while(strcmp(cod[i].cd,"stop")!=0)
    {
        j=0;
        cpt_ocur=0;

        while(strcmp(cod[j].cd,"stop")!=0)
        {
            if(strcmp(cod[j].cd,cod[i].cd)==0)
                cpt_ocur++;
            j++;
        }

        if(cpt_ocur==1)
        {
            i++;
        }
        else
        {
            printf("\nError ! There are %d processes with the same code %s !!",cpt_ocur,cod[i].cd);
            getch();
            return 0;
        }
    }
    return 1;
}

int som_acsii(char *code)
{
    char*p = code;
    int som=0;

    while (*p!='\0')//it doesn't work with '\n'
    {
        som=som+*p;//the sum of each character of the code in ascii
        p++;
    }
    return som;

}

///////////////////////////////////////////Functions for modifying the list of loaded processes/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
processus* enreg_pcb(FILE *fich_bcp,code_proc *code)
{
    processus *i= malloc(sizeof(processus));
    int date_arr;
    int dur_exec;
    int dur_non_modif_es;
    int priorite;
    char *fileRead;
    char chaine[100];
    char *part;

    fileRead =fgets(chaine,sizeof(chaine),fich_bcp);

    if(fileRead != NULL&&strcmp(chaine,"\n")!=0)
    {
        part = strtok (chaine,";");
        strcpy(code[0].cd,part);

        part = strtok(NULL, ";");
        date_arr=atoi(part);

        part = strtok (NULL, ";");
        dur_exec=atoi(part);

        part = strtok (NULL, ";");
        dur_non_modif_es=atoi(part);

        part = strtok (NULL, "\n");
        priorite=atoi(part);

        strcpy(i->code,code[0].cd);
        i->date_arr = date_arr;
        i->dur_exec = dur_exec;
        i->dur_exec_modif_proc = dur_exec;
        i->dur_non_modif_es=dur_non_modif_es;
        i->dur_modif_es=dur_non_modif_es;
        i->priorite=priorite;
        i->etat=0;
        i->dur_pret=0;
        i->dur_blq=0;
        code++;
        i->suiv = enreg_pcb(fich_bcp,code);
    }
    else
    {
        if(fileRead != NULL&&strcmp(chaine,"\n")==0)
        {
            strcpy(i->code,"zzzzzz");
            i->date_arr = 1000;
            i->suiv = enreg_pcb(fich_bcp,code);
        }
    }

    if(fileRead == NULL)
    {
        return NULL;
    }

    return i;
}

void supp_liste(processus *proc)
{
    processus *T;
    int boucle=1;
    do
    {
        T=proc;
        if(T->suiv!=NULL)
        {
            proc=proc->suiv;
            free(T);
        }
        else
        {
            boucle=0;
            free(T);
        }
    }
    while(boucle==1);
}

void supp_not(processus *proc)
{
    int boucle;
    processus *T=proc;

    boucle=1;

    do
    {
        if(T->suiv==NULL)
            break;

        if(strcmp(T->suiv->code,"zzzzzz")==0)
        {
            boucle=0;
            T->suiv=NULL;
        }
        else
            T=T->suiv;
    }
    while(boucle==1);
}

int nbr_proc(processus *proc)
{
    int nbr_pr=1;
    processus *pr=proc;

    if(pr->suiv!=NULL)
    {
        return nbr_pr+nbr_proc(pr->suiv);
    }
    else
    {
        return nbr_pr;
    }
}

void trie_proc(processus *proc)
{
    int permut,temp;
    char k[30];
    processus *T;
    do
    {
        T=proc;
        permut=0;

        while (T->suiv!=NULL)
        {
            if(T->date_arr>T->suiv->date_arr||(T->date_arr==T->suiv->date_arr&&strcmp(T->code,T->suiv->code)>0))
            {
                strcpy(k,T->code);
                strcpy(T->code,T->suiv->code);
                strcpy(T->suiv->code,k);

                temp=T->date_arr;
                T->date_arr=T->suiv->date_arr;
                T->suiv->date_arr=temp;

                temp=T->dur_exec;
                T->dur_exec=T->suiv->dur_exec;
                T->suiv->dur_exec=temp;

                temp=T->dur_exec_modif_proc;
                T->dur_exec_modif_proc=T->suiv->dur_exec_modif_proc;
                T->suiv->dur_exec_modif_proc=temp;

                temp=T->priorite;
                T->priorite=T->suiv->priorite;
                T->suiv->priorite=temp;

                temp=T->dur_modif_es;
                T->dur_modif_es=T->suiv->dur_modif_es;
                T->suiv->dur_modif_es=temp;

                temp=T->dur_non_modif_es;
                T->dur_non_modif_es=T->suiv->dur_non_modif_es;
                T->suiv->dur_non_modif_es=temp;

                temp=T->dur_blq;
                T->dur_blq=T->suiv->dur_blq;
                T->suiv->dur_blq=temp;

                temp=T->dur_pret;
                T->dur_pret=T->suiv->dur_pret;
                T->suiv->dur_pret=temp;

                permut=1;
            }
            T=T->suiv;
        }
    }
    while(permut!=0);
}

///////////////////////////////////////////grid display function/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affich_res(info proces[],int N,char *code,int a,int k)
{
    int i;

    if(meth_affich==1)
    {
        putchar(218);
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
        for(i=k; i<=N; i++)
        {
            putchar(194);
            putchar(196);
        }
        putchar(191);



        printf("\n");
        putchar(179);
        printf("     ");
        putchar(179);
        printf("elcted");

        for(i=k; i<=N; i++)
        {
            if(proces[i].elu==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);
            }
            else
            {
                if(proces[i].elu==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);
                }
                else
                {
                    if(proces[i].elu==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);
                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);
                    }
                }
            }
        }

        printf("\n");
        putchar(179);
        printf("     ");
        putchar(195);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(197);
            putchar(196);
        }
        putchar(180);
        printf("\n");
        putchar(179);


        if(a==1)
        {

            if(strlen(code)==1)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==2||strlen(code)==3)
                    printf(" ");
            }

            printf("%s",code);

            if(strlen(code)==1||strlen(code)==2)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==3||strlen(code)==4)
                    printf(" ");
            }
        }
        else
            printf("     ");

        putchar(179);
        printf(" Ready");

        for(i=k; i<=N; i++)
        {
            if(proces[i].pret==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);

            }
            else
            {
                if(proces[i].pret==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].pret==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                }

            }
        }

        printf("\n");


        putchar(179);


        if(a==2)
        {

            if(strlen(code)==1)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==2||strlen(code)==3)
                    printf(" ");
            }

            printf("%s",code);

            if(strlen(code)==1||strlen(code)==2)
            {
                printf("  ");
            }
            else
            {
                if(strlen(code)==3||strlen(code)==4)
                    printf(" ");
            }
        }
        else
            printf("     ");

        putchar(195);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        putchar(196);
        for(i=k; i<=N; i++)
        {
            putchar(197);
            putchar(196);
        }
        putchar(180);
        printf("\n");
        putchar(179);
        printf("     ");
        putchar(179);
        printf(" I/O  ");

        for(i=k; i<=N; i++)
        {
            if(proces[i].ent_sor==-1)
            {
                putchar(179);
                printf(" ");
                if(i==N)putchar(179);

            }
            else
            {
                if(proces[i].ent_sor==0)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].ent_sor==1)
                    {
                        putchar(179);
                        printf("X");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                }
            }
        }


        if(a==2)
        {
            printf("\n");
            putchar(179);
            printf("     ");
            putchar(195);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            putchar(196);
            for(i=k; i<=N; i++)
            {
                putchar(197);
                putchar(196);
            }
            putchar(180);
            printf("\n");
            putchar(179);
            printf("     ");
            putchar(179);
            printf("Bloked");

            for(i=k; i<=N; i++)
            {
                if(proces[i].blq==-1)
                {
                    putchar(179);
                    printf(" ");
                    if(i==N)putchar(179);

                }
                else
                {
                    if(proces[i].blq==0)
                    {
                        putchar(179);
                        printf(" ");
                        if(i==N)putchar(179);

                    }
                    else
                    {
                        if(proces[i].blq==1)
                        {
                            putchar(179);
                            printf("X");
                            if(i==N)putchar(179);

                        }
                        else
                        {
                            putchar(179);
                            printf(" ");
                            if(i==N)putchar(179);

                        }
                    }
                }
            }

        }

        printf("\n");
        putchar(192);
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
        for(i=k; i<=N; i++)
        {
            putchar(193);
            putchar(196);
        }
        putchar(217);

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("%d ",i);
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d ",i/10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",i/100);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("  ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d ",i%10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",(i%100)/10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t      ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("  ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("  ");
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d ",(i%100)%10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n");
    }
    else
    {
        printf("\n\telected\t: ");
        for(i=k; i<=N; i++)
        {
            if(proces[i].elu==-1)
                printf(" ");
            else
            {
                if(proces[i].elu==0)
                    printf("-");
                else
                {
                    if(proces[i].elu==1)
                        printf("X");
                    else
                        printf(" ");
                }
            }
        }

        printf("\n%s\tReady\t: ",code);
        for(i=k; i<=N; i++)
        {
            if(proces[i].pret==-1)
                printf(" ");
            else
            {
                if(proces[i].pret==0)
                    printf("-");
                else
                {
                    if(proces[i].pret==1)
                        printf("X");
                    else
                        printf(" ");
                }

            }
        }

        printf("\n\tI/O\t: ");
        for(i=k; i<=N; i++)
        {
            if(proces[i].ent_sor==-1)
                printf(" ");
            else
            {
                if(proces[i].ent_sor==0)
                    printf("-");
                else
                {
                    if(proces[i].ent_sor==1)
                        printf("X");
                    else
                        printf(" ");
                }
            }
        }

        if(a==2)
        {
            printf("\n\Blocked\t: ");
            for(i=k; i<=N; i++)
            {
                if(proces[i].blq==-1)
                    printf(" ");
                else
                {
                    if(proces[i].blq==0)
                        printf("-");
                    else
                    {
                        if(proces[i].blq==1)
                            printf("X");
                        else
                            printf(" ");
                    }
                }
            }
        }

        printf("\n\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf("%d",i);
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d",i/10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",i/100);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf(" ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf("%d",i%10);
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",(i%100)/10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

        printf("\n\t          ");
        for(i=k; i<=N; i++)
        {
            if(i<10)
            {
                printf(" ");
            }
            else
            {
                if(i>=10&&i<=99)
                {
                    printf(" ");
                }
                else
                {
                    if(i>=100&&i<=maxim)
                    {
                        printf("%d",(i%100)%10);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }

    }
}

/////////////////////////////////////////////////////////////Round_robin FIRST CASE////////////////////////////////////////////////////////////////////////
void Round_robin_pro(processus *proc,int N,char *code,int qt,info proces[])
{
    processus *T;
    processus *q;
    int boucle,cpt,maj;
    int duratt_cpu,place,pos,i,existe_cpu,util_cpu=0,pause=0;
    char cd_proc[10];
    int execution_proc=proc->date_arr;

    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);

    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        if(util_cpu==0)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the longest waiting time
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same long waiting time selected
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice by alphabetical order
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                    {
                        if(T->dur_exec_modif_proc>=qt)
                            util_cpu=qt;
                        else
                            util_cpu=T->dur_exec_modif_proc;
                        break;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                if(strcmp(T->code,cd_proc)!=0)
                {
                    strcpy(cd_proc,T->code);

                    pause=1;
                    T->cmt[i+1].elu=1;
                }
                else
                {
                    T->dur_exec_modif_proc--;
                    util_cpu--;

                    if(util_cpu==0&&T->dur_exec_modif_proc!=0)
                    {
                        strcpy(cd_proc,T->code);
                    }
                    T->cmt[i].elu=1;
                }
                T->dur_pret=0;

            }
        }
        else
        {
            T->dur_exec_modif_proc--;
            util_cpu--;

            if(util_cpu==0&&T->dur_exec_modif_proc!=0)
            {
                T->dur_pret--;
                strcpy(cd_proc,T->code);
            }
        }
/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0&&proces[i-1].elu==1)//process of elected to ready having just finished its quantum
                    {
                        proces[i].pret=-1;
                        proces[i].elu=-1;
                        proces[i].ent_sor=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&proces[i-1].elu!=1)//process always ready
                        {
                            proces[i].pret=1;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                        }
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&pause==0)//process always elected
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&pause==1)
                        {
                            pause=0;

                            if(proces[i-1].ent_sor==0||proces[i-1].pret==1)
                            {
                                proces[i].pret=-1;//from ready to elected
                            }
                            else proces[i].pret=0;

                            proces[i].elu=-1;

                            if(proces[i-1].ent_sor!=1||execution_proc==0)
                                proces[i].ent_sor=0;
                            else
                                proces[i].ent_sor=-1;//from I/O to elected
                        }
                    }
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Input and output processing/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to decrement the duration
        {

            if(q->date_arr<=execution_proc&&(q->etat==1||q->etat==2))
            {

                if(q->etat==1)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=-1;
                        proces[i].ent_sor=-1;
                    }

                    q->etat=2;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&q->etat==2)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                    }
                    q->dur_modif_es--;

                    if(q->dur_modif_es==0)
                    {
                        q->etat=0;
                        q->dur_modif_es=q->dur_non_modif_es;
                    }
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
                T->cmt[i+2].ent_sor=1;
            }
            T->dur_exec_modif_proc=T->dur_exec;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////Data initialization
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->etat=0;
        T->turn=0;
        T->dur_blq=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////Round_robin SECOND CASE////////////////////////////////////////////////////////////////////////
void Round_robin_pro_2(processus *proc,int N,char *code,int qt,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle,cpt,maj;
    int duratt_cpu,place,pos,i,existe_cpu,util_cpu=0,pause=0,es_lib=1,existe_es=0,dur_es;
    int execution_proc=proc->date_arr;
    char cd_proc[10];
    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        if(util_cpu==0)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the longest waiting time
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                    {
                        if(T->dur_exec_modif_proc>=qt)
                            util_cpu=qt;
                        else
                            util_cpu=T->dur_exec_modif_proc;
                        break;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same long waiting time selected
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice by alphabetical order
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    T=proc;
                    pos=0;
                    while(boucle==1)////////////////to point to the selected process
                    {
                        if(pos==place)
                        {
                            if(T->dur_exec_modif_proc>=qt)
                                util_cpu=qt;
                            else
                                util_cpu=T->dur_exec_modif_proc;
                            break;
                        }
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                if(strcmp(T->code,cd_proc)!=0)
                {
                    strcpy(cd_proc,T->code);
                    pause=1;//TC at the beginning of the process
                    T->cmt[i+1].elu=1;
                }
                else
                {
                    T->dur_exec_modif_proc--;
                    util_cpu--;

                    if(util_cpu==0&&T->dur_exec_modif_proc!=0)
                    {
                        T->dur_pret--;
                        strcpy(cd_proc,T->code);
                    }
                    T->cmt[i].elu=1;
                }
                T->dur_pret=0;

            }
        }
        else
        {
            T->dur_exec_modif_proc--;
            util_cpu--;

            if(util_cpu==0&&T->dur_exec_modif_proc!=0)
            {
                T->dur_pret--;
                strcpy(cd_proc,T->code);
            }
        }
/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0&&proces[i-1].elu==1)
                    {
                        proces[i].pret=-1;
                        proces[i].elu=-1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&proces[i-1].elu!=1)
                        {
                            proces[i].pret=1;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                            proces[i].blq=0;
                        }
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0&&pause==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(q->code,code)==0&&pause==1)
                        {
                            pause=0;

                            if(proces[i-1].ent_sor==0||proces[i-1].pret==1)
                            {
                                proces[i].pret=-1;
                            }
                            else proces[i].pret=0;

                            proces[i].elu=-1;
                            proces[i].blq=0;

                            if(proces[i-1].ent_sor!=1||execution_proc==0)
                                proces[i].ent_sor=0;
                            else
                                proces[i].ent_sor=-1;
                        }
                    }
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

/////////////////////////////////////////////////////////////I/O process processing/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2))
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that should use the I/O because it has the shortest I/O duration
                {
                    if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same small i/o duration chosen
                {
                    if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////to point to the first process not yet completed
                    {
                        if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2))
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////to detect the process that needs to use the I/O because it has the longest waiting time
                    {
                        if(K->date_arr<=execution_proc&&(K->etat==1||K->etat==2)&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i+1].ent_sor=1;
                es_lib=0;
            }
        }
/////////////////////////////////////////////////////////////Handling of blocked processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&(L->etat==1||L->etat==2))
            {
                if(L->etat==1)
                {
                    if(strcmp(L->code,code)==0&&strcmp(L->code,K->code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=-1;
                        proces[i].ent_sor=-1;
                        proces[i].blq=0;
                    }
                    else
                    {
                        if(strcmp(L->code,code)==0&&strcmp(L->code,K->code)!=0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=-1;
                            proces[i].ent_sor=0;
                            proces[i].blq=-1;
                        }
                    }
                    L->etat=2;
                }
                else
                {
                    if(strcmp(L->code,K->code)!=0)
                    {
                        if(strcmp(L->code,code)==0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=0;
                            proces[i].ent_sor=0;
                            proces[i].blq=1;
                        }
                        L->dur_blq++;
                        if(L->dur_blq==1)
                            L->cmt[i+1].blq=1;
                    }
                    else
                    {
                        if(strcmp(L->code,code)==0)
                        {
                            proces[i].pret=0;
                            proces[i].elu=0;
                            proces[i].ent_sor=1;
                            proces[i].blq=0;
                        }
                        L->dur_modif_es--;
                    }
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////Data initialization
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////FIFO FIRST CASE/////////////////////////////////////////////////////////////////////////
void fifo_pro(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    int boucle;
    int proc_lib=1,duratt_cpu,place,pos,i,existe_cpu,cpt,maj;
    int execution_proc=proc->date_arr;

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);

    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        if(proc_lib==1)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the longest waiting time
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same long waiting time selected
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice by alphabetical order
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                T->dur_pret=0;
                T->cmt[i].elu=1;
                proc_lib=0;
            }
        }
/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Input and output processing/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to decrease the duration
        {
            if(q->date_arr<=execution_proc&&q->etat==1)
            {
                if(strcmp(q->code,code)==0)
                {
                    proces[i].pret=0;
                    proces[i].elu=0;
                    proces[i].ent_sor=1;
                }
                q->dur_modif_es--;

                if(q->dur_modif_es==0)
                {
                    q->etat=0;
                    q->dur_modif_es=q->dur_non_modif_es;
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->date_arr<=execution_proc&&T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                T->cmt[i+1].ent_sor=1;
            }
            T->dur_exec_modif_proc=T->dur_exec;
            proc_lib=1;
        }

        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);
/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////Data initialization
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->etat=0;
        T->turn=0;
        T->dur_blq=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////FIFO SECOND CASE/////////////////////////////////////////////////////////////////////////
void fifo_pro_2(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle;
    int proc_lib=1,es_lib=1,duratt_cpu,dur_es,place,pos,i,existe_cpu,existe_es=0,cpt,maj;
    int execution_proc=proc->date_arr;

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        if(proc_lib==1)
        {
            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    existe_cpu=1;
                    duratt_cpu=q->dur_pret;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_cpu==1)
            {
                existe_cpu=0;
                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the longest waiting time
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->dur_pret>duratt_cpu))
                    {
                        place=pos;
                        duratt_cpu=T->dur_pret;
                    }

                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                q=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same long waiting time selected
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu))
                    {
                        cpt++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice by alphabetical order
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->dur_pret==duratt_cpu)&&som_acsii(q->code)<maj)
                        {
                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(T->suiv!=NULL) T=T->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                T->dur_pret=0;
                T->cmt[i].elu=1;
                proc_lib=0;
            }
        }
/////////////////////////////////////////////////////////////I/O process processing/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(K->date_arr<=execution_proc&&K->etat==1)
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }

            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that should use the I/O because it has the shortest I/O duration
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same small i/o duration chosen
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////to point to the first process not yet completed
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1)
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////to detect the process that needs to use the I/O because it has the longest waiting time
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i].ent_sor=1;
                es_lib=0;
            }
        }

/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

/////////////////////////////////////////////////////////////Handling of blocked processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&L->etat==1)
            {
                if(strcmp(L->code,K->code)!=0)
                {
                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=1;
                    }
                    L->dur_blq++;
                    if(L->dur_blq==1)
                        L->cmt[i].blq=1;
                }
                else
                {
                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                        proces[i].blq=0;
                    }
                    L->dur_modif_es--;
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)////test that it is better to put it after the treatment of the blocked ones
        {
            if(T->dur_modif_es!=0)T->etat=1;
            T->dur_exec_modif_proc=T->dur_exec;
            proc_lib=1;
        }

        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////to initialize the data
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////PRIORITY WITH REQUEST FIRST CASE/////////////////////////////////////////////////////////////////////////
void prio_avec_req(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    int boucle,prem_tour,tour=0;
    int place,pos,i,cpt_arr,prio_max,cpt_ocu,maj;
    char cd_proc[10];
    int execution_proc=proc->date_arr;
    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        cpt_arr=0;

        while(boucle==1)////////////////to point to the first process not yet completed
        {
            if(q->date_arr<=execution_proc&&q->etat==0&&q->dur_exec_modif_proc!=0&&q->dur_modif_es==q->dur_non_modif_es)
            {
                cpt_arr++;
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if((cpt_arr>1)||(cpt_arr==1&&strcmp(cd_proc,T->code)!=0))
        {
            if(T->date_arr<=execution_proc&&T->etat==0&&T->dur_exec_modif_proc!=T->dur_exec)
            {
                tour++;
                T->turn=tour;
            }

            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    prio_max=q->priorite;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }


            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////to detect which process should use the CPU because it has the highest priority
            {
                if(T->date_arr<=execution_proc&&T->etat==0&&(T->priorite)>(prio_max))
                {
                    place=pos;
                    prio_max=T->priorite;
                }
                if(T->suiv!=NULL) T=T->suiv;
                else
                {
                    boucle=0;
                }
                pos++;
            }

            cpt_ocu=0;
            boucle=1;
            q=proc;
            while(boucle==1)////////////////to find out if there are processes with the same priority
            {
                if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                {
                    cpt_ocu++;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
            }

            if(cpt_ocu!=1)
            {
                boucle=1;
                q=proc;
                while(boucle==1)////////////////to point to the first process with the highest priority
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                    {
                        prem_tour=q->turn;
                        break;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the highest priority and the first round (reboot)
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->turn)>(prem_tour))
                    {
                        place=pos;
                        prem_tour=T->turn;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else
                    {
                        boucle=0;
                    }
                    pos++;
                }


                boucle=1;
                q=proc;
                cpt_ocu=0;
                while(boucle==1)////////////////to count the number of processes having the same grand tour
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour))
                    {
                        cpt_ocu++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt_ocu!=1)
                {

                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice in alphabetical order for the case of processes having the same priority and the same round = 0 because they have the same arrival date
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour)&&som_acsii(q->code)<maj)
                        {

                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else
                        {
                            boucle=0;
                        }
                        pos++;
                    }
                }
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////to point to the selected process
            {
                if(pos==place)
                    break;
                else
                {
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                }
                pos++;
            }

            if(strcmp(cd_proc,T->code)!=0)
            {
                strcpy(cd_proc,T->code);
                T->cmt[i].elu=1;
                T->dur_pret=0;
                T->turn=0;
            }
        }
        else
            tour=0;

/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Input and output processing/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to decrease the duration
        {
            if(q->date_arr<=execution_proc&&q->etat==1)
            {
                if(strcmp(q->code,code)==0)
                {
                    proces[i].pret=0;
                    proces[i].elu=0;
                    proces[i].ent_sor=1;
                }
                q->dur_modif_es--;

                if(q->dur_modif_es==0)
                {
                    q->etat=0;
                    q->dur_modif_es=q->dur_non_modif_es;
                }
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                T->cmt[i+1].ent_sor=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////Data initialization
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->turn=0;
        T->etat=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

/////////////////////////////////////////////////////////////PRIORITY WITH REQUIREMENT SECOND CASE/////////////////////////////////////////////////////////////////////////
void prio_avec_req_2(processus *proc,int N,char *code,info proces[])
{
    processus *T;
    processus *q;
    processus *K;
    processus *L;
    int boucle,prem_tour,tour=0,maj;
    int place,pos,i,cpt_arr,prio_max,cpt_ocu,es_lib=1,dur_es,existe_es=0,cpt;
    char cd_proc[10];
    int execution_proc=proc->date_arr;

    strcpy(cd_proc,"nothing");

    for(i=0; i<N; i++)
    {
        proces[i].elu=-2;
        proces[i].ent_sor=-2;
        proces[i].pret=-2;
        proces[i].blq=-2;
    }

    boucle=1;
    T=proc;

    do
    {
        for(i=0; i<N; i++)
        {
            T->cmt[i].elu=0;
            T->cmt[i].pret=0;
            T->cmt[i].ent_sor=0;
            T->cmt[i].blq=0;
        }
        if(T->suiv!=NULL)
            T=T->suiv;
        else
            boucle=0;
    }
    while(boucle==1);


    i=proc->date_arr;

    do
    {
/////////////////////////////////////////////////////////////Treatment of the elected process/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        cpt_arr=0;

        while(boucle==1)////////////////to point to the first process not yet completed
        {
            if(q->date_arr<=execution_proc&&q->etat==0&&q->dur_exec_modif_proc!=0&&q->dur_modif_es==q->dur_non_modif_es)
            {
                cpt_arr++;
            }
            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }

        if((cpt_arr>1)||(cpt_arr==1&&strcmp(cd_proc,T->code)!=0))
        {
            if(T->date_arr<=execution_proc&&T->etat==0&&T->dur_exec_modif_proc!=T->dur_exec)
            {
                tour++;
                T->turn=tour;
            }

            boucle=1;
            q=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(q->date_arr<=execution_proc&&q->etat==0)
                {
                    prio_max=q->priorite;
                    place=pos;
                    break;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
                pos++;
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////to detect which process should use the CPU because it has the highest priority
            {
                if(T->date_arr<=execution_proc&&T->etat==0&&(T->priorite)>(prio_max))
                {
                    place=pos;
                    prio_max=T->priorite;
                }
                if(T->suiv!=NULL) T=T->suiv;
                else
                {
                    boucle=0;
                }
                pos++;
            }

            cpt_ocu=0;
            boucle=1;
            q=proc;
            while(boucle==1)////////////////to find out if there are processes with the same priority
            {
                if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                {
                    cpt_ocu++;
                }
                if(q->suiv!=NULL) q=q->suiv;
                else boucle=0;
            }

            if(cpt_ocu!=1)
            {
                boucle=1;
                q=proc;
                while(boucle==1)////////////////to point to the first process with the highest priority.
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&q->priorite==prio_max)
                    {
                        prem_tour=q->turn;
                        break;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                boucle=1;
                T=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that must use the CPU because it has the highest priority and the first round (reboot)
                {
                    if(T->date_arr<=execution_proc&&T->etat==0&&(T->turn)>(prem_tour))
                    {
                        place=pos;
                        prem_tour=T->turn;
                    }
                    if(T->suiv!=NULL) T=T->suiv;
                    else
                    {
                        boucle=0;
                    }
                    pos++;
                }
                boucle=1;
                q=proc;
                cpt_ocu=0;
                while(boucle==1)////////////////to count the number of processes having the same grand tour
                {
                    if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour))
                    {
                        cpt_ocu++;
                    }
                    if(q->suiv!=NULL) q=q->suiv;
                    else boucle=0;
                }

                if(cpt_ocu!=1)
                {
                    boucle=1;
                    q=proc;
                    maj=1000;
                    pos=0;

                    while(boucle==1)////////////////choice by alphabetical order
                    {
                        if(q->date_arr<=execution_proc&&q->etat==0&&(q->turn==prem_tour)&&som_acsii(q->code)<maj)
                        {

                            maj=som_acsii(q->code);
                            place=pos;
                        }
                        if(q->suiv!=NULL) q=q->suiv;
                        else
                        {
                            boucle=0;
                        }
                        pos++;
                    }
                }
            }

            boucle=1;
            T=proc;
            pos=0;
            while(boucle==1)////////////////to point to the selected process
            {
                if(pos==place)
                    break;
                else
                {
                    if(T->suiv!=NULL) T=T->suiv;
                    else boucle=0;
                }
                pos++;
            }

            if(strcmp(cd_proc,T->code)!=0)
            {
                strcpy(cd_proc,T->code);
                T->cmt[i].elu=1;
                T->dur_pret=0;
                T->turn=0;
            }
        }
        else
            tour=0;
///////////////////////////////////////////////////////////I/O process processing/////////////////////////////////////////////////////////////////////////
        if(es_lib==1)
        {
            boucle=1;
            K=proc;
            pos=0;
            place=0;
            while(boucle==1)////////////////to point to the first process not yet completed
            {
                if(K->date_arr<=execution_proc&&K->etat==1)
                {
                    existe_es=1;
                    dur_es=K->dur_non_modif_es;
                    place=pos;
                    break;
                }
                if(K->suiv!=NULL) K=K->suiv;
                else boucle=0;
                pos++;
            }
            if(existe_es==1)
            {
                existe_es=0;
                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to detect the process that should use the I/O because it has the shortest I/O duration
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es<dur_es))
                    {
                        place=pos;
                        dur_es=K->dur_non_modif_es;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                    pos++;
                }

                boucle=1;
                K=proc;
                cpt=0;
                while(boucle==1)////////////////to count the number of processes with the same small i/o duration chosen
                {
                    if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_non_modif_es==dur_es))
                    {
                        cpt++;
                    }
                    if(K->suiv!=NULL) K=K->suiv;
                    else boucle=0;
                }

                if(cpt!=1)
                {
                    boucle=1;
                    K=proc;
                    pos=0;
                    place=0;
                    while(boucle==1)////////////////to point to the first process not yet completed
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1)
                        {
                            dur_es=K->dur_blq;
                            place=pos;
                            break;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }

                    boucle=1;
                    K=proc;
                    pos=0;
                    while(boucle==1)////////////////to detect the process that needs to use the I/O because it has the longest waiting time
                    {
                        if(K->date_arr<=execution_proc&&K->etat==1&&(K->dur_blq>dur_es))
                        {
                            place=pos;
                            dur_es=K->dur_blq;
                        }
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                        pos++;
                    }
                }

                boucle=1;
                K=proc;
                pos=0;
                while(boucle==1)////////////////to point to the selected process
                {
                    if(pos==place)
                        break;
                    else
                    {
                        if(K->suiv!=NULL) K=K->suiv;
                        else boucle=0;
                    }
                    pos++;
                }
                K->dur_blq=0;
                K->cmt[i].ent_sor=1;
                es_lib=0;
            }
        }

/////////////////////////////////////////////////////////////Processing of ready processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        q=proc;
        while(boucle==1)////////////////to calculate the waiting time for each ready process
        {
            if(q->date_arr<=execution_proc&&q->etat==0)
            {
                if(strcmp(q->code,T->code)!=0)
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=1;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_pret++;
                    if(q->dur_pret==1)
                        q->cmt[i].pret=1;
                }
                else
                {
                    if(strcmp(q->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=1;
                        proces[i].ent_sor=0;
                        proces[i].blq=0;
                    }
                    q->dur_exec_modif_proc--;
                }
            }

            if(q->suiv!=NULL) q=q->suiv;
            else boucle=0;
        }
/////////////////////////////////////////////////////////////Handling of blocked processes/////////////////////////////////////////////////////////////////////////
        boucle=1;
        L=proc;
        while(boucle==1)
        {
            if(L->date_arr<=execution_proc&&L->etat==1)
            {
                if(strcmp(L->code,K->code)!=0)
                {

                    if(strcmp(L->code,code)==0)
                    {
                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=0;
                        proces[i].blq=1;
                    }
                    L->dur_blq++;
                    if(L->dur_blq==1)
                        L->cmt[i].blq=1;
                }
                else
                {
                    if(strcmp(L->code,code)==0)
                    {

                        proces[i].pret=0;
                        proces[i].elu=0;
                        proces[i].ent_sor=1;
                        proces[i].blq=0;
                    }
                    L->dur_modif_es--;
                }

                if(L->dur_modif_es==0)
                {
                    es_lib=1;
                    L->dur_modif_es=L->dur_non_modif_es;
                    L->etat=0;
                }
            }

            if(L->suiv!=NULL) L=L->suiv;
            else boucle=0;
        }

        if(T->dur_exec_modif_proc==0&&T->etat==0)////test that it is better to put it after the treatment of the blocked ones
        {
            if(T->dur_modif_es!=0)
            {
                T->etat=1;
                strcpy(cd_proc,"nothing");
            }
            T->dur_exec_modif_proc=T->dur_exec;
        }
        execution_proc++;
        i++;
    }
    while(execution_proc<N+1);

/////////////////////////////////////////////////////////////Data initialization/////////////////////////////////////////////////////////////////////////
    boucle=1;
    T=proc;
    while(boucle==1)////////////////Data initialization
    {
        T->dur_exec_modif_proc=T->dur_exec;
        T->dur_modif_es=T->dur_non_modif_es;
        T->dur_pret=0;
        T->dur_blq=0;
        T->etat=0;
        T->turn=0;

        if(T->suiv!=NULL) T=T->suiv;
        else boucle=0;
    }
}

///////////////////////////////////////Scheduling Algorithm Title Display Functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void title_fifo_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("First In First out stateless Blocked");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf("        ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

void title_trq_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("Round_robin with TC=1 stateless blocked");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

void title_par_1(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf("Priority with stateless recquisition Blocked");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

void title_fifo_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("First In First Out with Blocked state");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

void title_trq_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf(" ");
    printf("  ");
    printf("Round_robin with TC=1 with blocked state");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

void title_par_2(void)
{
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");
    printf("Priority with recquisition with Blocked state");
    printf(" ");
    printf(" ");
    printf(" ");
    putchar(179);
    printf("\n");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
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
    printf("\n");

}

///////////////////////////////////////////The display functions of the data table//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void entete(void)
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
    printf("I/O time   ");
    printf(" ");
    putchar(179);
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
    putchar(180);
}

void milieu(char *a,int b,int c,int d,int e)
{
    int aa=strlen(a),i;
    int bb;
    int cc;
    int dd;
    int ee;

    if(b>=10)
        bb=2;
    else
        bb=1;

    if(c>=10)
        cc=2;
    else
        cc=1;

    if(d>=10)
        dd=2;
    else
        dd=1;

    if(e>=10)
        ee=2;
    else
        ee=1;



    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for(i=1; i<=(9-aa)/2; i++)
        printf(" ");
    printf("%s",a);
    for(i=1; i<=((9-aa)/2)+(9-aa)%2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");


    if(bb==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }


    printf(" ");
    putchar(179);
    printf(" ");

    if(cc==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=6; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(dd==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(ee==1)
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=4; i++)
            printf(" ");
    }

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
    putchar(180);
}

void fin_tab(char *a,int b,int c,int d,int e)
{
    int aa=strlen(a),i;
    int bb;
    int cc;
    int dd;
    int ee;

    if(b>=10)
        bb=2;
    else
        bb=1;

    if(c>=10)
        cc=2;
    else
        cc=1;

    if(d>=10)
        dd=2;
    else
        dd=1;

    if(e>=10)
        ee=2;
    else
        ee=1;


    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf(" ");
    printf("        ");
    putchar(179);
    printf(" ");

    for(i=1; i<=(9-aa)/2; i++)
        printf(" ");
    printf("%s",a);
    for(i=1; i<=((9-aa)/2)+(9-aa)%2; i++)
        printf(" ");

    printf(" ");
    putchar(179);
    printf(" ");

    if(bb==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",b);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(cc==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=6; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",c);
        for(i=1; i<=5; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");


    if(dd==1)
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=5; i++)
            printf(" ");
        printf("%d",d);
        for(i=1; i<=4; i++)
            printf(" ");
    }

    printf(" ");
    putchar(179);
    printf(" ");

    if(ee==1)
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=5; i++)
            printf(" ");
    }
    else
    {
        for(i=1; i<=4; i++)
            printf(" ");
        printf("%d",e);
        for(i=1; i<=4; i++)
            printf(" ");
    }



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
    putchar(217);
}

void afficher_proc(processus *proc,int nbr,char nom_fich[])
{

    int boucle=1;
    int pos=1;
    processus *T=proc;

    printf("\n\t\t                       List of file data %s : \n",nom_fich);
    printf("\n");
    entete();

    do
    {
        if(pos!=nbr)
        {
            printf("\n");
            milieu(T->code,T->date_arr,T->dur_exec,T->dur_non_modif_es,T->priorite);
        }
        else
        {
            printf("\n");
            fin_tab(T->code,T->date_arr,T->dur_exec,T->dur_non_modif_es,T->priorite);
        }

        if(T->suiv!=NULL)
        {
            T=T->suiv;
        }
        else
            boucle=0;
        pos++;
    }
    while(boucle==1);

}

void titre(void)
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                     ~~ ORDO-3P1B ~~                    |\n");
    printf("                |                PROCESS MANAGEMENT PROGRAM              |\n");
    printf("                 --------------------------------------------------------\n");
}

int menu_prin(int enreg_don)
{
    int boucle=1,rep;

    printf(" \n                             -------------------------------\n");
    printf("                            |            MAIN MENU          |\n");
    printf("                             -------------------------------\n");
    printf("                            |   1 . Loading data            |\n");;
    printf("                            |   2 . List of data            |\n");;
    printf("                            |   3 . Choice of algorithm     |\n");
    printf("                            |   4 . Exit                    |\n");
    printf("                             -------------------------------\n");
    do
    {
        printf("\t\t\t\t\tyour choice : ");
        rep=getch();
        if(rep!=49&&rep!=50&&rep!=51&&rep!=52)
        {
            printf("\nPlease make a choice between 1 and 4 !!\n");
            boucle=1;
        }
        else
        {
            if(enreg_don==1)
            {
                boucle=0;
            }
            else
            {
                if((rep==50||rep==51)&&enreg_don==0)
                    printf("\nYou need to upload your data first !!\n");
                else
                    boucle=0;
            }
        }
    }
    while(boucle==1);
    return rep;
}

int menu_ch_algo(void)
{
    int rep;

    titre();

    printf(" \n                   ---------------------------------------------------\n");
    printf("                  |                SCHEDULING ALGORITHMS              |\n");
    printf("                   ---------------------------------------------------\n");
    printf("\t          |\t\t   ");
    putchar(4);
    printf(" Stateless blocked ");
    putchar(4);
    printf("\t      |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   1 . FIFO                                        |\n");
    printf("                  |   2 . Round_robin+TC=1                            |\n");
    printf("                  |   3 . Priority with requisition                   |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("\t          |\t     ");
    putchar(4);
    printf(" With blocked state managed by SJF ");
    putchar(4);
    printf("    |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   4 . FIFO                                        |\n");
    printf("                  |   5 . Round_robin+TC=1                            |\n");
    printf("                  |   6 . Priority with requisition                   |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                  |   7 . Return to the main menu                     |");
    printf("\n\t          |\t\t\t\t\t\t      |\n");
    printf("                   ---------------------------------------------------\n");

    printf("\t\t\t\t\t       your choice : ");

    do
    {
        rep=getch();
    }
    while(rep!=49&&rep!=50&&rep!=51&&rep!=52&&rep!=53&&rep!=54&&rep!=55);

    return rep;
}

int main()
{
    int nbrproc,i,n;
    int boucle,choix,decalge,existe,Qt;
    int rep,db,fn,qs,rest,enreg_don=0;
    char nom_fich[30],N[12],qt[12];
    FILE *pntr;
    processus *bcp,*T;
    info res[maxim];
    code_proc cod[20];

    if(meth_affich==1)
    {
        decalge=38;
    }
    else
    {
        decalge=60;
    }

    titre();
    // credits
    printf("\t\t\t\t       Hello (^_^) !!\n\t\t            Here is a process management program \n\t\t         according to the type of scheduling chosen\n\n");
    printf("   This program has been created by ABOUABDELMAJID KHALIL: a student in an Engineering Moroccan School ");
    printf("  \n          if anybody wanna contact me : abouabdelmajidkhalil@gmail.com ");
    printf("\n\n\t                               Press any key to begin ");
    getch();
    system("cls");
    rep=-1;

    do
    {
        if(rep==-1)
        {
            if(enreg_don==1)
            {
                system("cls");

            }
            titre();
            rep=menu_prin(enreg_don);
            if(rep==52)
            {
                printf("\n\n\t\tThank you for using this program (^_^) see you soon !!");
                getch();
            }
        }
        else
        {
            if(rep==49)
            {
                if(enreg_don==0)
                {
                    printf("\n\nGive the title of the file to load with the .TXT extension : ");
                    scanf("%s",nom_fich);

                    if(verif_bcp(nom_fich)==0)
                    {
                        rep=-1;
                        system("cls");
                    }
                    else
                    {
                        if(verif_occur_code(nom_fich)==0)
                        {
                            //supp_liste(bcp);
                            enreg_don=0;

                            rep=-1;
                            system("cls");
                        }
                        else
                        {
                            pntr=fopen(nom_fich,"rt");
                            bcp=enreg_pcb(pntr,&cod[0].cd);
                            fclose(pntr);

                            T=bcp;
                            trie_proc(T);
                            T=bcp;
                            supp_not(T);
                            T=bcp;
                            nbrproc=nbr_proc(T);

                            rep=-1;
                            enreg_don=1;
                            printf("Successful data loading !! \n");
                            getch();
                        }
                    }
                }
                else
                {
                    printf("\nSome Data are already loaded ! Do you want to crush them ? O/N : ");

                    do
                    {
                        rep=getch();
                    }
                    while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

                    if(rep==111||rep==79)
                    {
                        supp_liste(bcp);
                        printf("\ndeletion of old data has been done !!");

                        printf("\nGive the title of the new file to load with the .TXT extension : ");
                        scanf("%s",nom_fich);

                        if(verif_bcp(nom_fich)==0)
                        {
                            rep=-1;
                            enreg_don=0;
                            system("cls");
                        }
                        else
                        {
                            if(verif_occur_code(nom_fich)==0)
                            {
                                //supp_liste(bcp);
                                enreg_don=0;

                                rep=-1;
                                system("cls");
                            }
                            else
                            {
                                pntr=fopen(nom_fich,"rt");
                                bcp=enreg_pcb(pntr,&cod[0].cd);
                                fclose(pntr);

                                T=bcp;
                                trie_proc(T);
                                T=bcp;
                                supp_not(T);
                                T=bcp;
                                nbrproc=nbr_proc(T);

                                rep=-1;
                                enreg_don=1;
                                printf("Successful data loading !! \n");
                                getch();
                            }
                        }
                    }
                    else
                    {
                        printf("\nNo task were performed\n");
                        getch();
                        rep=-1;
                    }
                }
            }
            else
            {
                if(rep==50)
                {
                    system("cls");
                    titre();
                    T=bcp;
                    afficher_proc(T,nbrproc,nom_fich);
                    printf("\n\nR : return to the main menu ");
                    do
                    {
                        rep=getch();
                    }
                    while(rep!=114&&rep!=82);

                    if(rep==114||rep==82)
                        rep=-1;
                }
                else
                {
                    if(rep==51)
                    {
                        system("cls");
                        rep=menu_ch_algo();

                        if(rep!=55)
                        {
                            system("cls");
                            titre();
                            switch (rep)
                            {
                            case 49:
                                title_fifo_1();
                                break;
                            case 50:
                                title_trq_1();
                                break;
                            case 51:
                                title_par_1();
                                break;
                            case 52:
                                title_fifo_2();
                                break;
                            case 53:
                                title_trq_2();
                                break;
                            case 54:
                                title_par_2();
                                break;
                            }
                            do
                            {
                                printf("\nGive the stop time :");
                                scanf("%s",N);
                            }
                            while(verif_nombre(N,1)==0);

                            n=atoi(N);

                            if(rep==50||rep==53)
                            {
                                do
                                {
                                    printf("\nGive the Quantum : ");
                                    scanf("%s",qt);
                                }
                                while(verif_nombre(qt,2)==0);
                            }

                            Qt=atoi(qt);

                            boucle=1;
                            T=bcp;

                            do
                            {
                                for(i=0; i<=n; i++)
                                {
                                    T->cmt[i].elu=0;
                                    T->cmt[i].pret=0;
                                    T->cmt[i].ent_sor=0;
                                    T->cmt[i].blq=0;
                                }

                                if(T->suiv!=NULL)
                                    T=T->suiv;
                                else
                                    boucle=0;
                            }
                            while(boucle==1);
                            qs=(n/decalge);
                            rest=n-(qs*decalge);
                            db=0;
                            fn=decalge;
                            do
                            {
                                if(qs!=0)
                                {
                                    system("cls");
                                    titre();

                                    switch (rep)
                                    {
                                    case 49:
                                        title_fifo_1();
                                        break;
                                    case 50:
                                        title_trq_1();
                                        break;
                                    case 51:
                                        title_par_1();
                                        break;
                                    case 52:
                                        title_fifo_2();
                                        break;
                                    case 53:
                                        title_trq_2();
                                        break;
                                    case 54:
                                        title_par_2();
                                        break;
                                    }

                                    T=bcp;
                                    afficher_proc(T,nbrproc,nom_fich);
                                    printf("\n\nThe stop time is : %d\n\n",n);
                                    if(rep==50||rep==53)
                                        printf("The Quantum is : %d\n\n",Qt);

                                    T=bcp;
                                    for(i=0; i<nbrproc; i++)
                                    {
                                        switch (rep)
                                        {
                                        case 49:
                                            fifo_pro(T,fn,cod[i].cd,res);
                                            break;
                                        case 50:
                                            Round_robin_pro(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 51:
                                            prio_avec_req(T,fn,cod[i].cd,res);
                                            break;
                                        case 52:
                                            fifo_pro_2(T,fn,cod[i].cd,res);
                                            break;
                                        case 53:
                                            Round_robin_pro_2(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 54:
                                            prio_avec_req_2(T,fn,cod[i].cd,res);
                                            break;
                                        }

                                        switch (rep)
                                        {
                                        case 49:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 50:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 51:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 52:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 53:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 54:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        }
                                    }


                                    for(i=db; i<=fn; i++)/////////to view comments
                                    {
                                        T=bcp;
                                        boucle=1;
                                        existe=0;
                                        do
                                        {
                                            if(T->cmt[i].elu==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].pret==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].ent_sor==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].blq==1)
                                            {
                                                existe=1;
                                                break;
                                            }

                                            if(T->suiv==NULL)
                                                boucle=0;
                                            else
                                                T=T->suiv;
                                        }
                                        while(boucle==1);

                                        if(existe==1)
                                        {
                                            printf("\nT=%d\t: ",i);
                                            T=bcp;
                                            boucle=1;
                                            do
                                            {
                                                if(T->cmt[i].elu==1)
                                                    printf("%s is elected ",T->code);
                                                if(T->cmt[i].pret==1)
                                                    printf("%s is ready ",T->code);
                                                if(T->cmt[i].ent_sor==1)
                                                    printf("%s is using the I/O ",T->code);
                                                if(T->cmt[i].blq==1)
                                                    printf("%s is blocked ",T->code);

                                                if(T->suiv==NULL)
                                                    boucle=0;
                                                else
                                                    T=T->suiv;
                                            }
                                            while(boucle==1);
                                        }

                                    }

                                    if(rest==0)
                                    {
                                        if(qs-1==0)
                                        {
                                            if((n/decalge)>1)
                                            {
                                                printf("\n\n%c%c : Previous\t\tR : back to the algorithm choice menu\t",17,196);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=75&&choix!=114&&choix!=82);
                                            }
                                            else
                                            {
                                                if((n/decalge)==1&&rest==0)
                                                {
                                                    printf("\n\n\t\t          R : back to the algorithm choice menu ");
                                                    do
                                                    {
                                                        choix=getch();
                                                    }
                                                    while(choix!=114&&choix!=82);
                                                }
                                                else
                                                {
                                                    if((n/decalge)==1&&rest==1)
                                                    {
                                                        printf("\n\n\t\t        R : back to the algorithm choice menu\t         %c%c : Next",196,16);
                                                        do
                                                        {
                                                            choix=getch();
                                                        }
                                                        while(choix!=77&&choix!=114&&choix!=82);
                                                    }
                                                }

                                            }
                                        }
                                        else
                                        {
                                            if(qs==n/decalge)
                                            {
                                                printf("\n\n\t\t        R : back to the algorithm choice menu\t         %c%c : Next",196,16);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=77&&choix!=114&&choix!=82);
                                            }
                                            else
                                            {
                                                printf("\n\n%c%c : Previous\t          R : back to the algorithm choice menu\t     %c%c : Next",17,196,196,16);
                                                do
                                                {
                                                    choix=getch();
                                                }
                                                while(choix!=77&&choix!=75&&choix!=114&&choix!=82);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if(qs==n/decalge)
                                        {
                                            printf("\n\n\t\t        R : back to the algorithm choice menu\t         %c%c : Next",196,16);
                                            do
                                            {
                                                choix=getch();
                                            }
                                            while(choix!=77&&choix!=114&&choix!=82);
                                        }
                                        else
                                        {
                                            printf("\n\n%c%c : Previous\t           R : back to the algorithm choice menu\t          %c%c : Next",17,196,196,16);
                                            do
                                            {
                                                choix=getch();
                                            }
                                            while(choix!=77&&choix!=75&&choix!=114&&choix!=82);
                                        }
                                    }

                                    if(choix==77)
                                    {
                                        db=fn;
                                        qs--;
                                        fn=fn+decalge;
                                    }
                                    else
                                    {
                                        if(choix==75)
                                        {
                                            fn=db;
                                            db=db-decalge;
                                            qs++;
                                        }
                                    }
                                }
                                else
                                {
                                    system("cls");
                                    titre();

                                    switch (rep)
                                    {
                                    case 49:
                                        title_fifo_1();
                                        break;
                                    case 50:
                                        title_trq_1();
                                        break;
                                    case 51:
                                        title_par_1();
                                        break;
                                    case 52:
                                        title_fifo_2();
                                        break;
                                    case 53:
                                        title_trq_2();
                                        break;
                                    case 54:
                                        title_par_2();
                                        break;
                                    }

                                    fn=n;
                                    T=bcp;
                                    afficher_proc(T,nbrproc,nom_fich);
                                    printf("\n\nThe stop time is : %d\n\n",n);
                                    if(rep==50||rep==53)
                                        printf("The Quantum is : %d\n\n",Qt);

                                    for(i=0; i<nbrproc; i++)
                                    {
                                        switch (rep)
                                        {
                                        case 49:
                                            fifo_pro(T,fn,cod[i].cd,res);
                                            break;
                                        case 50:
                                            Round_robin_pro(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 51:
                                            prio_avec_req(T,fn,cod[i].cd,res);
                                            break;
                                        case 52:
                                            fifo_pro_2(T,fn,cod[i].cd,res);
                                            break;
                                        case 53:
                                            Round_robin_pro_2(T,fn,cod[i].cd,Qt,res);
                                            break;
                                        case 54:
                                            prio_avec_req_2(T,fn,cod[i].cd,res);
                                            break;
                                        }

                                        switch (rep)
                                        {
                                        case 49:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 50:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 51:
                                            affich_res(res,fn,cod[i].cd,1,db);
                                            break;
                                        case 52:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 53:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        case 54:
                                            affich_res(res,fn,cod[i].cd,2,db);
                                            break;
                                        }
                                    }

                                    for(i=db; i<=fn; i++)/////////to view comments
                                    {
                                        T=bcp;
                                        boucle=1;
                                        existe=0;
                                        do
                                        {
                                            if(T->cmt[i].elu==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].pret==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].ent_sor==1)
                                            {
                                                existe=1;
                                                break;
                                            }
                                            if(T->cmt[i].blq==1)
                                            {
                                                existe=1;
                                                break;
                                            }

                                            if(T->suiv==NULL)
                                                boucle=0;
                                            else
                                                T=T->suiv;
                                        }
                                        while(boucle==1);

                                        if(existe==1)
                                        {
                                            printf("\nT=%d\t: ",i);
                                            T=bcp;
                                            boucle=1;
                                            do
                                            {
                                                if(T->cmt[i].elu==1)
                                                    printf("%s is elected ",T->code);
                                                if(T->cmt[i].pret==1)
                                                    printf("%s is ready ",T->code);
                                                if(T->cmt[i].ent_sor==1)
                                                    printf("%s is using the I/O ",T->code);
                                                if(T->cmt[i].blq==1)
                                                    printf("%s is blocked ",T->code);

                                                if(T->suiv==NULL)
                                                    boucle=0;
                                                else
                                                    T=T->suiv;
                                            }
                                            while(boucle==1);
                                        }

                                    }

                                    if(n>decalge)
                                    {
                                        printf("\n\n%c%c : Previous\t\t       R : back to the algorithm choice menu\t",17,196);

                                        do
                                        {
                                            choix=getch();
                                        }
                                        while(choix!=75&&choix!=114&&choix!=82);

                                        if(choix==75)
                                        {
                                            fn=db;
                                            db=db-decalge;
                                            qs++;
                                        }
                                    }
                                    else
                                    {
                                        printf("\n\n\t\t         R : back to the algorithm choice menu ");
                                        do
                                        {
                                            choix=getch();
                                        }
                                        while(choix!=114&&choix!=82);
                                    }
                                }
                            }
                            while(choix!=114&&choix!=82);
                            rep=51;
                            system("cls");

                        }
                        else
                        {
                            rep=-1;
                        }
                    }
                }
            }
        }
    }
    while(rep!=52);

    return 0;
}
