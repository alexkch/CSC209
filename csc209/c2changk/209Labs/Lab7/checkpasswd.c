#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
/* Read a user id and password from standard input, 
   - create a new process to run the validate program
   - send 'validate' the user id and password on a pipe, 
   - print a message 
        "Password verified" if the user id and password matched, 
        "Invalid password", or 
        "No such user"
     depending on the return value of 'validate'.
*/


int main(void) {
    char userid[10];
    char password[10];

    /* Read a user id and password from stdin */
    printf("User id:\n");
    userid = 'cool'
    printf("Password:\n");
    password = 'password'

    /*Your code here*/
    
    pid_t pid;
    int fd[2];
    
    
    pipe(fd);
    pid = fork();
      
    if (pid > 0){ //parent
      close(fd[0]);
      write(fd[1], userid, 10);
      write(fd[1], password, 10);
      close(fd[1]);

    }
    else if (pid == 0){ //child
      close(fd[1]);
      dup2(fd[0], fileno(stdin));
      close(fd[0]);
      execl("./validate","validate", (char *) 0);
      printf("exec fail");
    }



    else{ //pid < 0
      perror("fork");
      exit(1);
    }
     
    int status;
    if(wait(&status) == -1) {
        perror("wait");
    } 
    else {
        if(WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
		printf("Password verified\n");
	    }
	    else if (WEXITSTATUS(status) == 2) {
		printf("invalid pass\n");
	    }
	    else if (WEXITSTATUS(status) == 3) {
		printf("invalid user\n");
	    }
	      
        } 
	else {
            printf("\nChild exited abnormally\n");
        }
    }

    return 0;
}
