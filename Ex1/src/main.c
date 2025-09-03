#include "strutils.h"
#include <stdio.h>

int main(){
    char text[] = "12345678\n";
    str_reverse(text);
    printf("%s\n", text);
    char text2[] = "   12433242   ";
    char* trimmed = str_trim(text2);
    printf("%s\n", trimmed);
    printf("%i\n", str_len(text2));
    printf("%i\n", str_len(trimmed));
}
