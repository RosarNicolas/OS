#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/* Méthode de génération d'un nombre aléatoire. */
int  myRand(int a, int b)
{
	int x = b - a;
	return rand()%x + a;
}

/* Méthode d'initialisation des paramètres de base
 * d'une voiture. */
void init( voiture *voit )
{
	voit->s1 = 0.0;
	voit->s2 = 0.0;
	voit->s3 = 0.0;
	voit->meilleurS1 = 50000.0;
	voit->meilleurS2 = 50000.0;
	voit->meilleurS3 = 50000.0;
	voit->tourRestant = 0;
	voit->pit = 0;
	voit->crash = 0;
	voit->tour = 0.0;
	voit->tot = 0.0;
	voit->meilleurTour = 1000.0;
}

/* Méthode de comparaison de temps pour déterminer
 * les meilleurs temps. */
double min( double a, double b )
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

double max( double a, double b )
{
	if(a<b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

/* Méthode qui efface stdout et enclenche
 * l'attente d'une entrée de la part de 
 * l'utilisateur pour continuer. */
void viderBuffer()
{
	system("clear");
	int c = 0;
	while(c!='\n' && c!= EOF)
	{
		c = getchar();
	}
}

/* Méthode qui ne fait QUE vider le buffer. */
void queViderBuffer()
{
	int c = 0;
	while(c!='\n' && c!= EOF)
	{
		c = getchar();
	}
}

void affichage1(  voiture *pointeurMPartagee, voiture *X, gp *pointeurGP, int *numEssai1, int *numEssai2, int *numEssai3 )
{
	int s1;// position dans le tableau du meilleur temps
	int s2;
	int s3;
	double meilleurS1 = 60.0;
	double meilleurS2 = 60.0;
	double meilleurS3 = 60.0;
	int z;

	for( z=0 ; z < 20 ; z++)
	{ 
		if( meilleurS1 > X[z].meilleurS1 )
		{	
			s1 = z;
			meilleurS1 = X[z].meilleurS1;
		}
		if( meilleurS2 > X[z].meilleurS2)
		{
			s2 = z;
			meilleurS2 = X[z].meilleurS2;
		}
		if ( meilleurS3 > X[z].meilleurS3 )
		{
			s3 = z;
			meilleurS3 = X[z].meilleurS3;
		}
	}
	usleep(900000);
	system("clear");
	for(z=0;z<20;z++)
	{
		printf("N°: %d	S1: %.3lf  S2: %.3lf  s3:  %.3lf  tot: %.3lf", X[z].numVoiture, X[z].s1, X[z].s2, X[z].s3, X[z].tot);
		printf("  Tour: %d", X[z].tourRestant);
		printf("  meilleur tour : %.3lf", X[z].meilleurTour);
		if(X[z].pit > 0)
		{	printf("   PIT");	}
		
		if(X[z].crash == 1)
		{	printf("   OUT");	}
		if( z == s1 )
		{	printf("   Meilleur s1");}

		if( z == s2 )
		{	printf("   Meilleur s2");}

		if( z == s3 )
		{	printf("   Meilleur s3");}
		
			printf("\n");
	}
	// affichage des position selon les essais
	if(pointeurGP->essai3 == 1)
		{
			for(z=0; z<20; z++)
			{
				numEssai3[z] = X[z].numVoiture;
			}
		}
		else if(pointeurGP->essai2 == 1)
		{
			for(z=0;z<20;z++)
			{
				numEssai2[z] = X[z].numVoiture;
			}
		}
		else if(pointeurGP->essai1 == 1)
		{
			for(z=0;z<20;z++)
			{
				numEssai1[z] = X[z].numVoiture;
			}
		}
}

/* Méthode d'affichage des temps d'essai*/
void afficherEssai( int *nEssai1, int *nEssai2, int *nEssai3 )
{
	int i;
	printf("Places des voitures pour l'essai 1 :\n");
	for(i=0;i<20;i++)
	{
		printf("Place n° %d :  %d  \n",i , nEssai1[i]);
	}
	queViderBuffer();
	system("clear");
	printf("Places des voitures pour l'essai 2 :\n");
	for(i=0;i<20;i++)
	{
		printf("Place n° %d :  %d \n", i, nEssai2[i]);
	}
	queViderBuffer();
	system("clear");
	printf("Places des voitures pour l'essai 3 :\n");
	for(i=0;i<20;i++)
	{
		printf("Place n° %d :  %d \n", i, nEssai3[i]); 
	}
}


/* Affichage de la grille de départ.
 * Les 8 premières voitures sont dans le tableau X
 * Les 6 voitures suivantes sont dans le tableau q2
 * Les 6 dernières sont dans le tableau q3 */
void affichageGrille( voiture *X, gp *pointeurGP)
{
	int z;
	printf("Grille de départ!\n");
	for(z=0;z<8;z++)
	{
		printf("Voiture n° : %d\n", X[z].numVoiture);
	}
	for(z=0;z<6;z++)
	{
		printf("Voiture n° : %d\n", pointeurGP->q2[z]);
	}
	for(z=0;z<6;z++)
	{
		printf("Voiture n° : %d\n", pointeurGP->q1[z]);
	}
}


/*
 * Méthodes pour les sémaphores.
 */
/*
void wait(struct sembuf semStruct)
{	
	semStruct.sem_num = 77;
	semStruct.sem_op = -1;
	semStruct.sem_flg = 0;
}

void signal(struct sembuf semStruct)
{
	semStruct.sem_num = 77;
	semStruct.sem_op = 1;
	semStruct.sem_flg = 0;
}
*/
