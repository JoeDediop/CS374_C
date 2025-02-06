#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

#define PREFIX "movies_"
#define EXT ".csv"
#define MAX_FILENAME 256

// Function to get the largest or smallest file
char* find_file(int find_largest) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char *best_file = NULL;
    long best_size = find_largest ? -1 : LONG_MAX;
    char filepath[MAX_FILENAME];

    dir = opendir(".");
    if (!dir) {
        perror("Unable to open directory");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, PREFIX, strlen(PREFIX)) == 0 && strstr(entry->d_name, EXT)) {
            stat(entry->d_name, &file_stat);
            if ((find_largest && file_stat.st_size > best_size) || (!find_largest && file_stat.st_size < best_size)) {
                best_size = file_stat.st_size;
                if (best_file) free(best_file);
                best_file = strdup(entry->d_name);
            }
        }
    }
    closedir(dir);
    return best_file;
}

// Function to generate a random directory name
void create_random_directory(char *dir_name) {
    srand(time(NULL));
    sprintf(dir_name, "chaudhrn.movies.%d", rand() % 100000);
    mkdir(dir_name, 0755);
}

// Function to process a selected file
void process_file(const char *filename) {
    char dir_name[MAX_FILENAME];
    create_random_directory(dir_name);
    printf("Now processing the chosen file named %s\n", filename);
    printf("Created directory with name %s\n", dir_name);
    // File processing logic here...
}

int main() {
    int choice;
    char filename[MAX_FILENAME];
    char *selected_file;
    
    while (1) {
        printf("\n1. Select file to process\n2. Exit the program\n\nEnter a choice 1 or 2: ");
        scanf("%d", &choice);
        getchar();  // Clear newline
        
        if (choice == 2) break;
        if (choice != 1) continue;

        while (1) {
            printf("\nWhich file you want to process?\n");
            printf("Enter 1 to pick the largest file\n");
            printf("Enter 2 to pick the smallest file\n");
            printf("Enter 3 to specify the name of a file\n\n");
            printf("Enter a choice from 1 to 3: ");
            scanf("%d", &choice);
            getchar();  // Clear newline

            if (choice == 1 || choice == 2) {
                selected_file = find_file(choice == 1);
                if (selected_file) {
                    process_file(selected_file);
                    free(selected_file);
                    break;
                } else {
                    printf("No valid files found. Try again.\n");
                }
            } else if (choice == 3) {
                printf("Enter the complete file name: ");
                scanf("%s", filename);
                getchar();  // Clear newline
                if (access(filename, F_OK) == 0) {
                    process_file(filename);
                    break;
                } else {
                    printf("The file %s was not found. Try again\n", filename);
                }
            } else {
                printf("Invalid choice. Try again.\n");
            }
        }
    }
    return 0;
}

