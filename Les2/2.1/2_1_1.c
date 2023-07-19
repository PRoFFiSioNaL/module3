#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    char str[80];
    int fd;
    if ((fd = open("temp.txt", O_RDONLY)) == -1) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    if ((read(fd, str, 80)) == -1) {
        perror("Ошибка чтения файла");
        exit(EXIT_FAILURE);
    }
    close(fd);
    puts(str);
    exit(EXIT_SUCCESS);
}