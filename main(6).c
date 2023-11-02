#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_TEXT_LENGTH 1024

void deleteFile(char *filename){
    if (remove(filename) == 0) {
        printf("%s fil slettet:\n", filename);
    } else {
        perror("Kunne ikke slette filen");
    }
}

void displayFileContents(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Kunne ikke aabne filen '%s'\n", filename);
        return;
    }

    char line[MAX_TEXT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void editFileContents(char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Kunne ikke aabne filen '%s'\n", filename);
        return;
    }

    char newContents[MAX_TEXT_LENGTH];
    printf("Indtast den nye tekst (afslut med Ctrl+D i Unix eller Ctrl+Z i Windows):\n");

    while (fgets(newContents, sizeof(newContents), stdin) != NULL) {
        // Remove the trailing newline character
        size_t len = strlen(newContents);
        if (len > 0 && newContents[len - 1] == '\n') {
            newContents[len - 1] = '\0';
        }

        // Append the text with a newline character
        fprintf(file, "%s\n", newContents);
    }

    fclose(file);
}

int createNewFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        printf("Filen eksisterer allerede\n");
        fclose(file);
        return 0; //ud af createFile
     }
    else {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Kunne ikke oprette filen '%s'\n", filename);
            return 0; //ud af createFile
        }
        fclose(file);
    }
    editFileContents(filename);
    return 0;
}

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Indtast filnavn at arbejde paa\n");
    scanf("%s", filename);

    int choice;

    while (1){
        printf("\nMenu:\n");
        printf("1. Vis fil\n");
        printf("2. Rediger fil\n");
        printf("3. Opret fil\n");
        printf("4. Afslut\n");
        printf("Valg: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayFileContents(filename);
                break;
            case 2:
                editFileContents(filename);
                break;
            case 3:
                createNewFile(filename);
                break;
            case 4:
                printf("Afslutter...\n");
                return 0;  //ud af main()
            default:
                printf("Ugyldigt valg. Proev igen.\n");
        }
    }
}
