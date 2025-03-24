#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

/* execl() = list of args.
 * execle() = list of args + environment.
 * execlp() = list of args + search on path.
 * execv() = array of args.
 * execve() = array of args + environment.
 * execvp() = array of args + search on path. */

int main(int argc, char *argv[])
{
    char *feeds[] = {"http://www.cnn.com/rss/celebs.xml",
                     "http://www.rollingstone.com/rock.xml",
                     "http://eonline.com/gossip.xml"};
    int times = 3;
    char *phrase = argv[1];
    int i;
    for (i = 0; i < times; i++)
    {
        char var[255];
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid_t pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
            return 1;
        }
        if (!pid)
            if (execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py", phrase, NULL, vars) == -1)
            {
                fprintf(stderr, "Can't run script: %s\n", strerror(errno));
                return 1;
            }
    }
    return 0;
}