#include <stdio.h>
int main(int argc, char *argv[]){
    int i = 1;
    while(argv[++i] != NULL){
        printf("%s ",argv[i]);
    }
    printf("\n");
    return 0;
}