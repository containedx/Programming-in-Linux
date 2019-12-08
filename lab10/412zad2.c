#include <stdio.h>
#include <time.h> 
#include <signal.h>
#include <string.h>

static void functionHandlingSignal()
{
    printf("i received signal SIGUSR1 or sth like that"); 
}


int main()
{
    
  struct sigaction A;
  memset(&A, '\0', sizeof(A));
  A.sa_handler = &functionHandlingSignal; 

  if(sigaction(SIGUSR1, &A, NULL) < 0){
    perror("sig erroor");
    return 1; 
  }        
    
  int i = 0; 

  struct timespec ts;    
  struct timespec before;
  struct timespec after; 
  ts.tv_sec = 1; 
  ts.tv_sec = 0; 
  
  while( i != 30 )
  {
    clock_gettime( CLOCK_REALTIME_COARSE, &before); //DEBUG WITH -lrt
    nanosleep(&ts, 0); 
    clock_gettime( CLOCK_REALTIME_COARSE, &after);
    
    long int deltaS = after.tv_sec-before.tv_sec;
    long int deltaNS = after.tv_nsec-before.tv_nsec;
    
    if(deltaNS < 0 )
    {
     deltaS -= 1;
     deltaNS = 1000000000 - deltaNS; 
    }
    
    
    if(i%2 == 0)
      ts.tv_nsec += 500000000; 
    else
    {
      ts.tv_sec += 1;
      ts.tv_nsec = 0; 
    }
    
    printf("before: %ld s %ld ns\t after: %ld s %ld ns\n delta: %ld s %ld ns \n\n",
	   before.tv_sec, before.tv_nsec, after.tv_sec, after.tv_nsec,
	   deltaS, deltaNS);
    i++;
  }  
  
}
