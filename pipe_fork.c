#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *s, buf[1024];
    int fds[2];
    s = "hello world\n";
    pipe(fds);
    if (fork() == 0)
    {
        printf("child process: \n");
        write(fds[1], s, 12);
        exit(0);
    }
    read(fds[0], buf, 6);
    write(1, buf, 6);
    return 0;
}
