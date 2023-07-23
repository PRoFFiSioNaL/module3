#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    printf("Programm without buffer\n");
    pid_t pid = getpid();
    int fd;
    if ((fd = open("temp.txt", O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR)) == -1) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }   
    int counter = 0;
    while(1) {
        write(fd, &counter, 4);
        printf("Cчетчик = %d\n", counter);
        sleep(1);
        counter++;
    }
    close(fd);
    exit(EXIT_SUCCESS);
}