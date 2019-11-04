#include <stdio.h>
#include <time.h> 

int LP=0; 
struct timespec ts = {1, 0};

void clear( void )
{
	printf("\nzwalniamzasoby, stan licznika %d", LP); 
	LP--; 

	time_t czas;
	time(&czas);
	char* data = ctime( &czas);
	printf("\n%s\n\n", data);
	nanosleep( &ts, NULL); 


}


int main(int argc, char** argv)
{
        int N = strtol(argv[1], 0, 10); //parametr 
	 

	while(N!=0) 
	{
		printf("\nLP: %d", LP);
		LP++;
		atexit( clear ); 
		nanosleep(&ts, NULL); 
		N--;
	}

	 

	return 0; 
}
