#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin(char **args, int numargs);

void socp(char *fonte, char *destino);

void ioCopy(int IN, int OUT);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpeg(int fileDescriptor);

int redirects(int numargs, char *args[]);

void aviso(char *mesg, int tempo);

void *avisowrapper(void *args);

void *socpwrapper(void *args);

long int findSize(char file_name[]);

void maior(char f1[], char f2[]);

void setx(char filename[]);

void removerl(char filename[]);

void sols(char *pasta);

typedef struct
{
    char msg[100];
    int tempo;
} aviso_t;

typedef struct
{
    char fonte[100];
    char destino[100];
} copiar_t;

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
