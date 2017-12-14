#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "structure.h"

int main()
{

int y;
int i;
pid_t pid;
	

int IDmemoire; // identifiant du segment de mémoire partagée
void* pointeurMPartagee; // pointeur sur l'adresse de la M P


	
 	//créer mémoire partagée A FAIRE DANS PERE pour que les fils aient l'adresse
	

	// shmget : allouer un segment de mémoire partagée
	// Renvoie l'ID du segment de MP associé à la clé
	// 	MAIS un nouveau segment est créé si aucun seg de mem n'est associé à la clé ( ou si IPC_PRIVATE)
	//
	// SUCCES => renvoie un identifiant de segment shmid valide
	// ERREUR => return -1
	if( (IDmemoire =  shmget( IPC_PRIVATE , 20* sizeof( voiture ), 0666 | IPC_CREAT )) == -1 )
	{
		perror("Erreur de création de la M P");
		exit(1);

	}
	

	// Attacher le segment de M P identifié par shmid à l'espace mémoire du processus appellant
	// SI shmaddr est a NULL, le system choisit une addresse convenable pour attacher le segment.

	// SUCCES => pointeurMPartagee recoit l'adresse du segment de mém partagé.
	// ERREUR => return -1
	if ( (pointeurMPartagee = shmat( IDmemoire , NULL , 0 )) == (void*) -1 )
	{
		perror("Erreur pour obtenir l'adresse de mém partagée");
		exit(1);
	}
	
	// donc à faire dans les fils???



	for( i = 0 ; i<20 ; i++)
	{

	pid = fork();
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
	
	// attendre les 20 processus fils
	for( y=0 ; y<20 ; y++){
		wait(-1);
	}
}


}
