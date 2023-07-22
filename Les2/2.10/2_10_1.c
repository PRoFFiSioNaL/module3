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
    char numberstr[100];
    int fd;
    if ((fd = open("/tmp/fifo0001.1", O_RDONLY)) == -1) {
        perror("Ошибка открытия канала");
        exit(EXIT_FAILURE);
    }
    while (1) {
        sleep(1);
        memset(numberstr, 0, 100);
        if (read(fd, numberstr, 100) == -1) {
            perror("Ошибка чтения");
            exit(EXIT_FAILURE);
        }
        printf("%s", numberstr);
    }
    exit(EXIT_SUCCESS);
}