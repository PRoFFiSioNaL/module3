#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main() {
    srand(time(NULL));
    char numberstr[5];
    int fd;
    unlink("/tmp/fifo0001.1");
    if ((mkfifo("/tmp/fifo0001.1", O_RDWR)) == -1) {
        perror("Ошибка создания канала");
        exit(EXIT_FAILURE);
    }
    if ((fd = open("/tmp/fifo0001.1", O_WRONLY)) == -1) {
        perror("Ошибка открытия канала");
        exit(EXIT_FAILURE);
    }
    while (1) {
        int number = rand() % 100;
        memset(numberstr, 0, 5);
        sprintf(numberstr, "%d ", number);
        if (write(fd, numberstr, strlen(numberstr)) == -1) {
            perror("Ошибка записи");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}