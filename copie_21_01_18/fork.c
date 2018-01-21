#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include "structure.h"
#include "prng.h"
// 1er argument durée essai 1
// 2ème argument durée essai 2
// 3ème argument durée essai 3
// 4ème argument durée qualif 1
// 5ème argument durée qualif 2
// 6ème argument durée qualif 3
// 7ème argument nombre de tours de la course
int main(int argc, char *argv[])
{
int i;
pid_t pid;

int numEssai1[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int numEssai2[20];
int numEssai3[20];
int *nEssai1 = numEssai1;
int *nEssai2 = numEssai2;
int *nEssai3 = numEssai3;
	
int num[] ={44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
voiture p[20];

int IDmemoire; // identifiant du segment de mémoire partagée
voiture * pointeurMPartagee; // pointeur sur l'adresse de la MP
voiture * pointeurMPere;
pointeurMPartagee = p;
voiture fils;

// mémoire partagée pour les différents tour
int IDmemoire2;
gp grandPrix;
gp *pointeurGP = &grandPrix;
	
 	//créer mémoire partagée DANS PERE pour que les fils aient l'adresse
	if( (IDmemoire =  shmget( 42 , 20* sizeof( voiture ), 0666 | IPC_CREAT )) == -1 )
	{
		perror("Erreur de création de la M P");
		exit(1);
	}
	// Attacher le segment de M P identifié par shmid à l'espace mémoire du processus appellant
	if ( (pointeurMPartagee = (voiture*) shmat( IDmemoire , NULL , 0 )) == (void*) -1 )
	{
		perror("Erreur pour obtenir l'adresse de mém partagée");
		exit(1);
	}
	// mémoire partagée grand Prix
	if( ( IDmemoire2 = shmget( 43, sizeof( gp ), 0666 | IPC_CREAT ) ) == -1)
	{
		perror("Erreur 2ème MP");
		exit(1);
	}
	if( (pointeurGP = shmat( IDmemoire2, NULL, 0) ) == (void*) -1 )
	{
		perror("Erreur obtention 2ème adress MP");
		exit(1);
	}
	
	// initialisation de grandPrix
	grandPrix.essai1 = 0;
	grandPrix.essai2 = 0;
	grandPrix.essai3 = 0;
	grandPrix.qualif1 = 0;
	grandPrix.qualif2 = 0;
	grandPrix.qualif3 = 0;
	grandPrix.course = 0;	
	

	for( i = 0 ; i<20 ; i++)
	{
		pid = fork();
		if( pid == -1 ){
		
			printf("Erreur de fork!\n");
			exit(-1);
		}
		else if ( pid == 0 )
		{	
			fils.numVoiture = num[i];
			init( &fils );
			fils.q2 = 1;
			fils.q3 = 1;
			fils.course = 1;
			pointeurMPartagee[i] = fils;
			
			while( pointeurGP->essai1 == 0 )
			{	usleep(500000);		}
			
			int g=0;
			while(fils.tot < atoi(argv[1]) && fils.crash == 0)
			{	
				carSys(&fils,(50 - g), g, atoi(argv[1]) );
				fils.tourRestant = g;
				pointeurMPartagee[i] = fils;
				g++;
			}
		
			while( pointeurGP->essai2 == 0)
			{	usleep(500000);		}
			init( &fils );	
			init( &pointeurMPartagee[i] );
			//pointeurMPartagee[i] = fils;
			g=0;
			while(fils.tot < atoi(argv[2]) && fils.crash == 0)
			{
				carSys( &fils,(50-g), g, atoi(argv[2]));
				fils.tourRestant = g;
				pointeurMPartagee[i] = fils;
				g++;
			}
			
			while(pointeurGP->essai3 == 0)
			{	usleep(500000);		}
			init( &fils );	
			init( &pointeurMPartagee[i] );
			//pointeurMPartagee[i] = fils;
			g=0;
			while(fils.tot < atoi(argv[3]) && fils.crash == 0)
			{
				carSys(&fils,(50-g),g, atoi(argv[3]));
				fils.tourRestant = g;
				pointeurMPartagee[i] = fils;
				g++;
			}
		
			while(pointeurGP->qualif1 == 0)
			{	usleep(500000);		}
			init( &fils);
			init( &pointeurMPartagee[i] );
			//pointeurMPartagee[i] = fils;
			g=0;
			while(fils.tot < atoi(argv[4]) && fils.crash == 0)
			{
				carSys(&fils,(50-g), g, atoi(argv[4]));
				fils.tourRestant = g;
				pointeurMPartagee[i] = fils;
				g++;
			}

			while(pointeurGP->qualif2 == 0)
			{	usleep(500000);		}
			
			for(g=0;g<6;g++)
			{
				if( pointeurGP->q1[g] == fils.numVoiture )
				{
					fils.q2 = 0;
				}
			}
			init(&fils);
			init( &pointeurMPartagee[i] );
			if( fils.q2 == 1 )
			{
				g=0;
				while(fils.tot < atoi(argv[5]) && fils.crash == 0)
				{
					carSys(&fils,(50-g),g, atoi(argv[5]));
					fils.tourRestant = g;
					pointeurMPartagee[i] = fils;
					g++;
				}
			}
			
			while(pointeurGP->qualif3 == 0)
			{	usleep(500000);		}

			for( g=0;g<6;g++)
			{
				if(pointeurGP->q2[g] == fils.numVoiture)
				{
					fils.q3 = 0;
				}
			}
			init( &fils );
			init( &pointeurMPartagee[i] );
			
			if( fils.q3 == 1 && fils.q2 == 1 )
			{
				g=0;
				while(fils.tot < atoi(argv[6]) && fils.crash == 0)
				{
					carSys(&fils,(50-g), g, atoi(argv[6]));
					fils.tourRestant = g;
					pointeurMPartagee[i] = fils;
					g++;
				}
			}
			while(pointeurGP->course == 0)
			{	usleep(500000);		}
			
			init(&fils);
			init(&pointeurMPartagee[i]);
			g=0;
			while(fils.tourRestant < atoi(argv[7]) && fils.crash == 0)
			{
				carSys(&fils,(50-g),g, 1200);
				fils.tourRestant = g;
				pointeurMPartagee[i] = fils;
				g++;
			}

			exit(0);
		}
	}
	
		pointeurGP->essai1 = 0;
		pointeurGP->essai2 = 0;
		pointeurGP->essai3 = 0;
		pointeurGP->qualif1 = 0;
		pointeurGP->qualif2 = 0;
		pointeurGP->qualif3 = 0;
		pointeurGP->course = 0;
		
		voiture *X;

		while( pointeurGP->qualif3 == 0 )
		{
		int r;
		if(pointeurGP->qualif2 == 1 )
		{
			for(r=8;r<14;r++)
			{
				pointeurGP->q2[r-8] = X[r].numVoiture;
			}
			printf("Lancer qualif 3 ?");
			viderBuffer();
			pointeurGP->qualif3 = 1;
		}
		else if(pointeurGP->qualif1 == 1)
		{
			for(r=14;r<20;r++)
			{
				pointeurGP->q1[r-14] = X[r].numVoiture;
			}
			printf("Lancer qualif 2 ?");
			viderBuffer();
			pointeurGP->qualif2 = 1;
		}
		else if(pointeurGP->essai3 == 1)
		{	
			printf("Lancer qualif 1 ?");
			viderBuffer();
			pointeurGP->qualif1 = 1;
		}
		else if(pointeurGP->essai2 == 1)
		{
			printf("Lancer essai 3 ?");
			viderBuffer();
			pointeurGP->essai3 = 1;
		}
		else if(pointeurGP->essai1 == 1)
		{
			printf("Lancer essai 2 ?");
			viderBuffer();
			pointeurGP->essai2 = 1;
		}
		else if(pointeurGP->essai1 == 0)
		{
			printf("Lancer essai 1 ?");
			viderBuffer();
			pointeurGP->essai1 = 1;
		}
		voiture qualif[ sizeof(voiture)*20];
		X = qualif;
		int z; // pour les boucles
		if( pointeurGP->qualif1 == 0)
		{
			for(i=0;i<25;i++)
			{		
				pointeurMPere = memcpy( p, pointeurMPartagee , 20*sizeof(voiture) );
				X = triageQualif( p );
				affichage1( pointeurMPere, pointeurMPartagee, X, pointeurGP, nEssai1, nEssai2, nEssai3 );
			}
			if(pointeurGP->essai3 == 1)
			{
				// !!!!!!!!!!!!!!!!!!!! afficher temps essai (code tout à la fin)
				viderBuffer();
				afficherEssai(X);
				
			}
		}
		else if(pointeurGP->qualif1 == 1 && pointeurGP->course == 0)
		{
			for(i=0;i<25;i++)
			{
				pointeurMPere = memcpy(p,pointeurMPartagee,20*sizeof(voiture));
				X = triageQualif( p );
				affichage1( pointeurMPere, pointeurMPartagee, X, pointeurGP, nEssai1, nEssai2, nEssai3 );
			}
		}
		


	}// while
	
	// affichage grille départ
	printf("Voulez-vous afficher la grille de départ ?");
	viderBuffer();
	affichageGrille(X, pointeurGP);
	
	int c;
	while(c!='\n' && c != EOF)
	{
		c = getchar();
	}
	// affichage des temps de la course.
	pointeurGP->course = 1;
	for(i=0;i<110;i++)
	{
		pointeurMPere = memcpy(p,pointeurMPartagee,20*sizeof(voiture));
		X = triageCourse(p);
		affichage1(pointeurMPartagee, pointeurMPartagee, X, pointeurGP, nEssai1, nEssai2, nEssai3);
	}

	return 0;
}
