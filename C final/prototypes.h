#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

/* Méthode générant un nombre aléatoire sur base
 * duquel est déterminé le fait qu'elle soit crashée
 * ou non. */
int crash( int a)
{
	srand(time(NULL) * a); 
	return myRand(0,1200);
}

/* Méthodes de génération d'un temps de voiture
 * pour le secteur 1, 2 et 3 (3 méthodes différentes).
 * Une voiture est passée en paramètre
 * ainsi qu'un entier utilisé pour modifier la seed
 * utilisée dans le "srand" de la méthode "crash( int a )". */
double secteur1( int a,  voiture *voit)
{	
	if(crash(a) == 1 && voit->crash == 0)
	{
		voit->crash = 1;
	}
	if( voit->crash == 1 )
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a);
		return myRand(25000,35000); //min 25
	}
}
// infos au-dessus de la méthode secteur 1.
double secteur2( int a, voiture *voit)
{
	if(crash((a*3)+1) == 1 && voit->crash == 0)
	{
		voit->crash = 1;
	}
	if(voit->crash == 1)
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a + rand()%10);
		return myRand(30000,35000); //min 30
	}

}
// infos au-dessus de la méthode secteur 1.
double secteur3( int a,  voiture *voit )
{
	if(crash(a*2) == 1 && voit->crash == 0)
	{
		voit->crash = 1;
	}
	if(voit->crash == 1)
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a  + rand()%20);
		return myRand(35000,40000); //min 35
	}	
}

/* Méthode de tri pour les qualif.
 * Méthode recevant un tableau en paramètre qui sera trié pour
 * récupérer les n° de voitures dans l'ordre des meilleurs temps par tour.
 * Retourne un pointeur. */
voiture* triageQualif( voiture tab[])
{
	voiture t[ sizeof(voiture)*20 ] ;
	voiture *pointeur = t;
	int num;
	int i;
	int z;
	voiture courante;
	int position = 19;
	int count;
	for(z=0;z<20;z++, position--)
	{
	count = z;
	courante = tab[z];
	for(i=0;i<20;i++)
	{
		if(courante.meilleurTour != max(courante.meilleurTour, tab[i].meilleurTour) )
		{
			courante = tab[i];
			count = i;
		}
	}
	tab[count].meilleurTour = 0.0;
	t[position] = courante;
	}
	return pointeur;
}
/* Méthode de triage pour la course
 * Trier d'abord sur le nombre de tour restans
 * et ensuite sur le temps total si leur nombre de tour
 * restants sont égaux. */
voiture* triageCourse( voiture tab[] )
{
	voiture t[sizeof(voiture)*20];
	voiture *pointeur = t;
	int i;
	int z;
	int count;
	int position = 0;
	voiture courante;
	for(z=0;z<20;z++,position++)
	{
	count = z;
	courante = tab[z];
	for(i=0;i<20;i++)
	{
		if(courante.numVoiture != tab[i].numVoiture)
		{
			if(courante.tourRestant < tab[i].tourRestant)
			{
				courante = tab[i];
				count = i;
			}
			else if(courante.tourRestant == tab[i].tourRestant)
			{
				if(courante.tot < tab[i].tot)
				{
					courante = tab[i];
					count = i;
				}
				else{}
			}
		}
	}
	tab[count].tourRestant = 0;
	tab[count].tot = 0.0;
	t[position] = courante;
	}
	return pointeur;
}


/* Méthode générant un nombre (0 ou 1) à partir duquel
 * sera déterminé le fait qu'une voiture passe ou non au
 * pit.*/
int pit( double proba )
{
	srand(time(NULL));
	int x = round(proba + 0.5);
	int y = rand()%x;
	if(y==1){return 1;}
	else {return 0;}
}
