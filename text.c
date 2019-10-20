/*
Name: William Moore
Email: wmoore02@uoguelph.ca
Student Num: 1061752
*/

#include"text.h"

struct node_struct* txt2Words(FILE *fp){
    /*For characters that are not included 
    in ascii, put it in its own category. 
    will not be marked on how these are handled*/
    int i = 0;
    struct node_struct *head, **runningStruct;
    char* wordIn;
    char* wordInStart;
    char* temp;
    /*point the struct building to head*/
    runningStruct = &head;
    /*Iterate through file*/
    while(1){
        wordIn = calloc(MAX_LINE_LENGTH, sizeof(char));
        wordInStart = wordIn;
        wordIn = fgets(wordIn, MAX_LINE_LENGTH, fp);
        /*Break at end of file*/
        if(wordIn == NULL){
            free(wordInStart);
            break;
        }

        for(i = 0; i < strlen(wordIn); i++){
            if(wordIn[i] == '\r'){
                wordIn[i] = '\n';
                wordIn[i + 1] = '\0';
            }
        }
        /*iterate through the line*/
        while(strlen(wordIn) != 0){
            /*gets word and checks for null character*/
            temp = getWord(&wordIn);
            if(temp[0] != '\0'){
                *runningStruct = addNode(temp);
                runningStruct = &((*runningStruct)->next);
            } else {
                free(temp);
                temp = NULL;
            }
        }
        wordIn = wordInStart;
        free(wordIn);
    }
    return head;
}

char* getWord(char** mainString){
    int i, type;
    int lastIsSpace = 0;
    char* toReturn;
    type = classifyCharacter(*mainString[0]);

    for(i = 0; i < strlen(*mainString); i++){
        if(type == one){
            if((*mainString)[i] == '\'' || (*mainString)[i] == '-'){
                if((*mainString)[i + 1] == (*mainString)[i] || (*mainString)[i + 1] == ' '){
                    break;
                }
            } else if(isspace((*mainString)[i])){
                lastIsSpace = 1;
                break;
            } else if(ispunct((*mainString)[i])){
                break;
            }
        } else if(type == two){
            if((*mainString)[i] != (*mainString)[i + 1]){
                if((*mainString)[i + 1] == ' ' || (*mainString)[i + 1] == '\n'){
                    lastIsSpace = 1;
                }
                i++;
                break;
            }
        } else if(type == three){
            toReturn = calloc(2, 1);
            strcpy(toReturn, "\n");
            *mainString += 2;
            return toReturn;
        }
    }
    toReturn = calloc(1, i + 1);
    strncpy(toReturn, *mainString, i);
    *mainString += (i + lastIsSpace);
    return toReturn;
}

enum type classifyCharacter(char theChar){
    static int classifyCount = 0;
    if(isalpha((theChar) || isdigit(theChar) || theChar == '-' || theChar == '\'')){
        classifyCount++;
        return one;
    }

    if(ispunct(theChar)){
        classifyCount++;
        return two;
    }

    if(classifyCount == 0 && theChar == '\n'){
        return three;
    } else {
        classifyCount = 0;
        return one;
    }
}

struct node_struct* addNode(void* theData){
    /*Allocate new structure*/
    struct node_struct* toReturn = malloc(sizeof(struct node_struct));
    /*Assign proper values*/
    toReturn->data = theData;
    toReturn->next = NULL;
    /*printf("%s\n", (char*)theData);*/
    return toReturn;
}

struct node_struct* search(struct node_struct *list, char *target, int (*compar)(const void*, const void*)){
    struct node_struct *head, **builder;
    /*initialize head*/
    head = NULL;
    /*double pointer to start reading in */
    builder = &head;
    /*loop through entirety of list*/
    while(list){
        /*checks for matches*/
        if(!compar(target, list->data)){
            /*adds nodes and points builder to the next node*/
            *builder = addNode(list);
            builder = &((*builder)->next);
        }
        /*go to the next element in the list*/
        list = list->next;
    }
    return head;
}

struct node_struct* copy(struct node_struct *start, struct node_struct *end){
    struct node_struct *head, **builder;
    /*double pointer assignment*/
    builder = &head;
    while(start){
        /*create new nodes, copying them from the given list*/
        *builder = addNode(start->data);
        builder = &((*builder)->next);

        /*check for the next element being the end element*/
        if(start->next && start->next == end){
            break;
        }

        /*go to next element*/
        start = start->next;
    }
    return head;
}

