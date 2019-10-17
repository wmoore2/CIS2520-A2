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
    struct node_struct *head, **runningStruct;
    char* wordIn = malloc(MAX_LINE_LENGTH * sizeof(char) + 1);
    char* temp;
    /*point the struct building to head*/
    runningStruct = &head;
    /*Iterate through file*/
    while(1){
        wordIn = fgets(wordIn, MAX_LINE_LENGTH, fp);
        /*Break at end of file*/
        if(wordIn == NULL){
            free(wordIn);
            break;
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
                if((*mainString)[i + 1] == ' '){
                    lastIsSpace = 1;
                }
                i++;
                break;
            }
        } else if(type == three){
            toReturn = malloc(2);
            strcpy(toReturn, "\n");
            *mainString += 2;
            return toReturn;
        }
    }
    toReturn = malloc(i + 1);
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

struct node_struct* addNode(char* stringData){
    /*Allocate new structure*/
    struct node_struct* toReturn = malloc(sizeof(struct node_struct));
    /*Assign proper values*/
    toReturn->data = stringData;
    toReturn->next = NULL;
    printf("%s", stringData);
    return toReturn;
}

struct node_struct* search(struct node_struct *list, char *target, int (*compar)(const void*, const void*)){
    return NULL;
}

struct node_struct* copy(struct node_struct *start, struct node_struct *end){
    return NULL;
}

void ftext(FILE *fp, struct node_struct *list){
    return;
}

struct node_struct* sort(struct node_struct *list, int (*compar)(const void*, const void*)){
    return NULL;
}

void remove_repeats(struct node_struct *list, int (*compar)(const void*, const void*)){
    return;
}

int length(struct node_struct *list){
    return 0;
}

void free_list(struct node_struct *list, int free_data){
    return;
}