#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLE 100

//Estructura de datos de intersecciones
typedef struct {
	char calle1[MAX_CALLE];
	char calle2[MAX_CALLE];
	int  trafico;
} Interseccion;

//Prototipos de Funcion
void ingresarDatos(void);
void verHistorial(void);
void buscarCalle(void);
void limpiarBuffer(void);
void imprimirLinea(char c, int n);

int main(){
	char opcion[4];   //Cadena para leer la opción del menú
	
	do {
		//Menu
		printf("   SISTEMA DE TRAFICO - INTERSECCIONES\n");
		printf("  [1] Ingresar datos\n");
		printf("  [2] Ver historial\n");
		printf("  [3] Buscar calle\n");
		printf("  [4] Salir\n");
		printf("  Opcion: ");
		fgets(opcion, sizeof(opcion), stdin);
		opcion[strcspn(opcion, "\n")] = '\0';   /* eliminar '\n' */
		
		if (strcmp(opcion, "1") == 0)      ingresarDatos();
		else if (strcmp(opcion, "2") == 0) verHistorial();
		else if (strcmp(opcion, "3") == 0) buscarCalle();
		else if (strcmp(opcion, "4") == 0) printf("\n  Hasta luego!\n\n");
		else                               printf("\n  Opcion invalida.\n\n");
		
	} while (strcmp(opcion, "4") != 0);
	
	free(historial);   /* liberar memoria antes de salir */
	return 0;
}

