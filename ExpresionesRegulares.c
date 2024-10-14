#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
    char *nombre;
    struct nodo *sig;
} TNodo;

// Funci�n para crear un nuevo nodo
TNodo *CrearNodo(char *nombre)
{
    TNodo *ptr = (TNodo *)malloc(sizeof(TNodo));

    if (ptr == NULL)
    {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    ptr->nombre = (char *)malloc(strlen(nombre) + 1);

    if (ptr->nombre == NULL)
    {
        printf("Error al reservar memoria para el nombre.\n");
        exit(1);
    }

    strcpy(ptr->nombre, nombre);
    ptr->sig = NULL;

    return ptr;
}

// Funci�n para insertar un nodo al final de la lista
void InsertaFinal(TNodo **cab, char *nombre)
{
    TNodo *ptr, *aux;

    ptr = CrearNodo(nombre);
    if (*cab == NULL) // Si la lista est� vac�a
    {
        *cab = ptr;
    }
    else
    {
        aux = *cab;
        while (aux->sig != NULL)
            aux = aux->sig;

        aux->sig = ptr;
    }
}

// Funci�n para imprimir la lista
void Imprime(TNodo *cab)
{
    TNodo *aux = cab;

    while (aux != NULL)
    {
        printf("%s", aux->nombre); // fgets incluye el salto de l�nea
        aux = aux->sig;
    }
    printf("\n");
}

// Funci�n para leer nombres desde un archivo e insertarlos en la lista
void LeerArchivo(TNodo **cab, char *nArchivo)
{
    FILE *archivo = fopen(nArchivo, "r");
    char nombre[50];

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo: %s\n", nArchivo);
        return;
    }

    while (fgets(nombre, sizeof(nombre), archivo))
    {
        InsertaFinal(cab, nombre);
    }

    fclose(archivo);
}

// Funci�n principal
int main()
{
    TNodo *cab = NULL;
    char nombreArchivo[50];

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    // Verificar si el archivo existe
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("El archivo '%s' no existe.\n", nombreArchivo);
        return 1;
    }
    fclose(archivo); // Cerrar el archivo despu�s de verificar la existencia

    // Leer los nombres del archivo y agregarlos a la lista
    LeerArchivo(&cab, nombreArchivo);

    printf("Nombres en la lista:\n");
    Imprime(cab);

    return 0;
}
