#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <string.h>

int dane;
int tablica; 
int archiwum;

char tabfile[20]; 

int ilepisarzy = 0;
int* pidy; 

int t=0;
int cykl=0;  

struct itimerspec val;
struct timespec ts = { 0, 225000000}; 

void handler(); 
void goodbye(); 

int main(int argc, char* argv[])
{
    int opt; 
    int N=5; 

    while( (opt = getopt( argc, argv, "d:b:l:N:" )) != -1)
    {
        switch(opt)
        {
            case 'd':
            printf("plik z danymi: %s\n", optarg);
            if( ! ( dane = open(optarg, O_RDONLY)))
            {
                printf("*** error open dane ***"); 
            }; 
            break;

            case 'b': 
            printf("tablica ogloszeniowa: %s\n", optarg);
            strcpy(tabfile, optarg);  
            if( ! ( tablica = open(optarg, O_RDWR | O_CREAT, S_IRWXU ) ))
            {
                printf("*** error open tablica ***"); 
            }; 
            break;

            case 'l':
            printf("archiwum X : %s\n", optarg);
            if(!(archiwum = open(optarg, O_WRONLY | O_CREAT, S_IRWXU ) ))
            {
                printf("*** error open archiwum ***"); 
            }; 
            break;

            case 'N':
            N = strtol( optarg, 0, 10);
            printf("opcjonalny parametr: %d\n", N);
        }
    }
    

    char c;
    int k=0;  
    int count=0;
    


    while( read(dane, &c, 1 ))
    {
        if(c=='\n' || c=='\0')
        {
            ilepisarzy++;
        }
    }

    lseek(dane, (off_t)0, 0); 
    pidy = (int*)malloc(ilepisarzy * sizeof(int)); 
    
        while( read(dane, &c, 1 ))
        {            
            if( c=='\n') //=> nowa linia => nowy potomek
            {
                 
                char* buf;
                buf = (char*)malloc((count+1) * sizeof(char)); 
                lseek(dane, t-count, 0);  
                read(dane, buf, count+1);
                //printf("%s", buf); 
                count = 0;
                t++;

                //char *args[] = {"./pisarz",  };

                if( fork() == 0 )
                {
                    pidy[k] = getpid(); 
                    //printf("\t hej, tu potomek nr %d, a moj pid to %d, a moj komunikat to %s\n", ilepisarzy, getpid(), buf);
                    char fd[3], offset[3], Np[10];
                    sprintf(fd, "%d", tablica); 
                    sprintf(offset, "%d", t);
                    sprintf(Np, "-N %d", N); 
                    execlp("./pisarz", "./pisarz", fd, offset, buf, Np, NULL);
                    k++; 
                }
            } 
            else 
            {
                count++;
                t++;
            }         
        }     


        timer_t timerid; 
        
        memset(&val, 0, sizeof(struct itimerspec)); 
            val.it_value.tv_sec = 0; 
            val.it_value.tv_nsec = 450000000;
            val.it_interval.tv_sec = 0; 
            val.it_interval.tv_nsec = 450000000;
        struct sigevent sev; 
        memset(&sev, 0, sizeof(struct sigevent)); 
            sev.sigev_signo = SIGHUP; 

        timer_create( CLOCK_REALTIME, &sev, &timerid); 
        timer_settime(timerid, 0, &val, NULL); 

        signal(SIGHUP, handler);
        signal(SIGUSR1, SIG_IGN); 
        signal(SIGTERM, SIG_IGN); 

        while(1)
        {
            
            if(cykl > 10)
                goodbye(); 
        } 

    return 0; 
}

void handler(int sig)
{
    if(cykl%2)
    {
        nanosleep(&ts, NULL); //spi dodatkowo 0,225sek, zeby miedzy sygnalami bylo 0,675sek
        for(int i=0; i<ilepisarzy; i++)
        {
            kill(pidy[i], SIGUSR1); 
        } 
    }  
    else  //kopia
    {        
        char* buff;
        buff = (char*)malloc(50*sizeof(char)); 
        lseek(tablica, (off_t)0, 0); 
        read(tablica, buff, 50);
        write(archiwum, buff, 50); 
    }

    cykl++;
}

void goodbye()
{
    for(int i=0; i<ilepisarzy; i++)
    {
        kill(pidy[i], SIGTERM); 
    } 

    close(tablica);
    close(archiwum);
    close(dane);

    printf("\n\t\tGOODBYE:)\n");  
    execlp("rm", "rm", tabfile, NULL); 
}