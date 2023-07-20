#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if (argc != 2) {
        puts("Ошибка ввода аргументов");
        exit(EXIT_FAILURE);
    }
    char str[80];
    int fd;
    if ((fd = open(argv[1], O_WRONLY|O_CREAT)) == -1) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    gets(str);
    int len = strlen(str);
    str[len] = '\n';
    str[len + 1] = '\0';
    if(lseek(fd, 0, 2) == -1) {
        perror("Ошибка lseek");
        exit(EXIT_FAILURE);
    }
        
    if ((write(fd, str, strlen(str))) != strlen(str)) {
        perror("Ошибка записи в файл");
        exit(EXIT_FAILURE);
    }
    close(fd);
    exit(EXIT_SUCCESS);
}