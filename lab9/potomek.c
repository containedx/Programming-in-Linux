#include <stdio.h>
#include <signal.h>

struct timespec ts = { 2, 66000000 };

int main()
{
	printf("odblokuj mnie! ( %d ) \n", getpid() ); 
	nanosleep(&ts, NULL); 
	raise( SIGSTOP ); 
	printf("dzieki! \n"); 
}
