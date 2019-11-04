#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <time.h>

// to jest rodzic. Tworzy on P0, L1 i L2. 
// P0 generuje P1 i P2

int main(int argc, char** argv)
{
	int opt;
	char *ltime, *ptime, *rtime;

	while( (opt = getopt( argc, argv, "l:p:r:" ) != -1 )) 
		// to ma pobierac jako argumenty czas, do dopracowania
		{
		switch(opt) 
		{
			case 'l':
				ltime = optarg; // = strtof( optarg, 0 );
				break;
			case 'p':
				ptime = optarg; //= strtof( optarg, 0 ); 
		;		break; 
			case 'r':
				rtime = optarg;  //= strtof( optarg, 0 ); 
				break; 
		}

		}

	pid_t p0, l1, l2; 
	
	//fork(); 

	switch( l1 = fork())
	{
		case -1:
			return -1;
		case 0:
			printf("egzekuje dziecko l1\n");
			execl("kid", ltime);
		default: 
			sleep(1);
			printf("spie, elo ~ l1\n");
			break;
	}

	switch( l2 = fork() )
	{
		case -1:
			return -1;
		case 0: 
			printf("egzekuje dziecko l2\n");
			execl("kid", ltime); 
		default: 
			sleep(1);
			printf("spie, elo ~l2\n");
			break;;;
	}

	switch( p0 = fork()) 
	{
		case -1:
			return -1; 
		case 0:
			fork();
			printf("jestem p0 i tworze teraz potomka p1 lub p2\n");
			execl("kid", ptime );
			break;
		default: 
			sleep( 1 );
		        printf("spie, elo, tu p0\n"); 	
			break;
	}

	

	return 0; 
}
