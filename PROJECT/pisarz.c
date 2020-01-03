#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int opt;
    int N;
    int fd = strtol(argv[1], 0, 10);
    int offset = strtol(argv[2], 0, 10);
    char komunikat[20];
    strcpy(komunikat, argv[3]); 

    printf("nr deskryptora: %d\n", fd);
    printf("przesuniecie: %d\n", offset); 
    printf("komunikat: %s | %s\n", komunikat, argv[3]); 

    while( (opt = getopt( argc, argv, "N:" )) != -1)
    {
        if(opt == 'N')
        {
            N = strtol(optarg, 0, 10);
            printf("krotnosc: %d\n", N); 
        }
    }

    return 0; 
}