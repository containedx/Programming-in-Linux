#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

struct timespec ts = {1, 0}; 

void clear(int fd) 
{

	time_t czas; 
	time(&czas);
	char* data = ctime( &czas ); 
	printf("\nzwolniono plik %s", data);
 	close(fd); 

       nanosleep( &ts, NULL); 	


}

int main( int argc, char** argv)
{
int n = argc; 
int file[n]; 

for(int i=1; i < n; i++)
{
   file[i] = open( argv[i], O_RDWR | O_CREAT | O_EXCL, S_IRUSR); //(plik, tryb, uprawnienia)
  printf("otwarto plik %s \n", argv[i]);  

  time_t cz;
  time( &cz );
  char* dat = ctime( &cz ); 
  write( file[i], dat, sizeof(dat)); 


   on_exit( clear, file[i] ); 
}



}
