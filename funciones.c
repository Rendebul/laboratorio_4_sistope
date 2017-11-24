#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "funciones.h"

bmp_file* leerArchivo(char *archivo) {
    printf("Archivo a leer: %s\n", archivo);
    header head;
    unsigned char *bitmapImage;

    FILE *file = fopen(archivo, "rb");

    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        abort();
    }

    fread(&head, sizeof(header),1,file);

    fseek(file, head.bfOffBits, SEEK_SET);

    bitmapImage = (unsigned char*)malloc(head->biSizeImage);

    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(file);
        printf("Error al asignar memoria\n");
        abort();
    }

    fread(bitmapImage,head->biSizeImage,file);
    fclose(file);
    
    bitmapImage = swapper(bitmapImage, head->biSizeImage);
    
    bit** matriz = ToBit(bitmapImage, head->biXPelsPerMeter, head->biYPelsPerMeter);

    bmp_file* datos = {head, matriz};
    return datos;
}

unsigned char* swapper(unsigned char *bitmap,LONG size) {
    int imageIdx=0;
    unsigned char tempRGB;
    for (imageIdx = 0;imageIdx < size;imageIdx+=3) // fixed semicolon
    {
        tempRGB = bitmap[imageIdx];
        bitmap[imageIdx] = bitmap[imageIdx + 2];
        bitmap[imageIdx + 2] = tempRGB;
    }

    return bitmap;
}

bit** ToBit(unsigned char *bitmap, LONG x, LONG y) {
    int i, j, contador;
    bit ** matriz = crearMatriz(x,y);
    for (i = 0; i < y; ++i)
    {
        for (j = 0; j < x; ++j)
        {
            bit b = {(int)bitmap[contador],(int)bitmap[contador+1],(int)bitmap[contador+2]};
            matriz[i][j] = b;
            contador+=3;
        }
    }

    return matriz;
}

bit ** crearMatriz(LONG i, LONG j){
    bit ** matriz = (bit**)malloc(sizeof(bit*)*i);
    if(!matriz) {
        printf("Error al asignar memoria\n");
        exit(-1);
    }
    int aux;
    for (aux = 0; aux < i; ++aux)
    {
        matriz[aux] = (bit*)malloc(sizeof(bit)*j);
        if(!matriz[aux]) {
            printf("Error al asignar memoria\n");
            exit(-1);
        }
    }
    return matriz;
};
