/* potomek: /lub i nie
printf("Prosze mnie odblokowac: (%d)\n", getpid());
raise(SIGSTOP);
printf("Dziekuje uprzejmie \n");
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

struct timespec ts = { 2, 66000000 }; // ~ 8/3 sek

int main() 
{
  int pid; 
   
  
  if( (pid = fork()) == 0 )
  {
    execv("./potomek", NULL); 
  }  
  
  else
  {
    //waitd id zbadac ze potomek poszedl spac. jesli tak to go obudzic
    siginfo_t inf;
    
    waitid( P_ALL, 0, &inf, WSTOPPED | WEXITED); 
    
    if( inf.si_code == CLD_STOPPED )
    {
      printf("\ndziecko sie zatrzymalo, wznawiam\n");
      kill(pid, SIGCONT); 
    }
    else if( inf.si_code == CLD_KILLED || inf.si_code == CLD_EXITED )
    {
      printf("potomek umarl\n");  
    }
    
   
  }
  
  
}