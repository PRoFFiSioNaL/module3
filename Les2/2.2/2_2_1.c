#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if (argc != 2) {
        puts("Ошибка ввода аргументов");
        exit(EXIT_FAILURE);
    }
    char str[80];
    FILE* fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    if (fread(str, 1, 80, fp) != 80) {
        if(!feof(fp)) {
            perror("Ошибка чтения файла");
            exit(EXIT_FAILURE);
        }
    }
    if (fclose(fp) != 0) {
        perror("Ошибка закрытия файла");
        exit(EXIT_FAILURE);
    }
    puts(str);
    exit(EXIT_SUCCESS);
}