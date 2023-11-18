// #include <stdio.h>
// #include <stdlib.h>

#include <dirent.h>

#include <dlfcn.h>

#include "misc.h" // miscellaneous functs/structs..

// #include <string.h>
// #include <ctype.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#define maxim 500     // the maximum stop time
#define meth_affich 1 // to choose the display method of the grill either 1 or 2

// TINKERING W/ GTK
GtkWidget *window;
GtkBuilder *builder;
GtkStack *stack1;
GtkBox *algorithm_box;

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
    printf("loading scheduling algo from lib");
    // LOCAL VERSION
    snprintf(fullPath, sizeof(fullPath), "algos/%s", algorithmName);
    // INSTALLATION VERSION
    // snprintf(fullPath, sizeof(fullPath), "/usr/local/lib/algos/%s", algorithmName);
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
// VERY BASIC GUI
// button switches  between pages
void on_switchbutton_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page2");
    g_print("switching to other page");
}
void on_switchbutton1_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page1");
}
void on_algorithm_button_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *algorithm_name = gtk_button_get_label(button);
    gtk_stack_set_visible_child_name(stack1, "page2");
    SchedulingAlgorithm algo=loadSchedulingAlgorithm(g_strdup(algorithm_name));
    
    g_print("Algorithm selected: %s\n", algorithm_name);
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_bcp(file);
    fclose(file);
    algo(p);
}

void commandLine()
{
    // LOCAL VERSION
    const char *directory = "algos";
    // INSTALLATION VERSION
    // const char *directory = "/usr/local/lib/algos";

    char **soFiles;
    int numFiles;
    SchedulingAlgorithm algo;
    getSOFiles(directory, &soFiles, &numFiles);
    printf("Found %d .so files / algorithms :\n", numFiles);
    // generateFile();
    for (int i = 0; i < numFiles; i++)
    {
        printf("%d : %s\n", i, soFiles[i]);
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
}
int main(int argc, char *argv[])
{
    // start w/ the command line, find the .so files
    // commandLine();
    const char *directory = "algos";
    char **soFiles;
    int numFiles;
    SchedulingAlgorithm algo;
    getSOFiles(directory, &soFiles, &numFiles);

    gtk_init(&argc, &argv);
    // very basic GUI
    // LOCAL VERSION
    builder = gtk_builder_new_from_file("prototype.glade");
    // INSTALLATION VERSION
    // builder = gtk_builder_new_from_file("/usr/local/lib/prototype.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    stack1 = GTK_STACK(gtk_builder_get_object(builder, "stack1"));
    algorithm_box = GTK_BOX(gtk_builder_get_object(builder, "algorithm_box"));
    // generate the buttons
    for (int i = 0; i < numFiles; i++)
    {
        g_print("huh %d : %s\n", i, soFiles[i]);
        gchar *function_name = soFiles[i];
        // Create a button with the function name
        GtkWidget *button = gtk_button_new_with_label(function_name);
        g_signal_connect(button, "clicked", G_CALLBACK(on_algorithm_button_clicked), NULL);
        gtk_box_pack_start(algorithm_box, button, FALSE, FALSE, 0);
        g_free(function_name);
    }

    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}