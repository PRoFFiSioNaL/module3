#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2){
        perror("Ошибка ввода аргументов");
        exit(EXIT_FAILURE);
    }
    DIR* dir;
    if ((dir = opendir(argv[1])) == NULL) {
        perror("Ошибка открытия каталога");
        exit(EXIT_FAILURE);
    }
    struct dirent* curr_dir;
    while ((curr_dir = readdir(dir)) != NULL) {
        puts(curr_dir->d_name);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}