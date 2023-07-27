#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void listener(int sig) {
    switch (sig)
    {
    case 2:
        printf("Вы вызывали функцию SIGINT\n");
        break;
    case 3:
        printf("Вы вызывали функцию SIGQUIT\n");
        break;
    default:
        break;
    }
}

int main() {
    printf("Programm with buffer\n");
    pid_t pid = getpid();
    FILE* fp;
    if ((fp = fopen("temp_buffer.txt", "w+")) == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, listener);
    signal(SIGQUIT, listener);
    int counter = 0;
    while (1) {
        fprintf(fp, "%d ", counter);
        printf("Cчетчик = %d\n", counter);
        sleep(1);
        counter++;
    }
    
    fclose(fp);
    exit(EXIT_SUCCESS);
}