#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool verifFile() {
    FILE *file = fopen("pcb.txt", "r");
    if (file == NULL) {
        perror("Erreur");
        getch();
        return false;
    }
    char ligne[100]; 
	char id[10]; 
    char ids[100][10]; 
    int id_count=0;
	int i,x, y, z;
    while (fgets(ligne, sizeof(ligne), file) != NULL) {
        if (sscanf(ligne,"%[^;];%d;%d;%d\n", id, &x, &y, &z)==4) {
        	printf("%s;%d;%d;%d\n",id,x,y,z);   	
            for (i = 0; i < id_count; i++) {
                if (strcmp(id, ids[i]) == 0) {
                    fclose(file);
                    return false;  //id n'est pas unique
                }
            }
            strcpy(ids[id_count], id);
            id_count++;
        } 
		else if(strcmp(ligne,"\n")!=0 && strncmp(ligne, "//", 2)!= 0)
		{
        	printf("erreur 2\n");
            fclose(file);
            return false;  // Format incorrect
        }
    }
    if(id_count==0)
    	{ // file vide
            printf("Your file is empty !!");
            getch();
            return false;
        }
    fclose(file);
    return true;  // "id" est unique \n et comment
}

int main() {
    if (verifFile()) {
        printf("good file \n");
    } else {
        printf("bad file \n");
    }

    return 0;
}
