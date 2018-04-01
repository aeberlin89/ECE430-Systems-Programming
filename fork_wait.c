#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child(int i, int N);

int main(int argc, char const *argv[])
{
    int i, N, dummy;
    if (argc != 2)
    {
        printf("\nPlease use one (and only one) positive integer to\nspecify the amount of children to create.\n\n");
        return -1;
    }
    if ((N = atoi(argv[1])) < 0)
    {
        printf("\nPlease use an argument greater than or equal to zero.\n\n");
        return -1;
    }
    printf("%d Children created\n", N);
    for (i = 0; i < 2; i++)
    {
        if(fork()==0)
        {
            child(i,N);
            exit(0);
        }
    }
    printf("Parent is waiting\n");
    wait(&dummy);
    wait(&dummy);
    printf("Parent is done\n");
    return 0;
}

void child(int i, int N) {
    int j;
    if (i % 2 == 0)
    {
        for (j =0; j < N; j=j+2)
        {
            printf("Child process %d: even number %d\n", i, j);
        }
    }
    else {
        for (j = 1; j < N; j=j+2)
        {
                printf("Child process %d: odd number %d\n", i, j);
        }
    }
}
