/*
William Moore
wmoore02@uoguelph.ca
1061752
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LINE_LENGTH 256

struct node_struct{
    void *data;
    struct node_struct *next;
};

enum type{
    one,
    two,
    three
};

struct node_struct* txt2Words(FILE *fp);

char* getWord(char** mainString);

enum type classifyCharacter(char theChar);

struct node_struct* addNode(void* stringData);

struct node_struct* search(struct node_struct *list, char *target, int (*compar)(const void*, const void*));

struct node_struct* copy(struct node_struct *start, struct node_struct *end);

void ftext(FILE *fp, struct node_struct *list);

int compareString(const void* arg1, const void* arg2);

struct node_struct* sort(struct node_struct *list, int (*compar)(const void*, const void*));

void mergeSplit(struct node_struct *list, struct node_struct **front, struct node_struct **back);

void mergeSort(struct node_struct **list, int (*compar)(const void*, const void*));

struct node_struct* merge(struct node_struct *front, struct node_struct *back, int (*compar)(const void*, const void*));

void removeNode(struct node_struct *previous, struct node_struct *toRemove);

void remove_repeats(struct node_struct *list, int (*compar)(const void*, const void*));

int length(struct node_struct *list);

void free_list(struct node_struct *list, int free_data);