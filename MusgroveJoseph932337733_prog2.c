#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE

/*
 * Function: processCSVFile
 *   Opens a file, reads and prints each line along with its line number
 *   filePath: path to the file
 */
void processCSVFile(char* filePath) {
    char *currLine = NULL; // To store the current line from the file
    size_t len = 0;        // Buffer length for getline
    ssize_t lineLen;       // Length of the current line
    int lineCount = 0;     // Line number tracker

    // Open the specified file for reading only
    FILE *csvFile = fopen(filePath, "r");

    // Check if the file was opened successfully
    if (csvFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the file line by line
    while ((lineLen = getline(&currLine, &len, csvFile)) != -1) {
        if (lineCount == 0) {
            printf("Header: %s", currLine); // Print header (first line)
        } else {
            printf("Line %d: %s", lineCount, currLine); // Print data rows
        }
        lineCount++;
    }

    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(csvFile);

    printf("\nProcessed file %s\nTotal lines: %d\n", filePath, lineCount);
}

/**
 * Main function to take the file path as a command-line argument
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./parse_csv file.csv\n");
        return EXIT_FAILURE;
    }
    processCSVFile(argv[1]);
    return EXIT_SUCCESS;
}
