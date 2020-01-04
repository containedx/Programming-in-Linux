#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static void writing();
int N=5;
int fd;
int offset; 
char* komunikat; 

int main(int argc, char* argv[])
{
    printf("MOJ PID: %d\n", getpid()); 
    int opt;
    fd = strtol(argv[1], 0, 10);
    offset = strtol(argv[2], 0, 10);
    komunikat = (char*)malloc(strlen(argv[3]) * sizeof(char)); 
    strcpy(komunikat, argv[3]); 

    //printf("nr deskryptora: %d\n", fd);
    //printf("przesuniecie: %d\n", offset); 
    //printf("komunikat: %s\n", komunikat); 
    

    while( (opt = getopt( argc, argv, "N:" )) != -1)
    {
        if(opt == 'N')
        {
            N = strtol(optarg, 0, 10);
            printf("krotnosc: %d\n", N); 
        }
        if(N<0)
        {
            perror("krotnosc nie moze byc ujemna !!!!");
            return 1; 
        }
    }

    struct sigaction action;
    memset(&action, '\0', sizeof(action));
    action.sa_handler = &writing;
  
    if(sigaction(SIGUSR1, &action, NULL) < 0)
    {
        perror("The night is dark and full of sigactions with errors\n"); 
        return 1;
    }

    while(1);

    return 0; 
}

static void writing()
{
        
    for(int i=0; i<N; i++)
    {
        lseek(fd, offset, 0);
        if( (write(fd, komunikat, strlen(komunikat))) == -1 )
        {
            perror("******error write na tablice ogloszen!*******");
            return; 
        }
    }
       

}