// En un archivo secuencial (por ejemplo “lluvias.txt”) se almacenan datos sobre la lluvia caída en un cierto período. Cada línea corresponde a un día y contiene los siguientes datos:
// Día - Mes - Año - Precipitaciones(0 si no llovió)
// Preparar un algoritmo con los procedimientos necesarios para :
// Cargar los datos correspondientes a los 30 días del mes de septiembre del corriente año.
// Leer el archivo e informar por pantalla : cuántos días hubo sin lluvias, cuántos días llovió menos de 50 mm y cuántos llovió 50 mm ó más.

#include <stdio.h>

typedef struct
{
  int sin_lluvia;
  int menos_50;
  int igual_mas_50;
} Informe;

void cargar_archivo(FILE *file, int dias, char mes[], char anio[]);
Informe armar_informe(FILE *file);

int main()
{
  int dias = 5;
  char mes[] = "9", anio[] = "2026";
  char headers[60];
  FILE *file = fopen("lluvias.txt", "w+");
  fputs("Dia-Mes-Anio-Precipitaciones\n", file);

  cargar_archivo(file, dias, mes, anio);

  // cuando se mantiene abierto el archivo a la hora de leer arranca desde donde quedó el cursor en el ultimo momento. Es decir si usamos w+ (escritura lectura), si escribimos 5 lineas, cuando hagamos fscanf vamos a empezar a leer desde la linea 5. rewind lo que hace es volver el cursor al inicio
  rewind(file);

  // Limpiamos cabeceras
  fgets(headers, sizeof(headers), file);

  Informe informe = armar_informe(file);

  printf("Dias sin lluvia: %d\n", informe.sin_lluvia);
  printf("Dias con menos de 50mm: %d\n", informe.menos_50);
  printf("Dias con 50mm o mas: %d\n", informe.igual_mas_50);

  fclose(file);
  return 0;
}

void cargar_archivo(FILE *file, int dias, char mes[], char anio[])
{
  for (int i = 0; i < dias; i++)
  {
    char precipitacion[50];
    printf("Dia %d\n", i + 1);
    printf("Ingrese las precipitaciones para el %d/%s/%s: \n> ", i + 1, mes, anio);
    fgets(precipitacion, sizeof(precipitacion), stdin);
    fprintf(file, "%d-%s-%s-%s", (i + 1), mes, anio, precipitacion);
  }
}

Informe armar_informe(FILE *file)
{
  Informe informe = {0};
  int dia, mes, anio, precipitacion;

  while (fscanf(file, "%d-%d-%d-%d", &dia, &mes, &anio, &precipitacion) == 4)
  {
    if (precipitacion == 0)
    {
      informe.sin_lluvia += 1;
    }
    else if (precipitacion > 0 && precipitacion < 50)
    {
      informe.menos_50 += 1;
    }
    else if (precipitacion >= 50)
    {
      informe.igual_mas_50 += 1;
    }
  };

  return informe;
}