#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>



typedef struct bit
{
    int r;
    int g;
    int b;
} bit;

typedef struct bmp_file
{
    header head;
    bit** bits;
} bmp_file;

bmp_file* leerArchivo(char *archivo);
bit ** crearMatriz(LONG i, LONG j);
bit ** ToBit(unsigned char *bitmap, LONG x, LONG y);
unsigned char* swapper(unsigned char *bitmap,LONG size);
