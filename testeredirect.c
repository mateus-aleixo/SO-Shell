#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

int main(void)
{
    int fd;
    char nome[] = "mateus";
    char *args[2];

    args[0] = nome;
    args[1] = NULL;
    fd = open("input.txt", O_RDONLY);

    if (fd < 0)
    {
        printf("Erro no open");

        return (1);
    }

    dup2(fd, STDIN_FILENO);
    close(fd);

    fd = creat("output.txt", FILE_MODE);

    if (fd < 0)
    {
        printf("Erro no creat");

        return (1);
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);
    execvp(nome, args);

    return (0);
}