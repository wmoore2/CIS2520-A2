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
    int i, outIndex = 0, type = 0;
    char* wordIn = malloc(MAX_LINE_LENGTH * sizeof(char));
    char wordOut[260];
    strcpy("", wordOut);
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
        for(i = 0; i < strlen(wordIn); i++){
            if(isalnum(wordIn[i]) || (wordIn[i] == '\'' && (i && isalnum(wordIn[i - 1]))) || (wordIn[i] == '-' && (i && isalnum(wordIn[i - 1])))){
                /*alpha or number*/
                if((wordIn[i] == '\'' || wordIn[i] == '-') && wordIn[i] == wordIn[i + 1]){
                    /*double hyphen or comma*/
                    /*add the new word to the list*/
                    (*runningStruct)->next = addNode(wordOut);
                    /*reset the string used for building*/
                    strcpy("", wordOut);
                    outIndex = 0;
                } else if((wordIn[i] == '\'' || wordIn[i] == '-') && isspace(wordIn[i + 1])){

                } else {
                    type = 1;
                    wordOut[outIndex] = wordIn[i];
                    outIndex++;
                }
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
            if(*mainString[i] == '\'' || *mainString[i] == '-'){
                if(*mainString[i + 1] == *mainString[i] || isspace(*mainString[i + 1])){
                    if(isspace(*mainString[i + 1])){
                        lastIsSpace = 1;
                    }
                    break;
                }
            } else if(isspace(*mainString[i])){
                break;
            }
        } else if(type == two){
            if(*mainString[i] != *mainString[i + 1]){
                if(isspace(*mainString[i + 1])){
                    lastIsSpace = 1;
                }
                break;
            }
        } else if(type == three){
            toReturn = malloc(2);
            strcpy(toReturn, "\n");
            return toReturn;
        }
    }
    toReturn = malloc(i);
    strncpy(toReturn, *mainString, i - 1);
    mainString += (i + lastIsSpace);
    return toReturn;
}

char** splitString(char* toSplit, int* wordCounter){
    char** toReturn = malloc(0);
    int i, start = 0, end = 0, type = 0;
    (*wordCounter) = 0;
    /*Iterate through string*/
    type = classifyCharacter(toSplit[0]);
    for(i = 0; i < strlen(toSplit); i++){
        /*Splitting strings*/
        if(isalnum(toSplit[i]) || toSplit[i] == '\'' || toSplit[i] == '-'){
            /*is a type 1 character*/
            if(i && (toSplit[i - 1] == '\'' || toSplit[i - 1] == '-') && (toSplit[i] == toSplit[i - 1])){
                /*we no longer have a type1 word. still need to end off the old word and then start new one*/

            }
        }
    }

    return toReturn;
}

char** addWord(char** toReturn, int* wordCounter, char* theString, int start, int end){
    /*allocate memory for new word and create a substring*/
    toReturn = realloc(toReturn, (++(*wordCounter)) * sizeof(char*));
    toReturn[(*wordCounter) - 1] = subString(theString, start, end);
    return toReturn;
}

char* subString(char* toSearch, int start, int end){
    int length = end - start + 1;
    char* toReturn = malloc(length + 1);
    int i;

    /*Iterates through string and build new one*/
    for(i = 0; i < length; i++){
        toReturn[i] = toSearch[start + i];
    }

    toReturn[length] = '\0';

    return toReturn;
}

enum type classifyCharacter(char theChar){
    if(isalpha((theChar) || isdigit(theChar) || theChar == '-' || theChar == '\'')){
        return one;
    }

    if(ispunct(theChar)){
        return two;
    }
    if(theChar == '\n'){
        return three;
    } else {
        return one;
    }
}

struct node_struct* addNode(char* stringData){
    /*Allocate new structure*/
    struct node_struct* toReturn = malloc(sizeof(struct node_struct));
    char* newData = malloc(strlen(stringData));
    /*copy data to new location and free given data for use in other functions once again*/
    strcpy(stringData, newData);
    /*Assign proper values*/
    toReturn->data = newData;
    toReturn->next = NULL;
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