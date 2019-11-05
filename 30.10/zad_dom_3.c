#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(int argc, char** argv)
{
	//srand( time(NULL ) ); 	
	float N = strtof(argv[1], 0);
	printf("%f", N);	
	int num; 
	int stat; 
	pid_t procesy[20];


	for(int i=0; i<20; i++)
	{
		sleep(1); 
		if( (procesy[i] = fork()) == 0 )
		{
			//sleep( N * pow(3, -2) );
			//sleep(3);
			srand(time(0));  
			num = ( rand() % ( 33 ));
			printf("\n%d:%d, num: %d\n",i,procesy[i], num);
			if( num < 32 )
				exit( num ); 
			else 
				abort(); 
		}
	}
	
	for(int i=0; i<20; i++)
	{
		pid_t cpid = waitpid(procesy[i], &stat);  
		printf("child %d: %d, exit status: %d\n",i, cpid, WEXITSTATUS(stat)); 
	}

	exit(0); 
	return 0; 
}
