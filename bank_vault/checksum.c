#include <checksum.h>

int checksum(char *message)
{
    int c;
    while (*message)
    {
        c += c ^ (int)*message;
        message++;
    }

    return c;
}