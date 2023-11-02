#include <stdio.h>
#include <time.h>

#define MAX_ENTRY_LENGTH 1024
char entry[MAX_ENTRY_LENGTH];

void insertDateLine(FILE *file){
    // Get the current date and time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);  //hent alle sekunder siden 1970
    timeinfo = localtime(&rawtime); // formater disse sekunder som beskrevet i strukturen tm

    // Format the date and time
    char currentDate[80];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d %H:%M:%S", timeinfo);  //formater efter eget valg og put i currentdate

    // Insert the date line and prompt
    fprintf(file, "Diary entry for %s\n", currentDate);  // gem i filen
}

int main() {
    // OPEN FILE
    FILE *file = fopen("C:/Users/Ruben Long Schlong/scrimblo/diary.txt", "a+"); //a = add/append
    if (!file) {
        perror("Error: Unable to open diary file");
        return 1;
    }

    insertDateLine(file);

    printf("Enter your diary entry below (Ctrl+Z to save and exit):\n");
    while (fgets(entry, sizeof(entry), stdin) != NULL) {
        fprintf(file, "%s\n", entry);
    }

    //CLOSE FILE
    fclose(file);
    printf("Diary entry saved.\n");

    return 0;
}
