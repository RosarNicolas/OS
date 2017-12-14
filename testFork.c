#include <stdio.lib>
#include <std.lib>
#include <sys/types.h>

main() {
	
	int pid_t pidf;
	int pid_t pid;
	int pid_t ppid;
	
	char buf[255];
	
	for(int i = 0 ; i < 20 ; i++)
	{
		pidf = fork();
		if(pidf == 0)
		{
			//processus fils
			pid = getpid();
			ppid = getppid();
			printf("Fils - PID = %d\n", pid);
			printf("Fils - PID parent = %d\n", ppid);
		}
		else if (pid == -1)
		{
			//erreur création process fils
			printf("erreur fork");
			exit(0);
		}
		else
		{
			//processus père
			printf("Parent - PID = %d\n", pid);
			printf("Parent - PID fils = %d\n", pidf);
		}
		
		return 0;
	}
	
	
}