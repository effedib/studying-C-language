#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    char *feeds[] = {"https://feeds.skynews.com/feeds/rss/world.xml"};
    char *phrase = argv[1];
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[0]);
    char *vars[] = {var, NULL};

    pid_t pid = fork();
    if (pid == -1)
        error("Can't fork process");
    if (!pid)
        if (execle("/usr/bin/python3", "/usr/bin/python3", "./rssgossip.py", phrase, NULL, vars) == -1)
            error("Can't run script");
    return 0;
}