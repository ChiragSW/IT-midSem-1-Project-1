#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
        printf("\n ### All entries deleted ###\n");
    } 
    else 
    {
        printf("!! Error deleting entries !!\n");
    }
}

void editEntries()
{



    //Isko try karke dekho koi



}

int main() 
{
    int choice;
    while (1) 
    {
        printf("\n=== Diary ===\n");
        printf("\n");
        printf("1. Write new entry\n");
        printf("2. View entries\n");
        printf("3. Delete all entries\n");
        printf("4. Exit\n");
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
                printf("Bye user!\n");
                return 0;               
            default:
                printf("Please choose a valid option.\n");
        }
    }
    return 0;
}
