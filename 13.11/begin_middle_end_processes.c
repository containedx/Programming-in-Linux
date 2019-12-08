#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define DESCRIPTOR 68

char** cut_param(int n, char** p);

int main( int argc, char** argv)
{
        int fd[2];  //fd[0] - input 
	            //fd[1] - output 


        if(argc == 1) //ostatni 
		{
			printf("Jestem ostatnim potomkiem, nie mam juz argumentow\n"); 

			//if(/*otwarty potok*/)
			//{
				/*wypisz na stdout z potoku*/
				char output[100];
				read(fd[0], output, 100);
				printf("OUTPUT: %s \n", output); 
				close(fd[0]); 
			//}
			//else
			//{
			//	perror("blad, brak potoku, brak parametrow"); 
			//}
		}

		else if( argc > 1 )
		{	

			//if( zamkniety ) //=> pierwszy 
			//{
				// otworz potok
				if( pipe(fd) == -1 ) 
					perror("pipe fail");
				write(fd[1], argv[1], strlen(argv[1]+1));
				dup2(fd[0], STDIN_FILENO); 
				close(fd[1]);
			//}	

			//jesli otwarty to => srodkowy
			//kopiuj do nowego potoku, wpisz nowy parametr

			printf("%s\n", argv[1]);
			char* param[] = {argv[0], NULL }; 
			execvp( argv[0], param  ); 

		}
	

	return 0; 
}

char** cut_param( int n, char** p )
{
	char* param[n-2]; 

	for(int i=0; i< n-2; i++) 
	{
		param[i] = p[i+2]; //bo 0 to program, a 1param obcinamy
	}

return param; 
}
