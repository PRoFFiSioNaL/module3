#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char* path = "/usr/bin/";
    char* result = malloc(strlen(path) + strlen(argv[1]) + 1);
    if (result == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcat(result, path);
    strcat(result, argv[1]);
    execv(result, (argv + 1));
    free(result);
    exit(EXIT_SUCCESS);
}