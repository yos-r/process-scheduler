#include <dirent.h>
#include <dlfcn.h>
#include "misc.h"
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

GtkWidget *window;
GtkBuilder *builder;
GtkStack *stack1;
GtkBox *algorithm_box;
GtkWidget *draw1;
GtkButton *configpcb;
GtkWidget *labelcheck;
GtkWidget *maxNumber;
GtkWidget *maxArrival;
GtkWidget *maxPrio;
GtkWidget *maxExec;

typedef struct
{
    gint value1;
    gint value2;
    gint value3;
    gint value4;
} SpinButtonValues;

typedef void (*SchedulingAlgorithm)(processus *);
void extractFunctionName(const char *algorithmName, char *functionName)
{
    const char *lastDot = strrchr(algorithmName, '.');
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
    // LOCAL VERSION DO NOT REMOVE
    // snprintf(fullPath, sizeof(fullPath), "algos/%s", algorithmName);
    snprintf(fullPath, sizeof(fullPath), "/usr/local/lib/algos/%s", algorithmName);
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
    DIR *dir = opendir(directory);
    if (!dir)
    {
        fprintf(stderr, "Error opening directory!!!: %s\n", directory);
        exit(EXIT_FAILURE);
    }

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { 
            const char *dot = strrchr(entry->d_name, '.');
            if (dot != NULL && strcmp(dot, ".so") == 0)
            {
                count++;
            }
        }
    }
    rewinddir(dir);

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

    if ((dir = opendir("algos")) != NULL)
    {
        int option = 1;

        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG && strstr(ent->d_name, ".c") != NULL)
            {
                char algorithmName[300];
                snprintf(algorithmName, sizeof(algorithmName), "algos/%s", ent->d_name);

                SchedulingAlgorithm algorithm = loadSchedulingAlgorithm(algorithmName);

                printf("%d. %s\n", option, ent->d_name);

                option++;
            }
        }

        closedir(dir);
    }
    else
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
}

void title(void)
{
    printf("                 --------------------------------------------------------\n");
    printf("                |                     ~~ (❁´◡`❁) ~~                    |\n");
    printf("                |                PROCESS SCHEDULER APPLICATION              |\n");
    printf("                 --------------------------------------------------------\n");
}
void on_switchbutton_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page2");
}
void on_switchbutton1_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page1");
}
void on_configpcb_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page4");
    gtk_label_set_text(GTK_LABEL(labelcheck), "");
}
void on_feelingLucky_clicked(GtkButton *b)
{
    generateFile();
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    sortProcesses(p);
    gtk_stack_set_visible_child_name(stack1, "page1");

    fclose(file);
}
void on_generateFile_clicked(GtkButton *b, gpointer user_data)
{
    SpinButtonValues *values = (SpinButtonValues *)user_data;
    values->value1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "maxNumber")));
    values->value2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "maxArrival")));
    values->value3 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "maxExec")));
    values->value4 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "maxPrio")));
    generateFileParam(values->value1, values->value2, values->value3, values->value4);
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    fclose(file);
    displayTab(p);
    gtk_stack_set_visible_child_name(stack1, "page1");
}
void on_configRandom_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page3");
}
void on_goback1_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page4");
    gtk_label_set_text(GTK_LABEL(labelcheck), " ");
}
void on_goback_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page4");
    gtk_label_set_text(GTK_LABEL(labelcheck), " ");
}
void on_inputPCBfile_clicked(GtkButton *b)
{
    gtk_stack_set_visible_child_name(stack1, "page2");
}
void on_choosePCB_file_set(GtkFileChooserButton *fileChooserButton, gpointer user_data)
{
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileChooserButton));
    g_print("Selected file: %s\n", filename);

    FILE *selectedFile = fopen(filename, "r");
    if (!selectedFile)
    {
        g_print("Error opening selected file: %s\n", filename);
        g_free(filename);
        return;
    }

    FILE *destinationFile = fopen("pcb.txt", "w");
    if (!destinationFile)
    {
        g_print("Error opening destination file: pcb.txt\n");
        fclose(selectedFile);
        g_free(filename);
        return;
    }
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), selectedFile)) > 0)
    {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(selectedFile);
    fclose(destinationFile);
    g_free(filename);
    if (!verifFile())
    {
        gtk_label_set_text(GTK_LABEL(labelcheck), "File is empty ! Try again");
    }
    else
    {
        g_print("File is valid ! ");
        gtk_stack_set_visible_child_name(stack1, "page1");
    }
}

void on_algorithm_button_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *algorithm_name = gtk_button_get_label(button);
    gtk_window_set_title(GTK_WINDOW(window), g_strdup(algorithm_name));
    SchedulingAlgorithm algo = loadSchedulingAlgorithm(g_strdup(algorithm_name));
    g_print("\n Algorithm selected: %s\n", algorithm_name);
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    fclose(file);
    algo(p);
}

void commandLine()
{
    // LOCAL VERSION
    // const char *directory = "algos";
    // INSTALLATION VERSION
    const char *directory = "/usr/local/lib/algos";

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
    algo = loadSchedulingAlgorithm(soFiles[choice]); 
    // free(soFiles);
    FILE *file = fopen("pcb.txt", "rt");
    processus *p = enreg_pcb(file);
    fclose(file);
    algo(p);
}

int main(int argc, char *argv[])
{
    title();
    const char *directory = "/usr/local/lib/algos";
    char **soFiles;
    int numFiles;
    SchedulingAlgorithm algo;
    getSOFiles(directory, &soFiles, &numFiles);

    gtk_init(&argc, &argv);
    // builder = gtk_builder_new_from_file("prototype.glade");
    builder = gtk_builder_new_from_file("/usr/local/lib/prototype.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    stack1 = GTK_STACK(gtk_builder_get_object(builder, "stack1"));
    algorithm_box = GTK_BOX(gtk_builder_get_object(builder, "algorithm_box"));
    configpcb = GTK_BUTTON(gtk_builder_get_object(builder, "generateFile"));
    labelcheck = GTK_WIDGET(gtk_builder_get_object(builder, "vibecheck"));
    SpinButtonValues spin_button_values = {0, 0, 0, 0};
    g_signal_connect(configpcb, "clicked", G_CALLBACK(on_generateFile_clicked), &spin_button_values);
    for (int i = 0; i < numFiles; i++)
    {
        gchar *function_name = soFiles[i];
        GtkWidget *button = gtk_button_new_with_label(function_name);
        g_signal_connect(button, "clicked", G_CALLBACK(on_algorithm_button_clicked), NULL);
        gtk_box_pack_start(algorithm_box, button, FALSE, FALSE, 0);
        g_free(function_name);
    }
    gtk_widget_show_all(window);
    gtk_main();
    return EXIT_SUCCESS;
}