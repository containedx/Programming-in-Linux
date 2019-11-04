#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h> 

int main(int argc, char** argv)
{
	int opt;
	float ltime, ptime, rtime; 

	while( (opt = getopt( argc, argv, "l:p:r:" ) != -1 ))
		{
		switch(opt) 
		{
			case 'l':
				ltime = strtof( optarg, 0 );
				break;
			case 'p':
				ptime = strtof( optarg, 0 ); 
				break; 
			case 'r':
				rtime = strtof( optarg, 0 ); 
				break; 
		}

		}

	fork();	
	if( fork() == 0 )
	{
		fork(); 
		execl( "kid", NULL); //jesli dziecko to exec
	}
	else 
		printf("\nxxx hello iam parent xxx\n"); 



	return 0; 
}
