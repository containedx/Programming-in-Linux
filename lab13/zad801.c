#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1
int N; 
int pipefd[2];

void handler(int sig)
{
    //obsluga alarmu
    char c; 
    c = rand() % N+1; 
    write(pipefd[1], &c, SIZE);
}

void handler2(int sig)
{
    //obsluga SIGCHILD
    printf("\ndostalem sygnal SIGCHLD\n"); 
    int status; 
    int pid; 
    while(( pid = waitpid(-1, &status, WNOHANG)))
    {
        printf("\t%d: %d\n\n",pid, status); 
    }
 

}

int main( int argc, char *argv[])
{
    if(argc<2)
    {
        perror("Podaj liczbe dzieci!!");
        return 1; 
    }
    
    N = strtol( argv[1], 0, 10); 

    if(pipe(pipefd) < 0)
    {
        perror("error pipe"); 
        return 1; 
    }

    struct timespec ts = {0, 500000000 };

    timer_t timerid; 
    struct itimerspec val;
    val.it_value.tv_sec = 0;
    val.it_value.tv_nsec = 50000;
    val.it_interval.tv_sec = 0;
    val.it_interval.tv_nsec = 50000;
    timer_create( CLOCK_REALTIME, 0, &timerid); 
    timer_settime(timerid, 0, &val, NULL); 

    signal(SIGALRM, handler); 
    signal(SIGCHLD, handler2); 

    for(int i=0; i<N; i++)
    {
        int pid = fork(); 
        if(pid == 0)
        {
            while(1)
            {
                int nbytes; 
                char buf; 
                nbytes = read(pipefd[0], &buf, SIZE);
                time_t currenttime = time(NULL); 
                char* timestamp = ctime(&currenttime); 
                printf("dziecko nr %d: odczytalem %s --time: %s", i+1, &buf, timestamp); 
                nanosleep(&ts, NULL);
                if( buf != 0)
                {
                    buf -= 1;  
                    write( pipefd[1], &buf, nbytes-1); 
                    time_t currenttime2 = time(NULL); 
                    char* timestamp2 = ctime(&currenttime2);
                    printf("  wpisalem %s --time %s", &buf, timestamp2 ); 
                }
                printf("\n\n");                  
            }
            exit(0);
        }
        else 
        {
            close(pipefd[0]); 
            
        }
    }
    

}