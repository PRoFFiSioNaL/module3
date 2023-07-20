#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2){
        perror("Ошибка ввода аргументов");
        exit(EXIT_FAILURE);
    }
    DIR* dir;
    FILE* fp;
    if ((dir = opendir(argv[1])) == NULL) {
        perror("Ошибка открытия каталога");
        exit(EXIT_FAILURE);
    }
    struct dirent* curr_dir;
    while ((curr_dir = readdir(dir)) != NULL) {
        if ((strcmp(curr_dir->d_name, ".") == 0) || (strcmp(curr_dir->d_name, "..") == 0)) {
            continue;
        }
        char name[80];
        memset (name, 0, sizeof(name)); 
        strcpy(name, argv[1]);
        name[strlen(name)] = '/';
        name[strlen(name)] = '\0';
        strcat(name, curr_dir->d_name);
        fputs(curr_dir->d_name, stdout);
        struct stat buff;
        if (stat(name, &buff) < 0) {
            perror("Ошибка stat");
            exit(EXIT_FAILURE);
        }
        if (S_ISLNK(buff.st_mode)) fputs(" - cимвольная ссылка\n", stdout);
        else if (S_ISREG(buff.st_mode)) fputs(" - обычный файл\n", stdout);
        else if (S_ISDIR(buff.st_mode)) fputs(" - каталог\n", stdout);
        else if (S_ISCHR(buff.st_mode)) fputs(" - символьное устройство\n", stdout);
        else if (S_ISBLK(buff.st_mode)) fputs(" - блочное устройство\n", stdout);
        else if (S_ISFIFO(buff.st_mode)) fputs(" - канал FIFO\n", stdout);
        else if (S_ISSOCK(buff.st_mode)) fputs(" - сокет\n", stdout);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}