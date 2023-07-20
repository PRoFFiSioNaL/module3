#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    char str[80];
    FILE* fp;
    if ((fp = fopen("temp.txt", "a")) == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    fgets(str, 80, stdin);
    int len = strlen(str);  
    if (fwrite(str, 1, strlen(str), fp) != strlen(str)) {
        perror("Ошибка записи в файл");
        exit(EXIT_FAILURE);
    }
    if (fclose(fp) != 0) {
        perror("Ошибка закрытия файла");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}