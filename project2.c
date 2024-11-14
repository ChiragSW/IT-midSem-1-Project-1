#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "diary.txt"
#define MAX_ENTRY_LENGTH 4096

void writeEntry() 
{
    char date[100];

    printf("Today's date: ");
    scanf("%s", &date);

    if(strlen(date) != 10)
    {
        printf("Enter a valid date");
        return;
    }

    FILE *file = fopen(FILENAME, "a");
    if (!file) 
    {
        printf("Error opening file.\n");
        return;
    }

    char entry[MAX_ENTRY_LENGTH];
    printf("[Enter your diary entry]\n");
    getchar();
    fgets(entry, MAX_ENTRY_LENGTH, stdin);

    fprintf(file, "Date : %s\n%s\n---\n", date, entry);
    fclose(file);
    printf("Entry saved!\n");
}

void viewEntries() 
{
    FILE *file = fopen(FILENAME, "r");
    if (!file) 
    {
        printf("No entries found.\n");
        return;
    }

    printf("##################################################################################################\n");
    char line[MAX_ENTRY_LENGTH];
    while (fgets(line, sizeof(line), file)) 
    {
        printf("%s", line);
    }
    fclose(file);
}

void deleteEntries() 
{
    if (remove(FILENAME) == 0) 
    {
        printf("\n ### All previous entries deleted ###\n");
    } 
    else 
    {
        printf("!! Error deleting entries !!\n");
    }
}

void editEntries()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file) 
    {
        printf("No entries found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) 
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char date[100], line[MAX_ENTRY_LENGTH], newEntry[MAX_ENTRY_LENGTH];
    int found = 0;

    printf("Enter the date of the entry to edit (DD-MM-YYYY): ");
    scanf("%s", date);

    // Loop through each line in the file
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Date : ") && strstr(line, date)) {
            found = 1;
            fprintf(tempFile, "%s", line); // Copy the date line
            printf("Enter the new entry: ");
            getchar(); // Clear newline character
            fgets(newEntry, MAX_ENTRY_LENGTH, stdin);
            fprintf(tempFile, "%s---\n", newEntry); // Write new entry followed by separator line
    // Skip the old entry until the "---" separator
            while (fgets(line, sizeof(line), file) && strcmp(line, "---\n") != 0) {}
        } else {
            fprintf(tempFile, "%s", line); // Copy lines as-is
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace old file with updated temp file
    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Entry updated!\n");
    } else {
        printf("Entry not found for the specified date.\n");
        remove("temp.txt");
    }
}

int main() 
{
    int choice;
    while (1) 
    {
        printf("\n===== Personal Diary =====\n");
        printf("\n");
        printf("1. Write new entry\n");
        printf("2. View entries\n");
        printf("3. Delete all entries\n");
        printf("4. Edit a previous entry \n");
        printf("5. Exit\n");
        printf("Choose number of what to do: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                writeEntry();
                break;
            case 2:
                viewEntries();
                break;
            case 3:
                deleteEntries();
                break;
            case 4:
                editEntries();    
            case 5:
                printf("<< Bye user >>\n");
                return 0;               
            default:
                printf("Please choose a valid option.\n");
        }
    }
    return 0;
}
