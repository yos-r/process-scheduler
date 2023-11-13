#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

void titre()
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                PROCESS MANAGEMENT PROGRAM              |\n");
    printf("                 --------------------------------------------------------\n");
}

int menu_prin(int enreg_don)
{
    int boucle=1,rep;

    printf(" \n                             -------------------------------\n");
    printf("                            |            MAIN MENU          |\n");
    printf("                             -------------------------------\n");
    printf("                            |   0 . Generate data           |\n");
    printf("                            |   1 . Loading data            |\n");
    printf("                            |   2 . List of data            |\n");
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
                    printf("\n You need to upload your data first !!\n");
                else
                    boucle=0;
            }
        }
    }
    while(boucle==1);
    return rep;
}





int main() {
	initscr();  // Initialize ncurses
    titre();
    menu_prin(1);
    endwin();   // Cleanup ncurses
    return 0;
}