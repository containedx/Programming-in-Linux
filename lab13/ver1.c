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
    pipe(pfd);

    struct timespec ts = {0, 29411760};  
    struct timespec tsx = {0, 5411764};

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
                char byte; 
                read(pfd[0], &byte, 1); 
                time_t currenttime = time(NULL); 
                char* timestamp = ctime(&currenttime); 
                //report
                printf("1 byte read ( %s ) \t%s", &byte, timestamp);
                //counting....
                nanosleep(&ts, NULL); 
                //wait for parent
                waitpid(parentpid, &status, WNOHANG); 
                if (WIFEXITED(status)) {
                    printf("parent exited, status=%d\n", WEXITSTATUS(status));
                    exit(0); 
                }
            }            
        }
    }

    //parent - writing end
    close(pfd[0]); //close reading end

    while(1)
    {
        //reading random length of random bytes
        int randomData = open("/dev/urandom", O_RDONLY);
        int size = rand()% N + 1; 
        char buffer[size]; 
        read(randomData, buffer, sizeof( buffer )); 
        //read time
        time_t currenttime = time(NULL); 
        char* timestamp = ctime(&currenttime); 
        write(pfd[1], buffer, sizeof(buffer)); 
        //report
        printf("%d bytes wroted ( %s ) \t%s", size, buffer, timestamp);
        //waiting....
        nanosleep(&tsx, NULL);
    }

}