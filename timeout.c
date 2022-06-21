#include <stdio.h>
#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// group members: guk il kim, vivek shome, isaac cho 

// fixes timeout problem by making sure child process is exited
void signalHandler(int signal) {
    exit(0);
}

// progran that terminates second program after a given period of time 
int main(int argc, char *argv[], char *envp[]) {

    // checks if the time is negative
    if (atoi(argv[1]) < 1) {
        printf("%d is not a positive integer\n", atoi(argv[1]));
        exit(2);
    }
    int time = atoi(argv[1]);
    // no commaxnd
    if (argc < 3) {
        perror("Usage: timeout sec command args\n");
        exit(1);
    }

    char *newargs[argc - 1];

    for (int i = 2; i < argc; i++) {
       newargs[i-2] = malloc(strlen(argv[i]));
       strcpy(newargs[i-2], argv[i]);
    }
    newargs[argc - 2] = NULL;

    // gets pid
    int pid = fork();
    // path name

    if (pid == 0) {
        // child process - do execve
        // int execve(const char *pathname, char *const argv[], char *const envp[]);
        if(execve(argv[2], newargs, envp) == -1) {
            perror("execve");
        }
    // this accoutns for the negative
    } else if (pid < 0) {
        perror("Couldn't create child process (fork)."); 
        exit(-1);
    } else {
        signal(SIGCHLD, signalHandler);
        
        sleep(time);
        
        kill(pid, SIGTERM);   
    }

    return 0;
}