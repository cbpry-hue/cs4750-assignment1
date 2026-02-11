/* Cynthia Brown
 * 01/28/2026
 * CS 4760 
 * Project 1
 * user.c - The user process that simulates work by sleeping for a specified number of iterations
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int nums = atoi(argv[1]); // number of iterations to sleep, passed as a command-line argument
    pid_t user_pid = getpid(); // get the process ID of the user process
    pid_t parent_pid = getppid(); // get the parent process ID (the oss process)

    for(int i = 0; i < nums; i++) {
        pid_t user_pid = getpid();
        pid_t parent_pid = getppid();

        printf("USER PID:%d PPID: %d Iteration:%d before sleeping\n", user_pid, parent_pid, i+1);
        sleep(1);
        printf("USER PID:%d PPID: %d Iteration:%d after sleeping\n", user_pid, parent_pid, i+1);
    }
}