// #include <stdio.h>
// #include <stdlib.h>

#include <dirent.h>

#include <dlfcn.h>

// #include "genListFile.c" //file  generates the list

#include "misc.h" // file w/ queues+ sorting functions
// including algorithms
// #include "algos/roundrobin.c"
// #include "algos/basicfifo.c"
// #include "algos/srt.c"

// #include <string.h>
// #include <ctype.h>

#define maxim 500     // the maximum stop time
#define meth_affich 1 // to choose the display method of the grill either 1 or 2

typedef void (*SchedulingAlgorithm)(processus *);
void extractFunctionName(const char *algorithmName, char *functionName)
{
    const char *lastDot = strrchr(algorithmName, '.');

    // Copy the substring before the last '.'
    if (lastDot)
    {
        size_t length = lastDot - algorithmName;
        strncpy(functionName, algorithmName, length);
        functionName[length] = '\0'; // Null-terminate the string
    }
    else
    {
        // No extension found, copy the whole string
        strcpy(functionName, algorithmName);
    }
}
SchedulingAlgorithm loadSchedulingAlgorithm(const char *algorithmName)
{
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "algos/%s", algorithmName);
    void *handle = dlopen(fullPath, RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Error loading %s: %s\n", algorithmName, dlerror());
        exit(EXIT_FAILURE);
    }
    char functionName[256];
    extractFunctionName(algorithmName, functionName);

    SchedulingAlgorithm algorithm = (SchedulingAlgorithm)dlsym(handle, functionName);
    if (!algorithm)
    {
        fprintf(stderr, "Error loading function from %s: %s\n", algorithmName, dlerror());
        exit(EXIT_FAILURE);
    }

    return algorithm;
}

void getSOFiles(const char *directory, char ***soFiles, int *numFiles)
{
    // Open the directory
    DIR *dir = opendir(directory);
    if (!dir)
    {
        fprintf(stderr, "Error opening directory: %s\n", directory);
        exit(EXIT_FAILURE);
    }

    // Count the number of .so files
    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Regular file
            const char *dot = strrchr(entry->d_name, '.');
            if (dot != NULL && strcmp(dot, ".so") == 0)
            {
                count++;
            }
        }
    }
    rewinddir(dir);

    // Allocate memory for the .so file names
    *soFiles = (char **)malloc(count * sizeof(char *));
    if (!(*soFiles))
    {
        fprintf(stderr, "Memory allocation error\n");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    int currentIndex = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Regular file
            const char *dot = strrchr(entry->d_name, '.');
            if (dot != NULL && strcmp(dot, ".so") == 0)
            {
                int len = strlen(entry->d_name);
                (*soFiles)[currentIndex] = (char *)malloc((len + 1) * sizeof(char));
                if (!(*soFiles)[currentIndex])
                {
                    fprintf(stderr, "Memory allocation error\n");
                    closedir(dir);
                    exit(EXIT_FAILURE);
                }
                strcpy((*soFiles)[currentIndex], entry->d_name);
                currentIndex++;
            }
        }
    }

    closedir(dir);

    *numFiles = count;
}

void displayMenu()
{
    DIR *dir;
    struct dirent *ent;

    // Open the directory
    if ((dir = opendir("algos")) != NULL)
    {
        int option = 1;

        // Read each entry in the directory
        while ((ent = readdir(dir)) != NULL)
        {
            // Check if the entry is a regular file and ends with ".c"
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".c") != NULL)
            {
                char algorithmName[300];
                snprintf(algorithmName, sizeof(algorithmName), "algos/%s", ent->d_name);

                // Load the algorithm dynamically
                SchedulingAlgorithm algorithm = loadSchedulingAlgorithm(algorithmName);

                // Display the menu option
                printf("%d. %s\n", option, ent->d_name);

                // Increment the option number
                option++;
            }
        }

        // Close the directory
        closedir(dir);
    }
    else
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
}

void titre(void)
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                     ~~ (❁´◡`❁) ~~                    |\n");
    printf("                |                PROCESS SCHEDULER APPLICATION              |\n");
    printf("                 --------------------------------------------------------\n");
}

int main()
{
    const char *directory = "algos";
    char **soFiles;
    int numFiles;
    SchedulingAlgorithm algo;

    getSOFiles(directory, &soFiles, &numFiles);
    printf("Found %d .so files / algorithms :\n", numFiles);
    for (int i = 0; i < numFiles; i++)
    {
        printf("%d : %s\n", i, soFiles[i]);
        // algo = loadSchedulingAlgorithm(soFiles[i]);
        // FILE *file = fopen("pcb.txt", "rt");
        // processus *p = enreg_bcp(file);
        // fclose(file);
        // algo(p);
        // free(soFiles[i]);
    }
    printf("choose algorithm");
    int choice;
    scanf("%d", &choice);
    algo = loadSchedulingAlgorithm(soFiles[choice]); // 1 for testing multi-level

    // free(soFiles);
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    algo(p);

    // // info res[maxim];
    // // code_proc cod[20];

    // if (meth_affich == 1)
    // {
    //     decalge = 38;
    // }
    // else
    // {
    //     decalge = 60;
    // }

    // titre();

    // // char r = getchar();
    // boucle = 1;
    // printf(" \n                             -------------------------------\n");
    // printf("                            |            MAIN MENU          |\n");
    // printf("                             -------------------------------\n");
    // printf("                            |   1 . Loading data            |\n");
    // ;
    // printf("                            |   2 . List of data            |\n");
    // ;
    // printf("                            |   3 . Choice of algorithm     |\n");
    // printf("                            |   4 . Exit                    |\n");
    // printf("                             -------------------------------\n");

    // do
    // {
    //     printf("\t\t\t\t\t your choice : ");
    //     rep = getchar();

    //     if (rep != '1' && rep != '2' && rep != '3' && rep != '4')
    //     {
    //         printf("\nPlease make a choice between 1 and 4 !!\n");
    //         boucle = 1;
    //     }
    //     else
    //     {
    //         boucle = 0;
    //         printf("\033[2J\033[H");
    //     }
    // } while (boucle == 1);
    // do
    // {
    //     boucle = 1;
    //     if (rep == '3')
    //     {
    //         // printf("\n executing basic FIFO from file \n");
    //         // fifo_scheduling(p);

    //         // printf("\n executing Round robin w/ quantum =2 from file \n");
    //         // rr_robin(p, 2);

    //         printf("\n executing SRT w/ quantum =3 from file \n");
    //         srtf(p);

    //         boucle = 0;
    //     }
    // } while (boucle == 1);
    // printf("\033[2J\033[H");

    // displayMenu();
    // int choice;
    // printf("Enter your choice: ");
    // scanf("%d", &choice);
    // char algorithmName[256];
    // snprintf(algorithmName, sizeof(algorithmName), "algos/algorithm%d.so", choice);

    // SchedulingAlgorithm algorithm = loadSchedulingAlgorithm(algorithmName);
    // dlclose(algorithm);
    // rr_robin(p);
    return 0;
}