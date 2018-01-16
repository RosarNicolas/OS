#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myRand.h"

double min( double a, double b)
{
	if( a  > b){ 	return b; }
	else{	return a; }
}

int crash( int a)
{
	srand(time(NULL) * a); 
	return myRand(0,1200);
}

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
		return myRand(25000,35000); //entre 0 et 11 +25 (pr avoir au min 25)
	}
}

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

voiture* triageQualif( voiture tab[] )
{
	voiture t[ sizeof(voiture)*20 ] ;
	voiture *pointeur = t;
	double meilleurT = 1000.0;
	int num;
	int i;
	int z;

	for(i=0; i<20 ; i++)
	{	
		meilleurT = tab[i].meilleurTour;
		for( z = 0 ; z < 20 ; z++)
		{
			if( tab[z].meilleurTour < meilleurT ){
				num = z;
				meilleurT = tab[z].meilleurTour;
			}
		}
		t[i] = tab[num];
		tab[num].meilleurTour = 1100.0;
	}
	return pointeur;
}
/*
voiture[] triageCourse()
{

}
*/
int pit( double proba )
{
	srand(time(NULL));
	int x = round(proba + 0.5);
	int y = rand()%x;
	if(y==1){return 1;}
	else {return 0;}
}
