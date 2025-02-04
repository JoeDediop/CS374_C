#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define MAX_FILENAME 256
#define MAX_LINE 1024
#define MAX_YEAR 3000
#define MIN_YEAR 1000

// Function to generate a random directory name
void generate_random_dir(char *dirname) {
    srand(time(NULL));
    int random_number = rand() % 100000;
    sprintf(dirname, "movies_%d", random_number);
    mkdir(dirname, 0750);
}

// Function to process the CSV file and group movies by year
void process_csv(const char *filename, const char *dirname) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        char title[MAX_FILENAME];
        int year;
        float rating;

        if (sscanf(line, "%[^,],%d,%f", title, &year, &rating) == 3) {
            if (year < MIN_YEAR || year > MAX_YEAR) continue;

            char filepath[MAX_FILENAME];
            sprintf(filepath, "%s/%d.txt", dirname, year);

            FILE *year_file = fopen(filepath, "a");
            if (year_file) {
                fprintf(year_file, "%s, %.1f\n", title, rating);
                fclose(year_file);
            }
        }
    }

    fclose(file);
}

// Main function
int main() {
    char filename[MAX_FILENAME];
    char dirname[MAX_FILENAME];
    
    printf("Enter the CSV filename: ");
    scanf("%255s", filename);

    generate_random_dir(dirname);
    printf("Created directory: %s\n", dirname);
    
    process_csv(filename, dirname);
    printf("Processing completed.\n");

    return 0;
}
