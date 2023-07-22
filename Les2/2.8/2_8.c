#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int rv, number;
    char numberstr[4];
    char str[10];
    pid_t pid;
    FILE* fp;
    int child_to_parrent[2];
    int parrent_to_child[2];
    if (pipe(child_to_parrent) != 0) {
        perror("Ошибка каналов");
        exit(EXIT_FAILURE);
    }
    if (pipe(parrent_to_child) != 0) {
        perror("Ошибка каналов");
        exit(EXIT_FAILURE);
    }
    switch (pid = fork()) {
    case -1:
        perror("Ошибка fork");
        close(child_to_parrent[0]);
        close(child_to_parrent[1]);
        close(parrent_to_child[0]);
        close(parrent_to_child[1]);
        exit(EXIT_FAILURE);
    case 0: //дочерний процесс
        close(child_to_parrent[0]); 
        close(parrent_to_child[1]);
        number = rand() % 100;  
        memset(numberstr, 0, 4);
        sprintf(numberstr, "%d", number);
        if (numberstr[1] == 0) write(child_to_parrent[1], numberstr, 1);
        else write(child_to_parrent[1], numberstr, 2);
        close(child_to_parrent[1]);
        sleep(1);
        memset(str, 0, 10);
        read(parrent_to_child[0], str, 10);
        close(parrent_to_child[0]);
        if ((fp = fopen("temp.txt", "a+")) == NULL) {
            perror("Ошибка открытия файла");
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "Число после умножения (дочерний процесс) - %s\n", str);
        fclose(fp);
        printf("Число после умножения (дочерний процесс) - %s\n", str);
        exit(rv);
    default: //родительский процесс
        close(child_to_parrent[1]);
        close(parrent_to_child[0]);
        sleep(1);
        memset(str, 0, 10);
        read(child_to_parrent[0], str, 10);
        close(child_to_parrent[0]);
        number = atoi(str);
        if ((fp = fopen("temp.txt", "w+")) == NULL) {
            perror("Ошибка открытия файла");
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "Число до умножения (родительский процесс) - %d\n", number);
        fclose(fp);
        printf("Число до умножения (родительский процесс) - %d\n", number);
        number *= 2;
        memset(numberstr, 0, 4);
        sprintf(numberstr, "%d", number);
        if (numberstr[1] == 0) write(parrent_to_child[1], numberstr, 1);
        else if (numberstr[2] == 0) write(parrent_to_child[1], numberstr, 2);
        else write(parrent_to_child[1], numberstr, 3);
        close(parrent_to_child[1]);
        sleep(2);
    }
    exit(EXIT_SUCCESS);
}