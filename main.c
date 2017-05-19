#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <time.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "timer.h"
#include "locked.h"
#include "find_updated.h"

#define LEN 150

int main(){

        // Create a child process      
        int pid = fork();
        int pid2 = fork();
        int ppid;
        int ppid2;
        
        
        FILE *pFile;
        char buffer[256];
        ppid = getpid();
        ppid2 = getpid();

        if (pid > 0) {
            printf("Starting Process\nCreating Parent and child");
            // if PID > 0 :: this is the parent
            // this process performs printf and finishes
            sleep(5);  // uncomment to wait 10 seconds before process ends
            exit(EXIT_SUCCESS);
        } else if (pid == 0) {
            // Step 1: Create the orphan process
            printf("Child process is now a orphan process\n");

            // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
            // This command runs the process in a new session
            if (setsid() < 0) { exit(EXIT_FAILURE); }

            // We could fork here again , just to guarantee that the process is not a session leader
            int pid = fork();
            if (pid > 0) {
                exit(EXIT_SUCCESS);
            } else {
                printf("Daemon process created and running\n");
                // Step 3: call umask() to set the file mode creation mask to 0
                // This will allow the daemon to read and write files 
                // with the permissions/access required 
                umask(0);

                // Step 4: Change the current working dir to root.
                // This will eliminate any issues of running on a mounted drive, 
                // that potentially could be removed etc..
                if (chdir("/") < 0 ) { exit(EXIT_FAILURE); }

                // Step 5: Close all open file descriptors
                /* Close all open file descriptors */
                int x;
                for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
                {
                    close (x);
                } 

                while(1) {  
                    int value = getTime();
                }
            }
        }

        if (pid > 0) {
            sleep(2);
            exit(EXIT_SUCCESS);
        } else if (pid == 0) {
            /*
            This function creates a file with all the files updated in the last 24 hours
            by piping outputs of execlp()s, however when introduced to the whole program it fails to work.
            */
            find_updated();
        }
    return 0;
}