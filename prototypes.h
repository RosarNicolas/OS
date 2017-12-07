#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "myRand.h"

double min( double a, double b)
{
	if( a  > b){ 	return b; }
	else{	return a; }
}

int crash( int a, int b)
{
	srand(time(NULL) * a * b); 
	return myRand(0,1200);
}

double secteur1( int a, int b, voiture * voit)
{
	if(crash(a,b) == 1 && voit->crash == 0)
	{
		printf("Crash S1\n");
		voit->crash = 1;
	}
	if( voit->crash == 1 )
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a * b);
		return myRand(25000,35000); //entre 0 et 11 +25 (pr avoir au min 25)
	}
}

double secteur2( int a, int b, voiture * voit)
{
	if(crash((a*3)+1, b) == 1 && voit->crash == 0)
	{
		printf("Crash S2\n");
		voit->crash = 1;
	}
	if(voit->crash == 1)
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a * b + rand()%10);
		return myRand(30000,35000); //min 30
	}

}

double secteur3( int a, int b, voiture * voit )
{
	if(crash((a*2),b) == 1 && voit->crash == 0)
	{
		voit->crash = 1;
		printf("Crash S3\n");
	}
	if(voit->crash == 1)
	{
		return 0.0;
	}
	else
	{
		srand(time(NULL) * a * b + rand()%20);
		return myRand(35000,40000); //min 35
	}	
}

int pit( double proba )
{
	srand(time(NULL));
	int x = round(proba + 0.5);
	int y = rand()%x;
	if(y==1){return 1;}
	else {return 0;}
}
