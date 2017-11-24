# Esta es la target que se ejecuta por defecto si se escribe "make" en la consola
all: dev

# Compilación principal del ejecutable
dev:
	@echo 'Compilando'
	gcc reduccion.c funciones.c -o reduccion -lm
	@echo "Ejecute el programa haciendo: ./reduccion -i archivo -s salida1 -g salida2 -n Ni -m Mi -o O -d"
	@echo "Donde  archivo: nombre del archivo junto a su extension. Ej: ejemplo1.txt"
	@echo "		  salida1: nombre del archivo de salida para el metodo 1."
	@echo "		  salida2: nombre del archivo de salida para el metodo 2."
	@echo "       Ni: Numero de veces de la reduccion."
	@echo "       Mi: Numero de pixeles a reducir."
	@echo "       O: Método al cual desea llamar:."
	@echo "              1 Método 1"
	@echo "              2 Método 1"
	@echo "              3 Ambos Métodos"
	@echo "       -d: (opcional) Si desea resultado por pantallas."
	