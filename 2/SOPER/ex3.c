#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char** argv)
{
	FILE *fp;
    int i;

	fp = fopen ( "a", "r" );        

	if (fp==NULL) {
        i = errno;
        printf("%d\n", errno);
        fprintf(stderr, "%s\n%i", strerror(i), i);
        perror(stderr);
        return 0;
    }

	fclose ( fp );

	return 0;
}

