#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	/*FILE *pf;*/
	pid_t pid;

	/*pf = fopen("buffer", "w");

	if (pf == NULL) {
		perror("File not open");
		exit(EXIT_FAILURE);
	}*/
	
	printf("Yo soy tu padre"); /*/n*/
	/*fprintf(pf, "Yo soy tu padre\n");
	fflush(pf);*/

	pid = fork();
	if(pid <  0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid ==  0)
	{
		printf("Noooooo");/*/n*/
		/*fprintf(pf, "Noooooo\n");*/
		exit(EXIT_SUCCESS);
	}

	wait(NULL);
	exit(EXIT_SUCCESS);
}
