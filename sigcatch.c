#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

// group members: guk il kim, vivek shome, isaac cho 

void signalHandler(int signal) {
    time_t currentTime = time(NULL);

    char *timeString = ctime(&currentTime);
    timeString[strlen(timeString)-1] = '\0';

    char temp[10]; 
    for(int i = 0; i < strlen(sys_siglist[signal]); i++)  {
        temp[i] = toupper((sys_siglist[signal])[i]);
    }
    temp[strlen(sys_siglist[signal])] = '\0';

    printf("%s Recieved signal %d (SIG%s)\n", timeString, signal, temp);
}

int main(void) {
    for(int i = 0; i < 32; i++) {
        signal(i, signalHandler);   
    }
    while(1);
    return 0;
}