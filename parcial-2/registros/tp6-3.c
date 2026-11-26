#include <stdio.h>

typedef struct
{
  int nro_legajo;
  int anio_inicio;
  float nota_promedio;
} Ficha_alumno;

void cargar_fichas(Ficha_alumno fichas[], int n);
void mostrar_fichas(Ficha_alumno fichas[], int n);

int main()
{
  int CANTIDAD_FICHAS = 2;
  Ficha_alumno fichas[CANTIDAD_FICHAS];
  cargar_fichas(fichas, CANTIDAD_FICHAS);
  mostrar_fichas(fichas, CANTIDAD_FICHAS);
  return 0;
}

void cargar_fichas(Ficha_alumno fichas[], int n)
{

  for (int i = 0; i < n; i++)
  {
    printf("Alumno %d\n", i + 1);
    printf("Ingrese el nro de legajo: ");
    scanf("%d", &fichas[i].nro_legajo);
    printf("Ingrese el anio de ingreso: ");
    scanf("%d", &fichas[i].anio_inicio);
    printf("Ingrese la nota promedio: ");
    scanf("%f", &fichas[i].nota_promedio);
  }
}

void mostrar_fichas(Ficha_alumno fichas[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("Ficha nro: %d\n", i + 1);
    printf("Nro de legajo:%d\n", fichas[i].nro_legajo);
    printf("Nota promedio:%.2f\n", fichas[i].nota_promedio);
    printf("Anio de inicio:%d\n", fichas[i].anio_inicio);
  }
}