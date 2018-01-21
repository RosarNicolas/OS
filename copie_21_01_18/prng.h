#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "prototypes.h"

int carSys( voiture *car, int proba, int premT, int temps)
{
srand(time(NULL));
int v;
int tourRestant = 50;
int i;
	if(car->crash == 1)
	{
		return 0;
	}
	
	if(premT == 0)
	{
		usleep(2000000);
	}
	
	usleep( ( (getpid()%5 + 1 ) *200 * temps));	
	car->s1 = (double) secteur1( car->numVoiture , car )/1000.0;	

	if( car->crash == 0)
	{
		car->meilleurS1 = min(car->meilleurS1, car->s1);
	}

	car->s2 = (double) secteur2( car->numVoiture, car )/1000.0;
	if( car->crash == 0)
	{
		car->meilleurS2 = min( car->meilleurS2, car->s2);
	}
 
	car->s3 = (double) secteur3( car->numVoiture, car )/1000.0;
		// vérification que voiture pas crashée
		if(car->crash != 1)
		{
			if(car->pit==0 && pit(proba) == 1 ){
				// ajout du temps du pit au s3
				car->s3 += (double)myRand(6000,25000)/1000.0;
				car->pit = 1;
			}
			else if(car->pit == 1 && pit(car->tourRestant) == 1 && tourRestant !=1)
			{
				car->s3 += (double)myRand(8000,25000)/1000.0; 
				car->pit = 2;
			} 
		}
	
	if( car->crash == 0)
	{
		car->meilleurS3 = min( car->meilleurS3, car->s3);
	}
	car->tour = 0.000;
	car->tour = (car->s1 + car->s2 + car->s3);
	car->tot = car->tot + car->tour;
	
	if(car->crash == 0)
	{
		car->meilleurTour = min(car->meilleurTour, car->tour);
	}

	tourRestant = tourRestant -1;

	return 0;
}
