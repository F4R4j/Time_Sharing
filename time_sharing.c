#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_PROCESS 3
#define TIME_QUANTUM 2

pid_t pid[NUM_PROCESS];

void child_process(int id) {
    while (1) {
        printf("Process %d is running...\n", id);
        sleep(1);
    }
}

int main() {
    int i;

    for (i = 0; i < NUM_PROCESS; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            raise(SIGSTOP);
            child_process(i + 1);
            exit(0);
        }
    }

    sleep(1);

    while (1) {
        for (i = 0; i < NUM_PROCESS; i++) {
            printf("\nScheduler: Running process %d\n", i + 1);
            kill(pid[i], SIGCONT);
            sleep(TIME_QUANTUM);
            kill(pid[i], SIGSTOP);
        }
    }

    return 0;
}
