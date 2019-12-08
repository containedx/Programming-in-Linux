#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv)
{
    float n = 50; 
    int opt;
    int infile;
    int outfile; 
    int option=0;
  
  while( (opt = getopt( argc, argv, "zxN:i:o:" )) != -1 )
  {
     // 1==zwykly na dziury
		    // 0==dziury na zwykly
    
      switch(opt)
      {
			case 'z':
				option = 0; 
				printf("dziurawy przerobie na zwykly\n");
			break; 
			
			case 'x':
				option = 1; 
				printf("zwykly przerobie na dziurawy\n"); 
			break; 
			
			case 'N':
				n = strtof(optarg, 0);
				printf("n bajtow = %f", n );
			break; 
			
			case 'i':
				infile = open( optarg, O_RDONLY ); 
				printf("otwarto plik %s\n", optarg); 
			break;
			
			case 'o':
				outfile = open( optarg, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU ); 
				printf("otwarto plik %s\n", optarg);
			break; 
	
      }     
      
      
  }
  
      if(option) //zwykly na dziury
      {
		  char nl[] = "\n"; 
		  char nb[(int)n];

		  while(read(infile, nb, sizeof(nb)))
			{
				
				write( outfile, nb, sizeof(nb)); 
				write( outfile, nl, sizeof(nl));	

			}
      }
      
      else //dziury na zwykly 
      {
		  char nb[(int)n];
		  while(read(infile, nb, sizeof(nb)))
			{				
				write( outfile, nb, sizeof(nb)); 
				lseek( infile, 2, SEEK_CUR); //omija "dziure"	

			}
      }
  
  
  
  
  
 return 0;  
}