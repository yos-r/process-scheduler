#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{
    showFile(9);
    return 0;
}
