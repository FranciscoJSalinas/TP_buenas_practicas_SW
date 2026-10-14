#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLE 100

//Variables globales
Interseccion *historial = NULL;   //arreglo dinámico de intersecciones
int cantidad = 0;                 //cantidad de registros ingresados


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
//Ingreso de Calles y Trafico
void ingresarDatos(void) {
	char continuar[4];
	char buffer[16];
	
	do {
		printf("\n");
		printf("  NUEVO REGISTRO #%d\n", cantidad + 1);
		
		/* Reservar (o ampliar) memoria para un registro más */
		Interseccion *tmp = (Interseccion *)realloc(historial, (cantidad + 1) * sizeof(Interseccion));
		
		if (tmp == NULL){
			printf("  Error: no se pudo asignar memoria.\n");
			return;
		}
		historial = tmp;
		
		/* Puntero al nuevo registro */
		Interseccion *reg = historial + cantidad;
		
		printf("  Calle 1: ");
		fgets(reg->calle1, MAX_CALLE, stdin);
		reg->calle1[strcspn(reg->calle1, "\n")] = '\0';
		
		printf("  Calle 2: ");
		fgets(reg->calle2, MAX_CALLE, stdin);
		reg->calle2[strcspn(reg->calle2, "\n")] = '\0';
		
		printf("  Trafico (vehiculos/hora): ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		reg->trafico = atoi(buffer);
		
		cantidad++;
		printf("  Registro guardado correctamente.\n");
		
		printf("\n  Desea ingresar otro registro? (s/n): ");
		fgets(continuar, sizeof(continuar), stdin);
		continuar[strcspn(continuar, "\n")] = '\0';
		
	} while (strcmp(continuar, "s") == 0 || strcmp(continuar, "S") == 0);
}

//Historial de Datos
void verHistorial(void) {
	printf("\n");
	printf("  HISTORIAL DE INTERSECCIONES (%d)\n", cantidad);
	
	if (cantidad == 0) {
		printf("  No hay registros ingresados.\n\n");
		return;
	}
	
	int i;
	for (i = 0; i < cantidad; i++) {
		Interseccion *reg = historial + i;
		printf("  #%-3d Calle 1 : %s\n",  i + 1, reg->calle1);
		printf("       Calle 2 : %s\n",          reg->calle2);
		printf("       Trafico : %d veh/h\n",     reg->trafico);
	}
	printf("\n");
}
//Funcion que busca en el historial los datos ingresados
void buscarCalle(void) {
	char busqueda[MAX_CALLE];
	int  encontrado = 0;
	int  i;
	
	printf("\n");
	printf("  BUSCAR CALLE\n");
	
	if (cantidad == 0) {
		printf("  No hay registros para buscar.\n\n");
		return;
	}
	
	printf("  Ingrese el nombre de la calle: ");
	fgets(busqueda, MAX_CALLE, stdin);
	busqueda[strcspn(busqueda, "\n")] = '\0';
	
	printf("\n  Resultados para: \"%s\"\n", busqueda);
	
	for (i = 0; i < cantidad; i++) {
		Interseccion *reg = historial + i;
		
		/* Comparación sin distinción de mayúsculas usando strstr */
		int en1 = (strstr(reg->calle1, busqueda) != NULL);
		int en2 = (strstr(reg->calle2, busqueda) != NULL);
		
		if (en1 || en2) {
			encontrado = 1;
			
			/* Mostrar la calle que intersecta (la "otra") */
			char *intersecta = en1 ? reg->calle2 : reg->calle1;
			
			printf("  Intersecta con : %s\n", intersecta);
			printf("  Trafico        : %d veh/h\n", reg->trafico);
		}
	}
	
	if (!encontrado)
		printf("  No se encontraron intersecciones para esa calle.\n");
	
	printf("\n");
}