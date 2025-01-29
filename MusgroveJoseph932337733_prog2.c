#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the movie structure
struct movie {
    char *title;
    int year;
    char *languages;
    float rating;
    struct movie *next;
};

/* Function prototypes */
struct movie* createMovie(char *line);
struct movie* buildMovieList(char *filePath, int *movieCount);
void printMovieList(struct movie *list);
void showMoviesByYear(struct movie *list, int year);
void showHighestRatedMovies(struct movie *list);
void showMoviesByLanguage(struct movie *list, char *language);
void freeMovieList(struct movie *list);
void displayMenu(struct movie *movieList, int movieCount);

/*
 * Creates a movie structure from a single line of CSV data.
 */
struct movie* createMovie(char *line) {
    struct movie *newMovie = malloc(sizeof(struct movie));
    char *token;

    // Title
    token = strtok(line, ",");
    newMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(newMovie->title, token);

    // Year
    token = strtok(NULL, ",");
    newMovie->year = atoi(token);

    // Languages
    token = strtok(NULL, ",");
    newMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(newMovie->languages, token);

    // Rating
    token = strtok(NULL, ",");
    newMovie->rating = strtof(token, NULL);

    newMovie->next = NULL;
    return newMovie;
}

/*
 * Reads a CSV file and creates a linked list of movies.
 * Also counts the number of movies processed.
 */
struct movie* buildMovieList(char *filePath, int *movieCount) {
    char *currLine = NULL;
    size_t len = 0;
    int lineLen;
    struct movie *head = NULL;
    struct movie *tail = NULL;

    FILE *csvFile = fopen(filePath, "r");
    if (csvFile == NULL) {
        perror("Error opening file");
        return NULL;
    }

    *movieCount = 0;
    while ((lineLen = getline(&currLine, &len, csvFile)) != -1) {
        if (*movieCount == 0) { // Skip the header line
            (*movieCount)++;
            continue;
        }
        struct movie *newMovie = createMovie(currLine);
        if (head == NULL) {
            head = newMovie;
            tail = newMovie;
        } else {
            tail->next = newMovie;
            tail = newMovie;
        }
        (*movieCount)++;
    }

    free(currLine);
    fclose(csvFile);
    (*movieCount)--; // Adjust for the header line
    return head;
}

/*
 * Prints movies released in a specific year.
 */
void showMoviesByYear(struct movie *list, int year) {
    int found = 0;
    struct movie *current = list;
    while (current != NULL) {
        if (current->year == year) {
            printf("Title: %s, Languages: %s, Rating: %.1f\n",
                   current->title, current->languages, current->rating);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("No movies found for the year %d.\n", year);
    }
}

/*
 * Displays the highest-rated movie for each year.
 */
void showHighestRatedMovies(struct movie *list) {
    struct movie *current;
    struct movie *highest;

    for (int year = 1900; year <= 2025; year++) {
        current = list;
        highest = NULL;

        while (current != NULL) {
            if (current->year == year) {
                if (highest == NULL || current->rating > highest->rating) {
                    highest = current;
                }
            }
            current = current->next;
        }

        if (highest != NULL) {
            printf("Year: %d, Title: %s, Rating: %.1f\n", highest->year, highest->title, highest->rating);
        }
    }
}

/*
 * Shows movies available in a specific language.
 */
void showMoviesByLanguage(struct movie *list, char *language) {
    struct movie *current = list;
    int found = 0;

    while (current != NULL) {
        if (strstr(current->languages, language) != NULL) {
            printf("Title: %s, Year: %d, Rating: %.1f\n",
                   current->title, current->year, current->rating);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No data about movies released in %s.\n", language);
    }
}

/*
 * Frees all memory allocated for the linked list of movies.
 */
void freeMovieList(struct movie *list) {
    struct movie *current = list;

    while (current != NULL) {
        struct movie *temp = current;
        current = current->next;

        free(temp->title);
        free(temp->languages);
        free(temp);
    }
}

/*
 * Main menu for user interaction.
 */
void displayMenu(struct movie *movieList, int movieCount) {
    int choice;
    do {
        printf("\n====== Movie Menu ======\n");
        printf("1. Show movies released in a specific year\n");
        printf("2. Show highest-rated movie for each year\n");
        printf("3. Show movies with a specific language\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int year;
            printf("Enter the release year: ");
            scanf("%d", &year);
            showMoviesByYear(movieList, year);
        } else if (choice == 2) {
            showHighestRatedMovies(movieList);
        } else if (choice == 3) {
            char language[50];
            printf("Enter a language: ");
            scanf("%s", language);
            showMoviesByLanguage(movieList, language);
        } else if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
        } else {
            printf("You entered an incorrect choice. Try again.\n");
        }
    } while (choice != 4);
}

/*
 * Main function
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }

    int movieCount = 0;
    struct movie *movieList = buildMovieList(argv[1], &movieCount);
    if (movieList == NULL) {
        printf("Failed to process the file.\n");
        return EXIT_FAILURE;
    }

    printf("Processed file %s and parsed data for %d movies\n", argv[1], movieCount);

    displayMenu(movieList, movieCount);
    freeMovieList(movieList);
    return EXIT_SUCCESS;
}
