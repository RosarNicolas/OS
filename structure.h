typedef struct 
{
	int pid;
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
}voiture;


typedef struct 
{
	double bestGlobalS1;
	double bestGlobalS2;
	double bestGlobalS3;
	int bestVoitS1;
	int bestVoitS2;
	int bestVoitS3;
	
	double bestTotal;
	int bestVoitTotal;
}global;
