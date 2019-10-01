/*
William Moore
wmoore02@uoguelph.ca
1061752
*/
#include<stdio.h>
#include<stdlib.h>

struct node_struct{
    void *data;
    struct node_struct *next;
};

struct node_struct* txt2Words(FILE *fp);

struct node_struct* search(struct node_struct *list, char *target, int (*compar)(const void*, const void*));

struct node_struct* copy(struct node_struct *start, struct node_struct *end);

void ftext(FILE *fp, struct node_struct *list);

struct node_struct* sort(struct node_struct *list, int (*compar)(const void*, const void*));

void remove_repeats(struct node_struct *list, int (*compar)(const void*, const void*));

int length(struct node_struct *list);

void free_list(struct node_struct *list, int free_data);