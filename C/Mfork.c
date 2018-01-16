#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include "structure.h"
#include "prng.h"

int main()
{

int y;
int i;
int j;
pid_t pid;
	
int num[] ={44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
voiture p[20];



int IDmemoire; // identifiant du segment de mémoire partagée
voiture * pointeurMPartagee; // pointeur sur l'adresse de la MP

voiture * pointeurMPere;

pointeurMPartagee = p;

voiture fils;
	
 	//créer mémoire partagée A FAIRE DANS PERE pour que les fils aient l'adresse
	

	// shmget : allouer un segment de mémoire partagée
	// Renvoie l'ID du segment de MP associé à la clé
	// 	MAIS un nouveau segment est créé si aucun seg de mem n'est associé à la clé ( ou si IPC_PRIVATE)
	if( (IDmemoire =  shmget( 42 , 20* sizeof( voiture ), 0666 | IPC_CREAT )) == -1 )
	{
		perror("Erreur de création de la M P");
		exit(1);

	}
	

	// Attacher le segment de M P identifié par shmid à l'espace mémoire du processus appellant
	// SI shmaddr est a NULL, le system choisit une addresse convenable pour attacher le segment.
	// SUCCES => pointeurMPartagee recoit l'adresse du segment de mém partagé.
	if ( (pointeurMPartagee = (voiture*) shmat( IDmemoire , NULL , 0 )) == (void*) -1 )
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
		else if ( pid == 0 )
		{
		
			int id;
			id = getpid();	
			
			fils.numVoiture = num[i];
			fils.s1 = 0.0;
			fils.s2 = 0.0;
			fils.s3 = 0.0;
			fils.tour = 0.0;
			fils.tot = 0.0;
			fils.crash = 0;
			fils.pit = 0;
			fils.meilleurS1 = 500000.0;
			fils.meilleurS2 = 500000.0;
			fils.meilleurS3 = 500000.0;
			fils.tourRestant = 0;
			fils.meilleurTour = 1000.0;
	
			voiture *v = &fils;
			int g;
			for( g=0; g<50 ; g++){
				
			
				carSys( v );
				fils.tourRestant = g;
			
			pointeurMPartagee[i] = fils;
			}
			exit(0);
	
		}
	
	}		
			
		for(y=0;y<35;y++)
		{	
			printf(" pid : %d	y : %d\n", getpid(), y );
			// sémaphore ici			
			pointeurMPere = memcpy( p, pointeurMPartagee , 20*sizeof(voiture) );
				usleep(1000000);

				system("clear");
				int bcl;
				for(bcl=0; bcl<20 ; bcl++)
				{
				printf("N° = %d  temps s1 : %.3lf	", p[bcl].numVoiture, p[bcl].s1);
				printf("s2 : %.3lf 	s3 : %.3lf", p[bcl].s2, p[bcl].s3);
				printf(" total : %3lf Status : %d\n", p[bcl].tot, p[bcl].tourRestant);
				}
		
			/*
			printf("num voiture : %d\n", pointeurMPartagee[y].numVoiture);
			printf("S1 : %.3f\n", pointeurMPartagee[y].s1);
			printf("S2 : %.3f\n", pointeurMPartagee[y].s2);
			printf("S3 : %.3f\n", pointeurMPartagee[y].s3);
			*/
		}

		voiture *pointeurMPere2;
		pointeurMPere2 = memcpy( p, pointeurMPartagee, 20*sizeof(voiture) );
		voiture qualif[ sizeof(voiture)*20 ];

		voiture *pointeurX = qualif;
	
		pointeurX = triageQualif( p );
		system("clear");
		int bcl2;
		for( bcl2=0; bcl2 < 20 ; bcl2++ )
		{
			printf("N° voiture = %d		meilleur temps = %.3lf\n", pointeurX[bcl2].numVoiture, pointeurX[bcl2].meilleurTour);
		}


	return 0;


}
