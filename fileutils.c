#include "shell.h"
#include <stdio.h>
#include <dirent.h>

long int findSize(char file_name[])
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Ficheiro não encontrado\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    long int res = ftell(fp);

    fclose(fp);

    return res;
}

void maior(char f1[], char f2[])
{
    long int sizef1 = findSize(f1);
    long int sizef2 = findSize(f2);

    if (sizef1 < sizef2)
        printf("Nome: %s | Tamanho: %fKB\n", f2, sizef2 * 0.001);
    else if (sizef1 > sizef2)
        printf("Nome: %s | Tamanho: %fKB\n", f1, sizef1 * 0.001);
    else
    {
        printf("Nome: %s | Tamanho: %fKB\n", f2, sizef2 * 0.001);
        printf("Nome: %s | Tamanho: %fKB\n", f1, sizef1 * 0.001);
    }
}

void setx(char filename[])
{
    char command[50] = "chmod u=rxw ";

    strcat(command, filename);
    system(command);
}

void removerl(char filename[])
{
    char command[50] = "chmod go-r ";

    strcat(command, filename);
    system(command);
}

void getFileCreationTime(char *path)
{
    struct stat attr;

    stat(path, &attr);
    printf("%s", ctime(&attr.st_mtime));
}

void sols(char *pasta)
{
    if (pasta == NULL)
        pasta = ".";

    DIR *d;

    struct dirent *dir;

    d = opendir(pasta);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%15s %i ", dir->d_name, dir->d_reclen);
            getFileCreationTime(pasta);
        }

        closedir(d);
    }
}