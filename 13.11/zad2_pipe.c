#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int N = strtol(argv[1], 0, 10); //parametr = liczba potomkow
	printf("Liczba potomkow: %d\n\n", N); 
	int fd[2]; 
	int nofbytes = 10; 
	int pid[N]; 

	if( pipe(fd)==-1 )
	{
		perror("pipe failed"); 
		exit(1); 
	}

	for(int i=0; i<N; i++)
	{
	
		if ((pid[N]=fork()) == 0 ) //=>child 
		{
			printf("Hello, here child number:> %d < \n", i+1);
			//odczytuje z kanalu liczbe i tyle spi
			close(fd[1]); 
			char output[nofbytes]; 
		        read(fd[0], output, sizeof(output));
			printf("%s\n\n", output); 	
		}
		else //=>parent 
		{
			//printf("Hello, here parent;> ");
			//rodzic odczytuje randomowa zmienna i wrzuca do kanalu 
			int randata = open("/dev/random", O_RDONLY ); 
			char input[10]; 
			read(randata, input, sizeof(input)); 
			close(randata);
			
			close(fd[0]); 
			
		        write(fd[1], input, strlen(input)+1);
		}
		



	}	




return 0;
}
