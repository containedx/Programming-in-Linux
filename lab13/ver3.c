#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 10

int main(int argc, char* argv[])
{
    int pfd[2]; 
    int pfd2[2];
    pipe2(pfd, O_NONBLOCK);
    pipe2(pfd2, O_NONBLOCK); 

//write random data to pipe
    int randomData = open("/dev/urandom", O_RDONLY);
    char buffer[50]; 
    read(randomData, buffer, sizeof( buffer ));    
    write(pfd[1], buffer, sizeof(buffer)); 

    struct timespec ts = {0, 29411760};  

    int parentpid = getpid(); 
    int status; 
    
    for(int i=0; i<N; i++)
    {
        if (fork()==0)
        {
            //child - reading end 
            close(pfd[1]); //close writing end 
            while(1)
            {
                //read pfd
                char byte; 
                read(pfd[0], &byte, 1); 
                time_t currenttime = time(NULL); 
                char* timestamp = ctime(&currenttime); 
                //write 
                write(pfd2[1], &byte, sizeof(byte)); 
                //read pfd2
                char byte2; 
                read(pfd2[0], &byte2, 1); 
                time_t currenttime2 = time(NULL); 
                char* timestamp2 = ctime(&currenttime2); 
                //report
                printf("%s: (%s) \t %s: (%s)\n",timestamp,  &byte, timestamp2, &byte2);
                //counting....
                nanosleep(&ts, NULL); 
                //wait for parent
                waitpid(parentpid, &status, WNOHANG); 
                if (WIFEXITED(status)) 
                {
                    printf("parent exited, status=%d\n", WEXITSTATUS(status));
                    exit(0); 
                }
            }            
        }
    }

    //parent - writing end
    close(pfd[0]); //close reading end
    close(pfd[0]); //close children's
    close(pfd[1]);

    while(1)
    {
        int cstatus; 
        int wpid; 
        while((wpid = waitpid(-1, &cstatus, WNOHANG)))
        {
            if(wpid==-1)
            {
                perror("waitpid"); exit(EXIT_FAILURE); 
                return 1;  
            }
            else if (WIFEXITED(cstatus)) 
            {
                printf("child %d exited, status=%d\n", wpid, WEXITSTATUS(cstatus));
            }
        }
    }

}