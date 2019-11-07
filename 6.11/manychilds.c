#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>


int main( int argc, char** argv)
{
	siginfo_t info;
	int i; 
	
	printf("hello, i am%d from %d group\n", getpid(), getpgid() );
	sleep(3); 

	for(i=1; i<argc; i++)
	{   
	   if( fork() == 0)
	   {
		printf("%d: pid: %d gpid: %d parametr: %s\n", i, getpid(), getpgid(), argv[i]); 
		execlp("sleep", "sleep", argv[i], NULL); 
	   }   
	}


	while(1)
	{
		if( ! (waitid(P_ALL, 1, &info, WEXITED | WNOHANG) ))
		{
			if( info.si_pid )
			{
				printf("process exited, pid: %d status: %d\n", info.si_pid, info.si_status);
			}
		}
		else
		{
			perror("ERROR");
			break; 
		}
	
	}

return 0; 
}
