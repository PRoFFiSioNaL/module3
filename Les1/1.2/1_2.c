#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void SUCCESS(){
    printf("Good\n");
}

int main(int argc, char *argv[]){
    pid_t pid;
    int rv;
    switch(pid = fork()){
        case -1:
            perror("Fail fork\n");
            exit(EXIT_FAILURE);
        case 0:
            for (int i = 1; i < argc; ++i){
                printf("%s ", argv[i]);
            }
            printf("\n");
            exit(rv);
        default:
            for (int i = 1; i < argc; ++i){
                printf("%s ", argv[i]);
            }
            printf("\n");
            wait(&rv);
            printf("%d\n", WEXITSTATUS(rv));
    }
    atexit(SUCCESS);
    exit(EXIT_SUCCESS);
}