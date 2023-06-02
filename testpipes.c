#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int containsPipe(int numArgs, char **args)
{
    int index;

    for (index = 0; index < numArgs; index++)
        if (args[index][0] == '|')
            return index;

    return -1;
}

int main()
{
    int indice, pidFilho, fd[2], numArgs;

    char *myargs[] = {"ls", "-l", "-a", NULL};
    char **args = myargs;

    numArgs = 7;
    indice = containsPipe(numArgs, args);

    if (indice == -1)
        execvp(*args, args);

    if (indice > 0)
    {
        printf("Pipe detetado no index %d\n", indice);
        printf("Remove o simbolo do pipe. Cria um pipe. Fork(). Executa em dois processos\n");

        args[indice] = NULL;

        pipe(fd);

        pidFilho = fork();

        if (pidFilho == 0)
        {
            numArgs = indice;

            printf("cmd escreve no pipe: %s numArgs=%d\n", args[0], numArgs);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
        }
        else
        {
            args = args + indice + 1;
            numArgs = numArgs - indice - 1;

            printf("cmd leu do pipe: %s numArgs=%d\n", args[0], numArgs);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
        }

        execvp(*args, args);
    }

    return 0;
}