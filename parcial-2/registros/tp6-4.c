// #Crear un registro que permita almacenar información relacionada con un músico.Cada músico cuenta con un nombre, una edad, un género músical e información sobre sus discos.Cada disco, posee un título, un año de lanzamiento y su cantidad de canciones.

#include <stdio.h>

#define MAX_DISCOS 20
#define MAX_MUSICOS 2

typedef struct
{
  char titulo[60];
  int lanzamiento;
  int canciones;
} Disco;

typedef struct
{
  char nombre[30];
  int edad;
  char genero[30];
  int cantidad_discos;
  Disco discos[MAX_DISCOS];
} Musico;

void agregar_musicos(Musico musicos[], int n);
void mostrar_musicos_discos(Musico musicos[], int n);
void mostrar_musicos_anio(Musico musicos[], int n, int anio);

int main()
{
  int cantidad_musicos = MAX_MUSICOS;
  Musico musicos[cantidad_musicos];
  agregar_musicos(musicos, cantidad_musicos);
  // mostrar_musicos_discos(musicos, cantidad_musicos);
  mostrar_musicos_anio(musicos, cantidad_musicos, 2000);
  return 0;
}

void limpiar_linea()
{
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void agregar_musicos(Musico musicos[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("Ingresando la info del musico nro: %d\n", i + 1);
    printf("nombre: ");
    fgets(musicos[i].nombre, sizeof(musicos[i].nombre), stdin);
    printf("edad: ");
    scanf("%d", &musicos[i].edad);

    limpiar_linea();
    printf("genero musical: ");
    fgets(musicos[i].genero, sizeof(musicos[i].genero), stdin);

    printf("Ingresando la info de los discos\n");
    printf("cuantos discos tiene el musico? (maximo 20 por artista)\n");
    scanf("%d", &musicos[i].cantidad_discos);
    limpiar_linea();
    for (int j = 0; j < musicos[i].cantidad_discos; j++)
    {
      printf("Ingrese la informacion del disco nro: %d\n", j + 1);
      printf("titulo: ");
      fgets(musicos[i].discos[j].titulo, sizeof(musicos[i].discos[j].titulo), stdin);
      printf("anio de lanzamiento: ");
      scanf("%d", &musicos[i].discos[j].lanzamiento);
      printf("canciones: ");
      scanf("%d", &musicos[i].discos[j].canciones);
      limpiar_linea();
    }
    printf("Muchas gracias\n");
  }
}

void mostrar_musicos_discos(Musico musicos[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("====Musico====\n %s\n", musicos[i].nombre);
    printf("edad: %d\n", musicos[i].edad);
    printf("genero que toca: %s\n", musicos[i].genero);

    printf("====DISCOS====\n");
    for (int j = 0; j < musicos[i].cantidad_discos; j++)
    {
      Disco disco = musicos[i].discos[j];
      printf("titulo: %s\n", disco.titulo);
      printf("anio de lanzamiento: %d\n", disco.lanzamiento);
      printf("cantidad de canciones: %d\n", disco.canciones);
    }
  }
}

// Una función que reciba el vector de músicos, un año e imprima por pantalla el nombre de los discos cuyo año de lanzamiento sea posterior al recibido cómo parámetro. Además, se debe incluir el nombre del artista, el género y la cantidad de canciones del disco.
void mostrar_musicos_anio(Musico musicos[], int n, int anio)
{
  for (int i = 0; i < n; i++)
  {
    Musico musico = musicos[i];
    for (int j = 0; j < musico.cantidad_discos; j++)
    {

      Disco disco = musico.discos[j];
      if (disco.lanzamiento > anio)
      {
        printf("Artista: %s\n", musico.nombre);
        printf("Genero: %s\n", musico.genero);
        printf("Disco: %s\n", disco.titulo);
        printf("Cantidad de canciones %s\n", disco.canciones);
      }
    }
  }
}