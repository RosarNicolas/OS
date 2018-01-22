// structure représentant un voiture
typedef struct 
{
	//int pid;
	int numVoiture;
	double s1;
	double meilleurS1;
	double s2;
	double meilleurS2;
	double s3;
	double meilleurS3;
	double tour;
	double tot;
	int crash;
	int pit;
	int tourRestant;
	double meilleurTour;
	int course;
	int q2;
	int q3;
}voiture;

// structure pour les différentes parties de la course
typedef struct
{	
	int q1[6];// contiendra les voitures ne participant pas à la 2ème qualif
	int q2[6];// ne participant pas à la 3ème qualif
	int course;
	int essai1;
	int essai2;
	int essai3;
	int qualif1;
	int qualif2;
	int qualif3;
}gp;


