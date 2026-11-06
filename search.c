#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "inverted_search.h"

static const WordNode *find_word(const WordNode *head, const char *target) {
    while (head && strcmp(head->word, target) < 0) head = head->next;
    if (head && strcmp(head->word, target) == 0) return head;
    return NULL;
}

void search_query(const WordNode *head, const char *query) {
    char token[MAX_WORD];
    int length = 0, found_any = 0;
    const char *p;

    printf("\n--------------- SEARCH RESULTS ---------------\n");
    for (p = query; ; ++p) {
        int ch = (unsigned char)*p;
        if (isalpha(ch)) {
            if (length < MAX_WORD - 1) token[length++] = (char)ch;
        } else {
            if (length > 0) {
                const WordNode *match;
                token[length] = '\0';
                match = find_word(head, token);
                if (match) {
                    const FileNode *file;
                    found_any = 1;
                    printf("Word \"%s\" is present in:\n", token);
                    for (file = match->files; file; file = file->next)
                        printf("  In file: %s  %u time(s)\n", file->filename, file->count);
                } else {
                    printf("Word \"%s\" was not found in the database.\n", token);
                }
                length = 0;
            }
            if (*p == '\0') break;
        }
    }
    if (!found_any) printf("No matching words were found.\n");
    printf("-----------------------------------------------\n");
}
