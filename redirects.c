#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

int redirects(int numargs, char *args[])
{
    if (numargs < 3)
        return numargs;

    if (strcmp(args[numargs - 2], "2>") == 0)
    {
        int fd = creat(args[numargs - 1], FILE_MODE);

        if (fd < 0)
        {
            printf("Erro ao criar");

            return -1;
        }

        dup2(fd, STDERR_FILENO);

        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    if (numargs < 3)
        return numargs;

    if (strcmp(args[numargs - 2], ">") == 0) // SAIDA
    {
        int fd1 = creat(args[numargs - 1], FILE_MODE);

        if (fd1 < 0)
        {
            printf("Erro ao criar");

            return -1;
        }

        dup2(fd1, STDOUT_FILENO);
        close(fd1);

        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    else
    {
        if (strcmp(args[numargs - 2], ">>") == 0)
        {
            int fd2 = creat(args[numargs - 1], O_WRONLY | O_APPEND);

            if (fd2 < 0)
            {
                printf("Erro ao criar");

                return -1;
            }

            dup2(fd2, STDOUT_FILENO);
            close(fd2);

            args[numargs - 2] = NULL;
            numargs = numargs - 2;
        }
    }

    if (numargs < 3)
        return numargs;

    if (strcmp(args[numargs - 2], "<") == 0) // ENTRADA
    {
        int fd3 = open(args[numargs - 1], O_RDONLY);

        if (fd3 < 0)
        {
            printf("Erro ao abrir");

            return -1;
        }

        dup2(fd3, STDIN_FILENO);
        close(fd3);

        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    return numargs;
}