#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main( int argc, char** argv )
{
	//int time = strtol(argv[1], 0, 10); 
	//printf("%d <- tyle nanosekund czekam ", time );
	struct timespec ts = { 1, 0 }; 
	nanosleep( &ts, NULL); 
	printf("*** hej, jestem dziecko *** \n");
	nanosleep( &ts, NULL);
	printf("bye\n"); 
        

   return 0;  
}
