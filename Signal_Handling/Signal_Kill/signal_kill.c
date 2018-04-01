#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sighup();
void sigint();
void sigquit();

int main()
{
    int pid;

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        signal(SIGHUP, sighup); /* set function calls */
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        for(;;); /* endless loop */
    }
    else    /* parent */
    {       /* pid hold id of child */
        printf("\nPARENT: sending SIGHUP\n\n");
        sleep(3);
        kill(pid, SIGHUP);
        sleep(3);   /* pause for 3 seconds */
        printf("\nPARENT: sending SIGINT\n\n");
        kill(pid, SIGINT);
        sleep(3);   /* pause for 3 seconds */
        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(3);   /* pause for 3 seconds */
    }
}

void sighup()
{
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n");
}

void sigint()
{
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD: I have received a SIGINT\n");
}

void sigquit()
{
    printf("My DADDY has killed me!!!\n");
    exit(0);
}
