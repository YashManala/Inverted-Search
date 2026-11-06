#include <stdio.h>
#include "inverted_search.h"

void display_database(const WordNode *head) {
    const WordNode *word;
    printf("\n================ DATABASE ================\n");
    printf("%-22s %-12s %s\n", "WORD", "FILE COUNT", "FILE DETAILS (filename: occurrences)");
    printf("---------------------------------------------------------------\n");

    for (word = head; word; word = word->next) {
        const FileNode *file;
        int file_count = 0;
        for (file = word->files; file; file = file->next) file_count++;

        printf("%-22s %-12d ", word->word, file_count);
        for (file = word->files; file; file = file->next) {
            printf("%s:%u", file->filename, file->count);
            if (file->next) printf(", ");
        }
        printf("\n");
    }
    printf("===========================================\n");
}

int save_database(const WordNode *head, const char *database_path) {
    FILE *fp = fopen(database_path, "w");
    const WordNode *word;
    if (!fp) return -1;

    fprintf(fp, "# INVERTED INDEX DATABASE\n");
    fprintf(fp, "# WORD | FILE_COUNT | FILENAME:OCCURRENCES\n");
    for (word = head; word; word = word->next) {
        const FileNode *file;
        int file_count = 0;
        for (file = word->files; file; file = file->next) file_count++;
        fprintf(fp, "%s | %d | ", word->word, file_count);
        for (file = word->files; file; file = file->next) {
            fprintf(fp, "%s:%u", file->filename, file->count);
            if (file->next) fprintf(fp, ", ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
