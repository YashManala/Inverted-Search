#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inverted_search.h"

/* Insert a word into the alphabetically sorted word linked list.
   If the word already exists, update its filename list. */
static int store_word(WordNode **head, const char *word, const char *filename) {
    WordNode *current = *head, *previous = NULL;
    while (current && strcmp(current->word, word) < 0) {
        previous = current;
        current = current->next;
    }

    if (!current || strcmp(current->word, word) != 0) {
        WordNode *new_word = (WordNode *)calloc(1, sizeof(WordNode));
        if (!new_word) return -1;
        snprintf(new_word->word, sizeof(new_word->word), "%s", word);
        new_word->next = current;
        if (previous) previous->next = new_word;
        else *head = new_word;
        current = new_word;
    }

    FileNode *file = current->files, *last = NULL;
    while (file && strcmp(file->filename, filename) != 0) {
        last = file;
        file = file->next;
    }

    if (!file) {
        file = (FileNode *)calloc(1, sizeof(FileNode));
        if (!file) return -1;
        snprintf(file->filename, sizeof(file->filename), "%s", filename);
        if (last) last->next = file;
        else current->files = file;
    }
    file->count++;
    return 0;
}

static int process_file(WordNode **head, const char *filename) {
    FILE *fp = fopen(filename, "r");
    int ch, length = 0;
    char word[MAX_WORD];

    if (!fp) {
        fprintf(stderr, "Warning: cannot open input file: %s\n", filename);
        return -1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalpha((unsigned char)ch)) {
            if (length < MAX_WORD - 1)
                word[length++] = (char)ch;
        } else if (length > 0) {
            word[length] = '\0';
            if (store_word(head, word, filename) != 0) {
                fclose(fp);
                return -1;
            }
            length = 0;
        }
    }

    if (length > 0) {
        word[length] = '\0';
        if (store_word(head, word, filename) != 0) {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

int add_file_to_database(WordNode **head, const char *filename) {
    if (!filename || !filename[0]) return -1;
    return process_file(head, filename);
}

int create_database_from_filelist(WordNode **head, const char *list_path) {
    FILE *list = fopen(list_path, "r");
    char filename[MAX_NAME];
    int files_read = 0, failures = 0;

    if (!list) {
        fprintf(stderr, "Cannot open file list: %s\n", list_path);
        return -1;
    }

    while (fgets(filename, sizeof(filename), list)) {
        trim_newline(filename);
        if (filename[0] == '\0' || filename[0] == '#') continue;
        if (process_file(head, filename) == 0) {
            printf("Indexed file: %s\n", filename);
            files_read++;
        } else failures++;
    }
    fclose(list);

    printf("Files indexed: %d", files_read);
    if (failures) printf(" | Files skipped: %d", failures);
    printf("\n");
    return (files_read > 0) ? 0 : -1;
}

int append_to_filelist(const char *list_path, const char *filename) {
    FILE *fp = fopen(list_path, "a");
    if (!fp) return -1;
    fprintf(fp, "%s\n", filename);
    fclose(fp);
    return 0;
}

void trim_newline(char *text) {
    if (!text) return;
    text[strcspn(text, "\r\n")] = '\0';
}

void free_index(WordNode *head) {
    while (head) {
        WordNode *next_word = head->next;
        FileNode *file = head->files;
        while (file) {
            FileNode *next_file = file->next;
            free(file);
            file = next_file;
        }
        free(head);
        head = next_word;
    }
}
