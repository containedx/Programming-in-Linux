#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

struct timespec ts = { 2, 66000000 }; 

static void action(int sig, siginfo_t *siginfo, void *context)
{
   printf("I received signal %d  , %d", sig, siginfo->si_code); 
}

int main()
{  

  //signal(SIGABRT, SIG_IGN); //chyba ignoruje sygnal abort??
  //signal(SIGINT, SIG_IGN);

  struct sigaction act; 
  memset(&act, '\0', sizeof(act)); 

  act.sa_sigaction = &action; 
  act.sa_flags = SA_SIGINFO; 
  
  if (sigaction( SIGINT, &act, NULL) == -1)
  {
    perror("error sig"); 
    return 1;
  }
  
  while(1)
  {
    nanosleep( &ts, 0 );
    printf("no action\t"); 
  }
  
  return 0;   
}