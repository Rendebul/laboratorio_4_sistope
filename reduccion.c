#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "funciones.h"
#include <pthread.h>

int main(int argc, char **argv)
{
  //Se declaran variables
  int num_pix, num_iteracion, opcion = 0;
  bool mostrar = false;
  char *nombre_salida1;
  char *nombre_salida2;
  char *archivo;
  int c;

  opterr = 0;

    //Se capta el getopt correspondiente al coordinador.
  while ((c = getopt (argc, argv, "n:m:s:g:i:o:d::")) != -1)
    switch (c) {
        case 'n':
                    num_iteracion = atoi(optarg);
                    break;
        case 'm':
                    num_pix = atoi(optarg);
                    break;
        case 'd':   
                    mostrar = true;
                    break;
        case 's':
                    nombre_salida1 = optarg;
                    break;
        case 'g':
                    nombre_salida2 = optarg;
                    break;
        case 'i':
                    archivo = optarg;
                    break;
        case 'o':
                    opcion = atoi(optarg);
                    break;
        case '?':
                    if (optopt == 'm' || optopt == 'n' || optopt == 'i' || optopt == 'g' || optopt == 's')
                        fprintf (stderr, "La opcion -%c requires un argumento.\n", optopt);
                    else if (isprint (optopt))
                        fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
                    else
                        fprintf (stderr,"Caracter desconocido `\\x%x'.\n",optopt);
                    return 1;
        default:
                abort ();
  }
  printf (" n = %d, m = %d, o= %d, d = %d, s= %s, g= %s, i= %s\n", num_iteracion, num_pix, opcion, mostrar, nombre_salida1, nombre_salida2, archivo);
  
  if(num_pix < 1){
    printf("Tamaño incorrecto para la reduccion de pixeles \n");
    abort();
  }
  if(num_iteracion < 1){
    printf("Tamaño incorrecto de iteraciones para inicializar\n");
    abort();
  }
  if(opcion > 4 || opcion < 1) {
    printf("Opcion fuera de rango\n");
    abort();
  }

  int alto, ancho;
  Cabecera head;
  FILE* file = fopen(archivo, "rb");
  bit** Matrix_aux;
  InfoCabecera info;
  info = leerInfo(file);
  esBMP(file,head,info);
  alto = info.height;
  ancho = info.width;
   
  Matrix_aux = crearMatriz(alto, ancho);
  bit** Matrix = cargarImagen(file,Matrix_aux, alto, ancho);

  
  printf("Sali\n");
  return 0;
}