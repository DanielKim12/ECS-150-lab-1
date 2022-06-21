#include <stdio.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

// group members: guk il kim, vivek shome, isaac cho 

int main(int argc, char* argv[]) {
    struct stat buf, buf1;
    int x, y; 
    
    // these works both prints 0 for hardlink 
    x = lstat (argv[1], &buf);
    y = lstat (argv[2], &buf1);

    // Checks # of parameters. This might not be necessary
    if (argc != 3) {
        perror(argv[0]);
        exit(1);
    }
    
    // Checks if file doesn't exist.
    if(x == -1) { 
        perror(argv[1]);
        exit(1);
    } else if (y == -1) {
        perror(argv[2]);
        exit(1);
    }

    if((x && y) == 0) {
        // f1 symlink to f2 
        } if (S_ISLNK(buf.st_mode) && S_ISREG(buf1.st_mode)) { 
            //this will check if f1 is symbolic link to f2 
            printf("These files are linked.\n");
            //printf("%s is a symbolic link to %s\n", argv[1], argv[2]);
        // f2 symlink to f1
        } else if (S_ISLNK(buf1.st_mode) && S_ISREG(buf.st_mode)) {
            printf("%s is a symbolic link to %s\n", argv[2], argv[1]);
        // both files are symlink 
        } else if (S_ISLNK(buf.st_mode) && (S_ISLNK(buf1.st_mode))) {
            printf("These files are linked.\n");
        } else if (S_ISREG(buf.st_mode) || (S_ISREG(buf1.st_mode))) {
            printf("These files are linked.\n");
    // files are not linked to one another
    } else { 
        printf("The files are not linked.\n");
    }  
    return 0;
}
