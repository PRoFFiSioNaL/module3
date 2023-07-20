#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Ошибка ввода аргументов");
        exit(EXIT_FAILURE);
    }
    char path[80];
    char name[20];
    int del = 0;
    for (int i = strlen(argv[1]); i > 0; --i) {
        if (*(argv[1] + i) == '/') {
            del = i;
            break;
        }
    }
    if (del != 0) {
        for (int i = 0; i < del; ++i) {
            path[i] = *(argv[1] + i);
        }
        printf("\n");
        for (int i = del + 1, j = 0; i < strlen(argv[1]); ++i, ++j) {   
            name[j] = *(argv[1] + i);
        }
        if (strlen(argv[1]) - del == strlen(name)) { //Проверка на дополнительный лишний символ, я не понимаю откуда он берется но если я записываю файл например temp.txt, то по непонятной причине в строке temp.txt@, причем это только при конкретной длине
            name[strlen(name) - 1] = '\0';
        }
    }
    else {
        for (int i = 0; i < strlen(argv[1]); ++i) {
            name[i] = *(argv[1] + i);
        }
        if (strlen(argv[1]) < strlen(name)) { //Проверка на дополнительный лишний символ, я не понимаю откуда он берется но если я записываю файл например temp.txt, то по непонятной причине в строке temp.txt@, причем это только при конкретной длине
            name[strlen(name) - 1] = '\0';
        }
        *path = '.';
    }
    char str[80];
    DIR* dir;
    FILE* fp;
    if ((dir = opendir(path)) == NULL) {
        puts("Ошибка открытия каталога");
        exit(EXIT_FAILURE);
    }
    struct dirent* curr_dir;
    while ((curr_dir = readdir(dir)) != NULL) {
        if (strcmp((curr_dir->d_name), name) == 0) {
            if ((fp = fopen(name, "a+")) == NULL) {
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
    }
    puts("Такого файла не существует, вы хотите создать файл?(y/n)");
    char agree = fgetc(stdin);
    while (getchar() != '\n');
    if (agree == 'y') {
        if ((fp = fopen(name, "w+")) == NULL) {
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
    }
    exit(EXIT_SUCCESS);
}