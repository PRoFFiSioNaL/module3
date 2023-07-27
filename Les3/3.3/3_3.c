#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

static int count = 0;

void listener(int sig) {
    count++;
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
    int counter = 0;
    do {
        fprintf(fp, "%d ", counter);
        printf("Cчетчик = %d\n", counter);
        sleep(1);
        counter++;
    } while (count < 3);
    
    fclose(fp);
    exit(EXIT_SUCCESS);
}