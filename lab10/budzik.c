#include <stdio.h>
#include <time.h>
#include <signal.h>

void timer_callback(int sig) {

    printf("\t*********ALARM*********\n\n"); 
    //wysyla do siebie sygnal sigusr2:
    kill(getpid(), SIGUSR2); //== raise(SIGUSR2); 
}

void sighandlerxd(int sig) {

    printf("wyslalem do siebie SIGUSR2 xD"); 
}

int main(int argc, char* argv[])
{

timer_t timerid; 
struct itimerspec value; 
value.it_value.tv_sec = 2; //czekaj 2sek przed wyslaniem sygnalu
value.it_value.tv_nsec = 0;
value.it_interval.tv_sec = 4;//wysylaj co 4 sekundy
value.it_interval.tv_nsec = 0;

timer_create(CLOCK_REALTIME, NULL, &timerid); 
timer_settime (timerid, 0, &value, NULL);

signal(SIGALRM, timer_callback);
signal(SIGUSR2, sighandlerxd);

    while(1)
    {
        printf(" XD "); 
        sleep(1); 
    }
}
