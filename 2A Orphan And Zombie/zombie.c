       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

       int main(int argc, char *argv[])
       {
         //  int pipefd[2];
           pid_t cpid;
       

           cpid = fork();
           /*both if and else will execute as fork returns 2 values*/
           /*One value in if and other in else*/
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
           sleep(1);
           printf("\n Child Process . . . . .");
           printf("\n Child Process ID : %d",getpid());
           printf("\n Parent Process ID : %d",getppid());
           /*sleep(4);    
           printf("\n Child Process ID : %d",getpid());   
           printf("\n New Parent Process ID : %d",getppid());*/
           } 
           else {            /* Parent writes argv[1] to pipe */
		        sleep(10);                /* parent will be suspended , so child is zombie for 10 sec*/
            printf("\n Parent Process . . . . . .I m Exiting\n");
            
           }
       }
