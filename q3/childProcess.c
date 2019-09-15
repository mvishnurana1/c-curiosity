#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc > 1){

        pid_t pid[argc]; 
        char *commandName; 
        int status;     

        for(int i = 1 ; i < argc; i++){
            
            pid[i-1] = fork(); 

            if(pid[i-1] < 0){
                perror("fork unsuccessful ");
                exit(1);  
            } else {
                if(pid[i-1] == 0){
                    commandName = strchr(argv[i], '/');
                    execl(argv[i], commandName, (char*)0);

                    perror("execl failed...");
                    exit(1);    
                }
            }

            printf("%s \n", argv[i]); 
        }

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