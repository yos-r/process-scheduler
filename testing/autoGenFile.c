#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

// GENERATE random TEXT FILE 
void creatFile() {
    FILE *f = fopen("pcb.txt", "w");

    if (f == NULL) {
        perror("Erreur");
        return;
    }
    srand(time(NULL));
	int i;
    int n=(rand()%10)+1;
    printf("%d\n",n); //print the number of processes randomly generated
    for (i = 0; i < n; i++) {
   		int x=(rand()%10)+1; // [1..10]
        int y=(rand()%10)+1;
        int z=(rand()%10)+1;
        fprintf(f,"p%d;%d;%d;%d\n",i,x,y,z);
    }
    fclose(f);
}

int main() {
    creatFile();
    printf("file generated.\n");
    return 0;
}
