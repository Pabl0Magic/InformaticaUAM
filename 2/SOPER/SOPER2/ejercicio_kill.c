#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Uso: %s -<señal> <pid>\n", argv[0]);
        return 1;
    }
    int signal = INT_MIN;
    pid_t pid = INT_MIN;
    for(int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            signal = atoi(argv[i] + sizeof(char));
        }
        else if (isdigit(argv[i][0])) {
            int j;
            for(j = 1; argv[i][j] != '\0' && isdigit(argv[i][j]); j++) ;
            if (argv[i][j] == '\0') {
                pid = atoi(argv[i]);
            }
        }
    }
    if (pid == INT_MIN || signal == INT_MIN) {
        fprintf(stderr, "Uso: %s -<señal> <pid>\n", argv[0]);
        return 1;
    }
    sleep(1);
    kill (pid, signal);
    return 0;
}
