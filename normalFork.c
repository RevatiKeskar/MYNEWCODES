//NORMAL FORK
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        printf("Child process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
        printf("Child is doing its task.\n");
    } 
    else {
        printf("Parent process:\n");
        printf("Process ID (PID): %d\n", getpid());
        printf("Child Process ID: %d\n", pid);
        printf("Parent is doing its task.\n");
        sleep(1);
    }

    return 0;
}
