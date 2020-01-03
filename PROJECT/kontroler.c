#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int opt; 
    int N; 

    while( (opt = getopt( argc, argv, "d:b:l:N:" )) != -1)
    {
        switch(opt)
        {
            case 'd':
            printf("plik z danymi: %s\n", optarg);
            break;

            case 'b': 
            printf("tablica ogloszeniowa: %s\n", optarg);
            break;

            case 'l':
            printf("archiwum X : %s\n", optarg);
            break;

            case 'N':
            N = strtol( optarg, 0, 10);
            printf("opcjonalny parametr(czyli jebac?): %d\n", N);
        }
    }

    return 0; 
}