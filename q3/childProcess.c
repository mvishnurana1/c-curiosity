#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){

/**
 * the program needs at least one argument to execute
 */
    if(argc > 1){

        pid_t pid[argc]; // a collection of number of arguments passsed to make the child concurrent
        char *commandName; // stores the command name
        int status;        // gives the status 

        for(int i = 1 ; i < argc; i++){
            pid[i-1] = fork(); 

            if(pid[i-1] < 0){
                perror("fork unsuccessful ");
                exit(1);  
            } else {
                if(pid[i-1] == 0){
                    commandName = strchr(argv[i], '/'); // find the occurrence of '/'
                    // execl (path, commandName, NULL)
                    execl(argv[i], commandName, (char*)0);

                    perror("execl failed...\n");
                    exit(1);    
                }
            }
            printf("%s \n", argv[i]); 
        }

        // for loop for controlling the parent process for concurrency 
        for(int i=1; i<argc; i++){
            wait((int*)0);
            // testing  
            printf("Command %s has finished executing \n", argv[i]);
            sleep(2); 

            if(WIFEXITED(status)){
                const int EXIT_STATUS = WEXITSTATUS(status);
                // testing 
                printf("exit status for the child was %d \n", EXIT_STATUS); 
            }
        }
    }
    else {
       printf("No path entered"); 
    }

    printf("All done bye-bye \n"); 

    return 0;  
}