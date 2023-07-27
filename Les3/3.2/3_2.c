#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    printf("Programm with buffer\n");
    pid_t pid = getpid();
    FILE* fp;
    if ((fp = fopen("temp_buffer.txt", "w+")) == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    signal(SIGINT, SIG_IGN);
    int counter = 0;
    while(1) {
        fprintf(fp, "%d ", counter);
        printf("Cчетчик = %d\n", counter);
        sleep(1);
        counter++;
    }
    fclose(fp);
    exit(EXIT_SUCCESS);
}