#include <stdio.h>
#include <time.h> 

int main()
{

struct timespec ts; 
struct timespec res; 

clock_gettime(CLOCK_MONOTONIC, &ts);

//sprawdzenie rozdzielczosci

clock_getres(CLOCK_REALTIME, &res); // 0 if success
printf("realtime: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_REALTIME_COARSE, &res);
printf("realtime coarse: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_MONOTONIC, &res);
printf("monotic: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_MONOTONIC_COARSE, &res);
printf("monotic coarse: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_MONOTONIC_RAW, &res);
printf("monotic raw: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_BOOTTIME, &res);
printf("boot time: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res);
printf("process cputime id: %ldns\n", res.tv_nsec); 

clock_getres(CLOCK_THREAD_CPUTIME_ID, &res);
printf("thread cputime id: %ldns\n", res.tv_nsec); 



  
}