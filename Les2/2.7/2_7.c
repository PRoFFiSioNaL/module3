#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        puts("Ошибка аргументов");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int rv;
    pid_t pid;
    int pipefd[2];
    if (pipe(pipefd) != 0) {
        perror("Ошибка каналов");
        exit(EXIT_FAILURE);
    }
    switch (pid = fork()) {
    case -1:
        perror("Ошибка fork");
        close(pipefd[0]);
        close(pipefd[1]);
        exit(EXIT_FAILURE);
    case 0:
        close(pipefd[0]);
        int arg = atoi(argv[1]);
        for (int i = 0; i < arg; ++i) {
            int number = rand() % 100;
            char numberstr[4];
            memset(numberstr, 0, 4);
            sprintf(numberstr, "%d ", number);
            if (numberstr[2] == 0) write(pipefd[1], numberstr, 2);
            else write(pipefd[1], numberstr, 3);
        }

        close(pipefd[1]);
        exit(rv);
    default:
        close(pipefd[1]);
        char str[256];
        wait(&rv);
        read(pipefd[0], str, 255);
        close(pipefd[0]);
        FILE* fp;
        if ((fp = fopen("temp.txt", "w+")) == NULL) {
            perror("Ошибка открытия файла");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "%s", str);
        fclose(fp);
        puts(str);
        printf("%d\n", WEXITSTATUS(rv));
    }
    exit(EXIT_SUCCESS);
}
