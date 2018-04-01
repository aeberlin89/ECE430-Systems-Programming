#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define P1_READ 0
#define P2_WRITE 1
#define P2_READ 2
#define P1_WRITE 3

// the total number of pipe *pairs* we need
#define NUM_PIPES 2

int main(int argc, char *argv[])
{
    int fd[2*NUM_PIPES];
    int val = 0, len, i;
    pid_t pid;

    // create all the descriptor pairs we need
    for (i=0; i<NUM_PIPES; ++i)
    {
        if (pipe(fd+(i*2)) < 0)
        {
            perror("Failed to allocate pipes");
            exit(0);
        }
    }

    // fork() returns 0 for child process, child-pid for parent process.
    if ((pid = fork()) < 0)
    {
        perror("Failed to fork process");
        return 0;
    }

    // if the pid is zero, this is the child process
    if (pid == 0)
    {
        // Child. Start by closing descriptors we don't need in this process
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);

        pid = getpid();

        // wait for parent to send us a value
        len = read(fd[P2_READ], &val, sizeof(val));
        if (len < 0)
        {
            perror("Child: Failed to read data from pipe");
            exit(0);
        }
        else if (len == 0)
        fprintf(stderr, "Child: Read EOF from pipe");
        else
        {
            printf("Child(%d): Received %d\n", pid, val);

            //now double it and send it back
            val *= 5;

            printf("Child(%d): Sending %d back\n", pid, val);
            write(fd[P2_WRITE], &val, sizeof(val));
        }
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);

        return 0;
    }

    // Parent. Close unneeded descriptors
    close(fd[P2_READ]);
    close(fd[P2_WRITE]);

    // used for output
    pid = getpid();

    // send value to the child
    val = 100;
    printf("Parent(%d): Sending %d to child\n", pid, val);
    write(fd[P1_WRITE], &val, sizeof(val));

    len = read(fd[P1_READ], &val, sizeof(val));
    if (len < 0)
    {
        perror("Parent: failed to read value from pipe");
        exit(0);
    }
    else if(len == 0)
        fprintf(stderr, "Parent(%d): Read EOF from pipe", pid);
    else
        printf("Parent(%d): Received %d\n", pid, val);

    // close down remaining descriptors
    close(fd[P1_READ]);
    close(fd[P1_WRITE]);

    // wait for child termination
    wait(NULL);
    return 0;
}
