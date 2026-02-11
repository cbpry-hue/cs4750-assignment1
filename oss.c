/* Cynthia Brown
 * 01/28/2026
 * CS 4760 
 * Project 1: 
 * oss.c - The main process manager for launching user processes
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

// Function to print help message
void print_help() {
    printf("Usage: oss [-h] [-n proc] [-s simul] [-t iter]\n");
    printf("  -h        Display this help message\n");
    printf("  -n proc   Total number of child processes to launch (default: 5)\n");
    printf("  -s simul  Maximum number of simultaneous processes (default: 2)\n");
    printf("  -t iter   Number of iterations for each user process (default: 5)\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int n = 5; // Default number of child processes
    int s = 2; // Default maximum simultaneous processes
    int t = 5; // Default iterations for each user process
    int c = 0; // current number of simultaneous processes
    int total = 0; // total number of processes launched

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-n") == 0) {
            n = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-s") == 0) {
            s = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-t") == 0) {
            t = atoi(argv[++i]);
        } else {
            // if you really screw up the command line arguments, print the help message and exit
            print_help();
            return 1;
        }
    }

    // Launch initial processes based on the specified parameters
    while (c < s && total < n) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char iter_str[20];
            snprintf(iter_str, sizeof(iter_str), "%d", t); // buffer to hold the string representation of t
            execl("./user", "user", iter_str, NULL);
            perror("execl failed");
            return 1;
        } else if (pid < 0) {
            // Parent process
            c++;
            total++;
        } else {
            printf("OSS: Launching child process with PID %d (total: %d)\n", pid, total + 1);
            c++;
            total++;
        }
    }
    
    // Continue launching until all n processes have been spawned
    while (total < n) {
        wait(NULL);  // Wait for a child to finish
        c--;         // Decrement running count
        
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            char iter_str[20];
            snprintf(iter_str, sizeof(iter_str), "%d", t);
            execl("./user", "user", iter_str, NULL);
            perror("execl failed");
            return 1;
        } else {
            // Parent process
            printf("OSS: Launching child process with PID %d (total: %d)\n", pid, total + 1);
            c++;
            total++;
        }
    }
    
    // Wait for all remaining children to finish
    while (c > 0) {
        wait(NULL);
        c--;
    }

    printf("OSS: All %d child processes have finished.\n", total);
    return 0;
}