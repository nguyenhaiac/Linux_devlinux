#include "strutils.h"
#include "stdio.h"
#include "ctype.h"

void str_reverse(char *Text){
    int i = 0;
    while(Text[i] != 0){
      i += 1;
    }
    for(int j=0; j<i/2; j++){
        swap_char(Text+j, Text+i-1-j);
    }
}

char* str_trim(char *Text){
    char * start = Text;
    char *end;
    while(isspace((unsigned char)*start)){
        start++;
    }
    if(*start == '\0'){
        return start;
    }
    end = start + str_len(start) - 1;
    while(end > start && isspace((unsigned char)*end)){
        end--;
    }
    *(end + 1) = '\0';
    return start;

}

int str_len(char * Text){
    int i = 0;
    while(Text[i] != 0){
        i+=1;
    }
    return i;
}

void swap_char(char * a, char * b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
