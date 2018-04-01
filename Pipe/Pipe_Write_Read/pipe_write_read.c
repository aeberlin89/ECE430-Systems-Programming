#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
    char *s, buf[1024];

    int fds[2];
    s = "hello world\n";
    pipe(fds);
    write(fds[1], s, strlen(s));
    read(fds[0], buf, strlen(s));
    write(1, buf, strlen(s));
    return 0;
}
