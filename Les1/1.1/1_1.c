#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t uid = getuid();
    pid_t euid = geteuid();
    pid_t gid = getgid();
    pid_t sid = getsid(pid);
    printf("%d - pid\n%d - ppid\n%d - uid\n%d - euid\n%d - gid\n%d - sid\n", pid, ppid, uid, euid, gid, sid);
    while(1);
    exit(EXIT_SUCCESS);
}