#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "funciones.h"

bit** crearMatriz(int alto, int ancho){
    bit** Matrix;
    int i;
    Matrix = (bit **) malloc (sizeof (bit*) * alto);
    if (Matrix == NULL){
        perror("***** No memory available *****");
        exit(0);
    }
    for (i=0;i<alto;i++){
        Matrix[i] = (bit *) malloc (sizeof(bit) * ancho);
        if (Matrix[i] == NULL){
        perror("***** No memory available *****");
            exit(0);
        }
    }
    return(Matrix);
}
 
// ********** Verify if the file is BMP *********
void esBMP(FILE* archivo, Cabecera head, InfoCabecera info){
    char type[3];
    unsigned short int bpp;
    fseek(archivo,0,0);
    fread(type,1,2,archivo);
    type[2] = '\0';
 
    fseek(archivo,28,0);
    fread(&bpp,1,2,archivo);
 
    if (strcmp(type,"BM") || (bpp != 24)){
        printf("\nThe file is not BMP format or is not 24 bits\n");
            exit(0);
    }
}
 
// ********** Read BMP info from file **********
InfoCabecera leerInfo(FILE* archivo){
    InfoCabecera info;
 
    // Image Width in pixels
    fseek(archivo,18,0);
    fread(&info.width,1,4,archivo);
 
    // Image Height in pixels
    fseek(archivo,22,0);
    fread(&info.height,1,4,archivo);
 
    // Color depth, BPP (bits per pixel)
    fseek(archivo,28,0);
    fread(&info.bpp,1,2,archivo);
 
    // Compression type
    // 0 = Normmally
    // 1 = 8 bits per pixel
    // 2 = 4 bits per pixel
    fseek(archivo,30,0);
    fread(&info.compression,1,4,archivo);
 
    // Image size in bytes
    fseek(archivo,34,0);
    fread(&info.imagesize,1,4,archivo);
 
    // Number of color used (NCL)
    // value = 0 for full color set
    fseek(archivo,46,0);
    fread(&info.colours,1,4,archivo);
 
    // Number of important color (NIC)
    // value = 0 means all collors important
    fseek(archivo,50,0);
    fread(&info.impcolours,1,4,archivo);
 
    return(info);
}
 
bit** cargarImagen(FILE* archivo, bit** Matrix, int alto, int ancho){
    int i,j;
    bit tmp;
    long pos = 51;
 
    fseek(archivo,0,0);
 
    for (i=0; i<alto; i++){
        for (j=0; j<ancho; j++){
            pos+= 3;
            fseek(archivo,pos,0);
            fread(&tmp,(sizeof(bit)),1,archivo);
            Matrix[i][j] = tmp;
        }
    }
    return(Matrix);
}
 