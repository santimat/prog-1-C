#include <stdio.h>

// Ejercicio 1
// Crear ficha de alumno

typedef struct
{
  int nro_legajo;
  int nota_promedio;
  int anio_ingreso;
} Ficha_alumno;

int diferencia_anios(Ficha_alumno *fa, int anio_actual);

int main()
{

  Ficha_alumno ficha_santino = {
      .nro_legajo = 25633,
      .anio_ingreso = 2005,
      .nota_promedio = 7.5};
  printf("Ficha santino:\n");
  printf("Nro legajo: %d\nAnio ingreso:%d\nNota promedio:%d\n", ficha_santino.nro_legajo, ficha_santino.anio_ingreso, ficha_santino.nota_promedio);

  printf("El alumno cursa hace: %d anios", diferencia_anios(&ficha_santino, 2026));

  return 0;
}

int diferencia_anios(Ficha_alumno *fa, int anio_actual)
{

  return anio_actual - fa->anio_ingreso;
}