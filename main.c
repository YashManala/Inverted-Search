#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inverted_search.h"

static void show_menu(void) {
    printf("\n============================================\n");
    printf("             INVERTED SEARCH\n");
    printf("============================================\n");
    printf("1. Create DATABASE\n");
    printf("2. Display Database\n");
    printf("3. Update DATABASE\n");
    printf("4. Search\n");
    printf("5. Save Database\n");
    printf("0. Exit\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");
}

int main(void) {
    WordNode *index = NULL;
    char choice_line[32];
    int choice;
    char filename[MAX_NAME];
    char query[MAX_QUERY];

    printf("INVERTED SEARCH PROJECT\n");
    printf("File list: data/filelist.txt\n");

    for (;;) {
        show_menu();
        if (!fgets(choice_line, sizeof(choice_line), stdin)) break;
        choice = atoi(choice_line);

        switch (choice) {
            case 1:
                free_index(index);
                index = NULL;
                if (create_database_from_filelist(&index, FILE_LIST_PATH) == 0)
                    printf("\nDatabase created successfully.\n");
                else
                    printf("\nDatabase creation failed. Check data/filelist.txt and input files.\n");
                break;

            case 2:
                if (!index) printf("\nDatabase is empty. Choose 1 to create it first.\n");
                else display_database(index);
                break;

            case 3:
                printf("Enter the file name to update (example: data/file2.txt): ");
                if (fgets(filename, sizeof(filename), stdin)) {
                    trim_newline(filename);
                    if (filename[0] && add_file_to_database(&index, filename) == 0) {
                        append_to_filelist(FILE_LIST_PATH, filename);
                        printf("Database updated successfully with %s\n", filename);
                    } else {
                        printf("Could not update database. Check the filename and try again.\n");
                    }
                }
                break;

            case 4:
                if (!index) {
                    printf("\nDatabase is empty. Choose 1 to create it first.\n");
                    break;
                }
                printf("Enter the word you want to search: ");
                if (fgets(query, sizeof(query), stdin)) {
                    trim_newline(query);
                    search_query(index, query);
                }
                break;

            case 5:
                if (!index) printf("\nNothing to save. Create the database first.\n");
                else if (save_database(index, DATABASE_PATH) == 0)
                    printf("Database backup saved to %s\n", DATABASE_PATH);
                else printf("Could not save database.\n");
                break;

            case 0:
                free_index(index);
                printf("Exiting Inverted Search. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please select 0 to 5.\n");
        }
    }

    free_index(index);
    return 0;
}
