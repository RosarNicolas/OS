#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// 0) Structure
// 0.1) Methodes
// 1) Methodes GENERATION DES TEMPS : secteur
// 2) Methodes GENERATION DU TEMP : PIT
// 3) MAIN
// 4) CREATION D UNE "voiture"
// 5) GENERATION DES TEMPS

// 0) STRUCTURE
typedef struct{
	int pid;
	int numVoiture;
	double s1;
	double s2;
	double s3;
	double tour;
	double tot;
	int crash;
	int pit;
	int tourRestant;
}voiture;

// 0.1) METHODES

double min(double a, double b)
{
	if(a>b)
	{
		return b;
	}
	else 
	{
		return a;
	}
}	

// crash à une chance sur 200    aléatoire
int crash(int a)
{	
	
	srand(time(NULL) * a);
	return rand()%1200;

}

// 1) METHODES GENERATION DES TEMPS  :  SECTEURS
int secteur1(int a, voiture *pointeur )
{	
	if(crash(a) == 1 && pointeur->crash == 0)
	{
		printf("Crash s1\n");
		pointeur->crash = 1;
	}
	if( pointeur->crash == 1)
	{ 
		
		return 0.0;
		
	}
	else
	{
		srand(time(NULL) * a);
		return (rand()%11000 + 25000); // entre 0 et 11 + 25 (pr avoir au min 25)
	}	
}
int secteur2(int a, voiture *pointeur )
{	
	if( crash((a * 3) +1) == 1 && pointeur->crash == 0)
	{	
		printf("Crash s2\n");
		 pointeur->crash = 1;
		
	}
	if( pointeur->crash == 1 )
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a + rand()%10 );
		return (rand()%6000 + 30000);  // min 30
	}
}
int secteur3(int a, voiture *pointeur )
{		
	if( crash(a * 2) == 1 && pointeur->crash == 0)
	{
		pointeur->crash = 1;
		printf("Crash s3\n");
	}
	if( pointeur->crash == 1)
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a + rand()%20 );
		return (rand()%6000 + 35000);   // min 35
	}
}

// 2) METHODES GENERATION DU TEMP  :  PIT  
int pit(int nbrTourRestant)
{
	srand(time(NULL));
	int y = rand()%nbrTourRestant;
	if( y == 1)
	{
		return 1;
	}
	else
	{
		return 0.0;
	}
}

// 3) MAIN
int main()
{
int v;
int proba;
// déclaration du tableau avec toutes les voitures
voiture voitures[20] ;// {44, 77, 3, 33, 5, 7, 11, 31, 19, 18, 14, 2, 10, 55, 8, 20, 27, 30, 9, 94};	
for( v = 0; v< sizeof(voitures) / sizeof(voitures[0]); v++)
{	
// 4) CREATION D'UNE "voiture"
 // mémoire allouée en même temps que création de la struct voiture a
// assignation des valeurs par défaut
	voitures[v].numVoiture = 1;
	voitures[v].s1 = 0.0;
	voitures[v].s2 = 0.0;
	voitures[v].s3 = 0.0;
	voitures[v].tour = 0.0; 
	voitures[v].tot = 0.0;
	voitures[v].crash = 0; // 1 crashé    0 Ok
	voitures[v].pit =0;
	voitures[v].tourRestant = 50;
}


int meilleurVoitS1;
double meilleurS1 = 500000;
int meilleurVoitS2;
double meilleurS2 = 500000;
int meilleurVoitS3;
double meilleurS3 = 500000;


// 5) GENERATION DES TEMPS
// boucle d'ajout des des valeurs   :  ADD s1, s2, s3, tour, total
// désincrémentation de tourRestant :  tourRestant --

// BOUCLE GLOBALE
int y;
int i;
for( y = 0 ; y< sizeof(voitures) / sizeof(voitures[0]) ; y++){
voiture a = voitures[y];
printf("%d\n", y);
for( proba = a.tourRestant / 2, i = 1 ; i < 2 ; i++, proba--)
{	
	
	a.tour = 0; // mise à 0 de tour
	a.s1 = (double) secteur1( i, &a )/1000.0;	
	if(a.crash == 0)
	{
		meilleurS1 = min(a.s1,meilleurS1);
	}
	a.tour = a.tour + a.s1;

	a.s2 = (double) secteur2( i, &a )/1000.0;
	if(a.crash == 0)
	{
		meilleurS2 = min(a.s2,meilleurS2);
	}
	a.tour = a.tour + a.s2;
 
	a.s3 = (double) secteur3( i, &a )/1000.0;
	
	/**	// vérifié que voiture pas crashé
		if(a.crash != 1){
			if(a.pit==0 && pit(proba) == 1 ){  // SI a.pit = 0    ET    pit(.....) est égal à 1 ALORS ==> ajoute temp pit
				srand(time(NULL)); 
				a.s3 += (double)(rand()%6000 + 25000)/1000.0; // %6 car temps au pit stop entre 25 et 30 secondes
				printf("Je suis passé au pit première fois au tour : %d\n", ( i ) );
				a.pit = 1;
			}
		
			else if(a.pit == 1 && pit(a.tourRestant) == 1 && a.tourRestant != 1 ){
				srand(time(NULL));
				a.s3 += (double)(rand()%8000 + 25000)/1000.0;
				printf("Je suis passé au pit pour la 2eme fois\n"); 
				a.pit = 2;
			} 
		}
	**/
	if(a.crash == 0)
	{
		meilleurS3 = min(a.s3,meilleurS3);
	}
	a.tourRestant --;
	a.tour = a.tour + a.s3;
	// Mise à jour du temps total
	a.tot = a.tot + a.tour;


	printf("Tour numéro : %d	Tour Restant : %d\n", i, a.tourRestant);
	printf("Secteur 1 : %.3fs		Secteur 2 : %.3fs		Secteur 3 : %.3fs\nTour : %.3fs\nTotal : %.3fs\n\n", a.s1, a.s2, a.s3, a.tour, a.tot);
printf("meilleur temps s1 : %.3f\nmeilleur temps s2 : %.3f\nmeilleur temps s3 : %.3f\n",meilleurS1, meilleurS2, meilleurS3);
}
}
}