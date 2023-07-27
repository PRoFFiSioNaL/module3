#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    char* path = "/usr/bin/";
    //-----------------------------Отделение команды-------------------------------------------------
    char arg[60] = {0};
    char args[3][20] = {0};
    char param[3][3] = {0};
    fgets(arg, 60, stdin);
    int i = 0, j = 0, k = 0;
    while ((*(arg + i) != '\n') && (*(arg + i) != '\0')) {
        if (arg[i + 1] == '|') {
            i += 3;
            ++j;
            k = 0;
        }
        if (arg[i + 1] == '-') {
            sprintf(param[j], "-%c", arg[i + 2]);
            i += 2;
        }
        if (!(arg[i] >= 48 && arg[i] < 58)) {
            args[j][k] = arg[i];
            k++;
        }
        i++;
        
    }
    char* result = malloc(strlen(path) + strlen(args[0]) + 1);
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcat(result, path);
    strcat(result, args[0]);
    //-----------------------------------------------------------------------------------------------
    int rv1, rv2, rv3;
    pid_t pid_first;
    int first_to_second[2];
    if (pipe(first_to_second) != 0) {
        perror("Ошибка каналов");
        exit(EXIT_FAILURE);
    }
    switch (pid_first = fork()) {
    case -1:
        perror("Ошибка fork");
        close(first_to_second[0]);
        close(first_to_second[1]);
        exit(EXIT_FAILURE);
    case 0: //Первый дочерний процесс (ls)
        close(first_to_second[0]);
        if (j != 0) dup2(first_to_second[1], 1); //Заменяю 1(stdout) на поток вывода
        if (strcmp(param[0], "") != 0)  execl(result, args[0], param[0], NULL);
        else execl(result, args[0], NULL);
        close(first_to_second[1]);
        free(result);
        exit(rv1);
    default: //Родительский процесс 
        close(first_to_second[1]);
        wait(&rv1);
        //-----------------------------Отделение команды-------------------------------------------------
        char* result = malloc(strlen(path) + strlen(args[1]) + 1);
        if (result == NULL){
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcat(result, path);
        strcat(result, args[1]);
        //-----------------------------------------------------------------------------------------------
        if (j != 0) {
            pid_t pid_second;
            int second_to_third[2];
            if (pipe(second_to_third) != 0) {
                perror("Ошибка каналов");
                exit(EXIT_FAILURE);
            }
            switch (pid_second = fork()) {
            case -1:
                perror("Ошибка fork");
                close(first_to_second[0]);
                close(second_to_third[0]);
                close(first_to_second[1]);
                close(second_to_third[1]);
                exit(EXIT_FAILURE);
            case 0: //Второй дочерний процесс(head)
                close(second_to_third[0]);
                dup2(first_to_second[0], 0);
                if (j != 1) dup2(second_to_third[1], 1);
                if (strcmp(param[1], "") != 0)  execl(result, args[1], param[1], NULL);
                else execl(result, args[1], NULL);
                close(first_to_second[0]);
                close(second_to_third[1]);
                free(result);
                exit(rv2);
            default:
                close(first_to_second[0]);
                close(second_to_third[1]);
                wait(&rv2);
                //-----------------------------Отделение команды-------------------------------------------------
                char* result = malloc(strlen(path) + strlen(args[2]) + 1);
                if (result == NULL){
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                strcat(result, path);
                strcat(result, args[2]);
                //-----------------------------------------------------------------------------------------------
                if (j != 1) {
                    switch (pid_second = fork()) {
                    case -1:
                        perror("Ошибка fork");
                        close(first_to_second[0]);
                        close(second_to_third[0]);
                        close(first_to_second[1]);
                        close(second_to_third[1]);
                        exit(EXIT_FAILURE);
                    case 0: //Третий дочерний процесс(tail)
                        dup2(second_to_third[0], 0);
                        if (strcmp(param[2], "") != 0) execl(result, args[2], param[2], NULL);
                        else execl(result, args[2], NULL);
                        close(second_to_third[1]);
                        free(result);
                        exit(rv3);
                    default:
                        close(second_to_third[1]);
                        wait(&rv3);
                    }
                }
            }
        }
    }
    exit(EXIT_SUCCESS);
}