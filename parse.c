#include "shell.h"

int parse(char *buf, char **args)
{
    int cnt = 0;

    while ('\0' != *buf)
    {
        while (isspace((unsigned char)*buf))
            *buf++ = '\0';

        *args++ = buf;

        cnt++;

        while ((*buf != '\0') && (!isspace((unsigned char)*buf)))
            buf++;
    }

    *args = (char *)NULL;

    return cnt;
}