void ftext(FILE *fp, struct node_struct *list){
    int lineLen = 0;
    int printSpaceChar = 0;
    /*iterate through list*/
    while(list){
        /*print element*/
        fprintf(fp, "%s", (char*)list->data);
        lineLen += (strlen((char*)list->data));
        /*check the existence of the next element*/
        if(list->next){
            if((((char*)(list->data))[0] == ',' || ((char*)(list->data))[0] == '\'' || ((char*)(list->data))[0] == '!' || ((char*)(list->data))[0] == '.' ) && (((char*)(list->next->data))[0] != '"' && strcmp((char*)(list->next->data), "--"))){
                /*check for sentence ending punctuation*/
                printSpaceChar = 1;
            } else if(isalnum(((char*)(list->data))[0]) && isalnum(((char*)(list->next->data))[0])){
                /*check for alphanumeric*/
                printSpaceChar = 1;
            }
            /*check to print out newline or space depending on line length*/
            if((printSpaceChar && (lineLen + strlen((char*)list->next->data)) >= 80) || ((char*)(list->data))[0] == '\n'){
                /*print newline*/
                /*fprintf(fp, "%d", (lineLen + strlen((char*)list->next->data)));*/
                fprintf(fp, "\n");
                printSpaceChar = 0;
                lineLen = 0;
            } else {
                /*check for flag*/
                if(printSpaceChar){
                    /*print space*/
                    fprintf(fp, " ");
                    printSpaceChar = 0;
                    lineLen++;
                }
            }
        } else {
            /*prints newline at the end of the print*/
            fprintf(fp, "\n");
        }
        list = list->next;
    }
    return;
}

int compareString(const void* arg1, const void* arg2){
    /*cast arguments to string*/
    char* str1 = (char*)arg1;
    char* str2 = (char*)arg2;
    /*compare them*/
    return strcmp(str1, str2);
}

struct node_struct* sort(struct node_struct *list, int (*compar)(const void*, const void*)){
    struct node_struct* toSort;
    /*copy list to new list*/
    toSort = copy(list, NULL);
    /*sort list with mergeSort*/
    mergeSort(&toSort, compar);
    /*return sorted list*/
    return toSort;
}

void mergeSplit(struct node_struct *list, struct node_struct **front, struct node_struct **back){
    int listLen = length(list), counter = 0;
    struct node_struct **frontList = NULL, **backList = NULL;
    /*assign new variables so as to preserve values outside the function*/
    frontList = front;
    backList = back;
    /*iterate through given list*/
    while(list){
        /*check for midpoint in list*/
        if(counter < (listLen / 2)){
            /*add nodes to the front list*/
            *frontList = list;
            frontList = &((*frontList)->next);
        } else {
            /*add nodes to the back list*/
            *backList = list;
            backList = &((*backList)->next);
        }
        /*move to next node*/
        list = list->next;
        counter++;
    }
    /*point the end of the front list to NULL*/
    (*frontList) = NULL;
}

void mergeSort(struct node_struct **list, int (*compar)(const void*, const void*)){
    /*create instance variables*/
    struct node_struct *front = NULL, *back = NULL;
    /*recursive base case for when there are 0 or 1 elements*/
    if(*list == NULL || (*list)->next == NULL){
        return;
    }

    /*split the current list into two halves: front and back*/
    /*double pointers being used here to get the information out*/
    mergeSplit(*list, &front, &back);

    /*recursively sort the two halves of the list*/
    mergeSort(&front, compar);
    mergeSort(&back, compar);

    /*merge halves and return the head*/
    *list = merge(front, back, compar);
}

struct node_struct* merge(struct node_struct *front, struct node_struct *back, int (*compar)(const void*, const void*)){
    struct node_struct *head, **runningStruct;
    int combinedLength = 0, counter = 0;
    /*double pointer for returning*/
    runningStruct = &head;
    /*get the length of the final list*/
    combinedLength = length(front) + length(back);
    /*build list*/
    while(counter < combinedLength){
        if(front == NULL){
            /*return the back list if the front list is empty*/
            *runningStruct = back;
            break;
        } else if(back == NULL){
            /*return the front list if the back list is empty*/
            *runningStruct = front;
            break;
        }

        if(compar(front->data, back->data) < 0){
            /*add fronts node*/
            *runningStruct = front;
            runningStruct = &((*runningStruct)->next);
            front = front->next;
        } else {
            /*add backs node*/
            *runningStruct = back;
            runningStruct = &((*runningStruct)->next);
            back = back->next;
        }
        counter++;
    }
    return head;
}

void removeNode(struct node_struct *previous, struct node_struct *toRemove){
    /*move next pointer past the removed node*/
    previous->next = toRemove->next;
    /*free the node*/
    free(toRemove);
    toRemove = NULL;
    return;
}

void remove_repeats(struct node_struct *list, int (*compar)(const void*, const void*)){
    struct node_struct **head;
    /*double pointer for building new list without repeats*/
    head = &list;
    /*iterate through list*/
    while(list){
        /*check for existence of next element*/
        if(list->next){
            /*check if current and next node differ*/
            if(compar(list->data, list->next->data)){
                /*add new entry to the list*/
                *head = list;
                head = &((*head)->next);
                /*move to next node*/
                list = list->next;
            } else {
                /*remove the duplicate node*/
                removeNode(list, list->next);
            }
        } else {
            break;
        }
    }
    /*end list by setting the last node to null*/
    (*head)->next = NULL;
    return;
}

int length(struct node_struct *list){
    int counter = 0;
    /*iterate through the list*/
    while(list){
        /*increment counter for each node*/
        list = list->next;
        counter++;
    }
    return counter;
}

void free_list(struct node_struct *list, int free_data){
    struct node_struct *temp;
    while(list){
        /*assign temp to the next node*/
        temp = list->next;
        /*free the data*/
        if(free_data){
            if(list->data){
                free(list->data);
            }
        }
        /*free the node*/
        free(list);
        /*make list point to the next element*/
        list = temp;
    }    
    return;
}