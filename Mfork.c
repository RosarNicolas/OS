#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

int i;
pid_t pid;
int buffer[255];

for( i = 0 ; i<5 ; i++)
{

	pid = fork();
	/*	
	if( i = 4 ){
		return 0;
	}*/
	if( pid == -1 ){
		
		printf("Erreur de fork!\n");
		exit(-1);

	}
	else if ( pid == 0 ){
		
		int id;
		id = getpid();
		
	
		printf("Je suis le fils.\n");
		exit(0);
	}

}


}
