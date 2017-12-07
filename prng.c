#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prototypes.h"

int main()
{
srand(time(NULL));
int v;
int tourRestant = 50;
int proba;
//double meilleurGlobalS1 = 500000.0;
//double meilleurGlobalS2 = 500000.0;
//double meilleurGlobalS3 = 500000.0;
global g;
g.bestGlobalS1 = 500000.0;
g.bestGlobalS2 = 500000.0;
g.bestGlobalS3 = 500000.0;

// déclaration du tableau avec toutes les voitures
voiture voitures[20] ;// {44, 77, 3, 33, 5, 7, 11, 31, 19, 18, 14, 2, 10, 55, 8, 20, 27, 30, 9, 94};	
for( v = 0; v < 20; v++)
{	
 // mémoire allouée en même temps que création des struct voiture
// assignation des valeurs par défaut
	voitures[v].numVoiture = v+1;
	voitures[v].s1 = 0.0;
	voitures[v].s2 = 0.0;
	voitures[v].s3 = 0.0;
	voitures[v].tour = 0.0; 
	voitures[v].tot = 0.0;
	voitures[v].crash = 0; // 1 crashé    0 Ok
	voitures[v].pit =0;
	voitures[v].meilleurS1 = 500000.0;
	voitures[v].meilleurS2 = 500000.0;
	voitures[v].meilleurS3 = 500000.0;

}

// BOUCLE GLOBALE
int i;

for(i = 1 , proba = 25; i < 51 ; i++,proba--)
{
int y = 0;
for(y= 0; y<20; y++){	
	
	voitures[y].s1 = (double) secteur1( i, y , &voitures[y] )/1000.0;	
	if(voitures[y].crash == 0)
	{
		voitures[y].meilleurS1 = min(voitures[y].meilleurS1, voitures[y].s1);
	}
	voitures[y].s2 = (double) secteur2( i, y, &voitures[y] )/1000.0;
	if(voitures[y].crash == 0)
	{
		voitures[y].meilleurS2 = min(voitures[y].meilleurS2, voitures[y].s2);
	}
 
	voitures[y].s3 = (double) secteur3( i, y, &voitures[y] )/1000.0;
	
		// vérifié que voiture pas crashé
		if(voitures[y].crash != 1){
			if(voitures[y].pit==0 && pit(proba) == 1 ){  // SI voitures[y].pit = 0    ET    pit(.....) est égal à 1 ALORS ==> ajoute temp pit
				// ajout du temps du pit au s3
				voitures[y].s3 += (double)myRand(6000,25000)/1000.0; // %6 car temps au pit stop entre 25 et 30 secondes
				printf("Je suis passé au pit première fois au tour : %d\n", i );
				voitures[y].pit = 1;
			}
		
			else if(voitures[y].pit == 1 && pit(voitures[y].tourRestant) == 1 && tourRestant !=1)
			{
				voitures[y].s3 += (double)myRand(8000,25000)/1000.0;
				printf("Je suis passé au pit pour la 2eme fois\n"); 
				voitures[y].pit = 2;
			} 
		}
	
	if( voitures[y].crash == 0)
	{
		voitures[y].meilleurS3 = min( voitures[y].meilleurS3, voitures[y].s3);
	}
	voitures[y].tour = 0.000;
	voitures[y].tour = voitures[y].s1;
	voitures[y].tour += (voitures[y].s2 + voitures[y].s3);
	voitures[y].tot = voitures[y].tot + voitures[y].tour; // MAJ temps total
	
	printf("Voiture n°: %d \n", voitures[y].numVoiture);
	printf("Tour numéro : %d  Tours restants %d\n", i, tourRestant );
	printf("Secteur 1 : %.3fs		Secteur 2 : %.3fs		Secteur 3 : %.3fs\n", voitures[y].s1, voitures[y].s2, voitures[y].s3);
	printf("Tour : %.3f\nTotal : %.3fs\n\n", voitures[y].tour, voitures[y].tot);
}
tourRestant = tourRestant -1;
}

int z;
for( z=0 ; z<20 ; z++){
	
	printf("N° voiture : %d   ", voitures[z].numVoiture);
	printf("meilleurS1 : %.3f   meilleurS2 : %.3f  meilleurS3 : %.3f  ", voitures[z].meilleurS1, voitures[z].meilleurS2, voitures[z].meilleurS3);
	printf("temps tot : %.3f\n", voitures[z].tot);
	if(voitures[z].crash == 1)
	{
		printf("CRASHEEEEEEEEEEEEEE !!!!!!!!!!!\n");
	}
	printf("pit voitures :%d\n", voitures[z].pit);
	if(voitures[z].pit == 1 || voitures[z].pit == 2)
	{
		printf("PASSER AU PIT !!!!!!!!!!\n");
	}


	g.bestGlobalS1 = min( g.bestGlobalS1, voitures[z].meilleurS1);
	g.bestGlobalS2 = min( g.bestGlobalS2, voitures[z].meilleurS2);
	g.bestGlobalS3 = min( g.bestGlobalS3, voitures[z].meilleurS3);
	
}
	printf("Meilleur S1 Global : %.3f\n", g.bestGlobalS1);
	printf("Meilleur S2 Global : %.3f\n", g.bestGlobalS2);
	printf("Meilleur S3 Global : %.3f\n", g.bestGlobalS3);


}

