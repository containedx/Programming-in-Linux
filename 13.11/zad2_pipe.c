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
    
    char* mypipe = "/tmp/mypipe";   //NAMED PIPE
    mkfifo( mypipe, 0666); 

	if( pipe(fd)==-1 )
	{
		perror("pipe failed"); 
		exit(1); 
	}

	//rodzic odczytuje randomowa zmienna i wrzuca do kanalu 
			int randata = open("/dev/urandom", O_RDONLY ); 
			char input[nofbytes];			       	 	
			read(randata, input, sizeof(input)); 
			close(randata);
            printf("\tinput: %s\n", input); 
			
            
	for(int i=0; i<N; i++)
	{
	
		if ((pid[N]=fork()) == 0 ) //=>child 
		{
			printf("Hello, here child number:> %d < \n", i+1);
			//odczytuje z kanalu liczbe i tyle spi
			close(fd[1]);
            fd[0] = open( mypipe, O_RDONLY);
			char output[nofbytes]; 
            read(fd[0], output, sizeof(output));
			printf("%s\n\n", output);
			exit(0); 	
		}
		
		else
        {
             close(fd[0]); 		
             fd[1] = open( mypipe, O_WRONLY);
             //char inputx[] = "inputtest"; 
             write(fd[1], input, sizeof(input));
             printf("parent wrote: %s \n", input); 
        }
	}
		
	
	//while(1)  
		//{
			//printf("Hello, here parent;> ");
		//	close(fd[0]); 			
       //     write(fd[1], input, strlen(input)+1);
			
	//	}
		
	

// zrobic globalnie char [N] i odczytac z tego random a pozniej wrzucac po kolei od [i]. geniusz !

return 0;
}
