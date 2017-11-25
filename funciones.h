#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct bit{
    unsigned char RGB[3];
}bit;
 
typedef struct InfoCabecera{
    unsigned int size;
    int width,height;
    unsigned short int planes;
    unsigned short int bpp;
    unsigned int compression;
    unsigned int imagesize;
    int xresolution,yresolution;
    unsigned int colours;
    unsigned int impcolours;
}InfoCabecera;

typedef struct Cabecera{
    char type[2];
    unsigned int size;
    unsigned short int reserved1,reserved2;
    unsigned int offset;
}Cabecera;

bit** crearMatriz(int alto, int ancho);
 
void esBMP(FILE* archivo, Cabecera head, InfoCabecera info);
 
InfoCabecera leerInfo(FILE* archivo);
 
bit** cargarImagen(FILE* archivo, bit** Matrix, int alto, int ancho);
 