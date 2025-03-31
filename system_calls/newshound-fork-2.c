#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    char *phrase = argv[1];
    char *vars[] = {"RSS_FEED=https://feeds.skynews.com/feeds/rss/world.xml", NULL};
    FILE *f = fopen("stories.txt", "w");
    if (!f)
        error("Can't open stories.txt");

    pid_t pid = fork();
    if (pid == -1)
        error("Can't fork process");
    if (!pid)
    {
        if (dup2(fileno(f), 1) == -1)
            error("Can't redirect Standard Output");
        if (execle("/usr/bin/python3", "/usr/bin/python3", "./rssgossip.py", phrase, NULL, vars) == -1)
            error("Can't run script");
    }

    int pid_status;
    if (waitpid(pid, &pid_status, 0) == -1)
        error("Error waiting child process");

    if (WEXITSTATUS(pid_status))
        puts("Error status non-zero");

    return 0;
}