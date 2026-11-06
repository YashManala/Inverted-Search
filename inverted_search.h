#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define MAX_NAME 256
#define MAX_WORD 128
#define MAX_QUERY 512
#define FILE_LIST_PATH "data/filelist.txt"
#define DATABASE_PATH "output/database.txt"

typedef struct FileNode {
    char filename[MAX_NAME];
    unsigned int count;
    struct FileNode *next;
} FileNode;

typedef struct WordNode {
    char word[MAX_WORD];
    FileNode *files;
    struct WordNode *next;
} WordNode;

void trim_newline(char *text);
void free_index(WordNode *head);
int create_database_from_filelist(WordNode **head, const char *list_path);
int add_file_to_database(WordNode **head, const char *filename);
void display_database(const WordNode *head);
int save_database(const WordNode *head, const char *database_path);
void search_query(const WordNode *head, const char *query);
int append_to_filelist(const char *list_path, const char *filename);

#endif
