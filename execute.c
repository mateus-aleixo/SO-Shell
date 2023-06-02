#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

int ultimo(int *numargs, char **args)
{
    if (args[*numargs - 1][0] == '&')
    {
        *numargs = *numargs - 1;
        args[*numargs] = NULL;

        return BG;
    }

    return FG;
}

int containsPipe(int numArgs, char **args)
{
    int index;

    for (index = 0; index < numArgs; index++)
        if (args[index][0] == '|')
            return index;

    return -1;
}

void execute(int numargs, char **args)
{
    int pid, pidFilho, status, fd[2];
    int code = ultimo(&numargs, args);

    if ((pid = fork()) < 0)
    {
        printf("Erro nos forks");
        exit(1);
    }

    if (pid == 0)
    {
        int indice = containsPipe(numargs, args);

        if (indice == -1)
        {
            redirects(numargs, args);
            execvp(*args, args);
        }

        if (indice > 0)
        {
            args[indice] = NULL;

            pipe(fd);

            pidFilho = fork();

            if (pidFilho == 0)
            {
                numargs = indice;

                redirects(numargs, args);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            else
            {
                args = args + indice + 1;
                numargs = numargs - indice - 1;

                redirects(numargs, args);
                dup2(fd[0], STDIN_FILENO);
                close(fd[1]);
                close(fd[0]);
            }

            execvp(*args, args);
        }

        execvp(*args, args);
        perror(*args);
        exit(1);
    }

    if (FG == code)
        while (wait(&status) != pid)
            ;

    return;
}
