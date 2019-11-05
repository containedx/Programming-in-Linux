//proces nadrzedny ma tworzyc 20 potomków 
//nalezacych na przemian do tej samej grupy co rodzic/specjalnie utworzonej 
//nastepnie proces nadrzedny czeka na smierc potomków i nastepnie sam ginie. 


#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

float f(float n) 
{
	if( n==1 )
		return 1; 
	else return 1/n + f(n-1); 
}

int main( int argc, char** argv)
{
	pid_t pids[20]; 
	
	for(int i=0; i<20; i++)
	{
		if( i%2 == 0 )
		{	sleep(1); 
			if( (pids[i] = fork()) == 0 ) //-->child<--
			{
				printf("%d: pid: %d grouppid: %d\n", i, pids[i], getpgrp());
		        	exit(NULL);	
			}
		}
		else
		{
			sleep(1);
			if( (pids[i] = fork() ) == 0 ) 
			{
				setpgrp(); 
				printf("%d: pid: %d grouppid: %d\n", i, pids[i], getpgrp());
				exit(NULL); 

			}

		}

	}

	for(int i=0; i<20; i++)
	{
		waitpid(pids[i]); 
	}

}
