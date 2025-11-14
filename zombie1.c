#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {

        printf("Child process (PID: %d) exiting now...\n", getpid());
        _exit(0);
    } else {

        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent sleeping 40 seconds... child becomes zombie.\n");
        sleep(40);
        printf("Parent woke up. Exiting now.\n");
    }

    return 0;
}

