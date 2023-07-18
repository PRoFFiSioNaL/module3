#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int rv;
    pid_t pid;
    switch(pid = fork()){
        case -1:
            perror("Fail fork\n");
            exit(EXIT_FAILURE);
        case 0:
            for (int i = 1; i <= argc / 2; ++i){
                printf("%d ", atoi(argv[i]) * atoi(argv[i]));
            }
            printf("\n");
            exit(rv);
        default:
            for (int i = (int)(argc / 2) + 1; i < argc; ++i){
                printf("%d ", atoi(argv[i]) * atoi(argv[i]));
            }
            printf("\n");
            wait(&rv);
            printf("%d\n", WEXITSTATUS(rv));
    }
    exit(EXIT_SUCCESS);
}