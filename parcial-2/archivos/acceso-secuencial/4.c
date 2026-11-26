// Se efectúa una encuesta para conocer el nivel de ocupación de los pobladores de una ciudad. Los encuestados contestaron los siguientes ítems:
// - Sexo (1 varón; 2 mujer)
// - Edad
// - Estado civil (1 soltero; 2 casado; 3 otros)
// - Trabaja (0 no; 1 sí)
// - Estudia (0 no; 1 sí).
// a) Generar un archivo con todos los datos validados
// b) Utilizando el archivo imprimir un reporte como el siguiente:

// PORCENTAJES
// • varones xx
// • mujeres xx
// • menores de 18 años que trabajan xx
// • solteros xx
// • casados xx
// • encuestados que trabajan y estudian xx
// • mujeres que trabajan xx

#include <stdio.h>

typedef struct
{
  int sexo;
  int edad;
  int estado_civil;
  int estudia;
  int trabaja;
} Poblador;

typedef struct
{
  float varones;
  float mujeres;
  float menores_18_trabajando;
  float solteros;
  float casados;
  float trabajando_estudiando;
  float mujeres_trabajando;
} Informe_Porcentajes;

void pedir_datos(FILE *file);
int leer_entero_validado(char mensaje[], int min, int max);
Informe_Porcentajes armar_informe(FILE *file);
void mostrar_informe(Informe_Porcentajes informe);

int main()
{

  FILE *file = fopen("ocupacion.txt", "w+");
  fputs("Sexo-Edad-EstadoCivil-Estudia-Trabaja\n", file);
  pedir_datos(file);
  rewind(file);
  Informe_Porcentajes informe = armar_informe(file);
  mostrar_informe(informe);
  fclose(file);
  return 0;
}

void pedir_datos(FILE *file)
{
  int cantidad = 0;

  printf("Ingrese la cantidad de pobladores a cargar\n> ");
  scanf("%d", &cantidad);

  int i = 0;
  while (i < cantidad)
  {
    printf("Info del poblador nro %d\n", ++i);
    Poblador poblador = {
        .sexo = leer_entero_validado("Sexo (1 varon; 2 mujer)\n> ", 1, 2),
        .edad = leer_entero_validado("Edad\n> ", 1, 150),
        .estado_civil = leer_entero_validado("Estado civil (1 soltero; 2 casados; 3 otros)\n> ", 1, 3),
        .estudia = leer_entero_validado("Estudia? (1 si; 0; no)\n> ", 0, 1),
        .trabaja = leer_entero_validado("Trabaja? (1 si; 0 no)\n> ", 0, 1)};

    fprintf(file, "%d-%d-%d-%d-%d\n", poblador.sexo, poblador.edad, poblador.estado_civil, poblador.estudia, poblador.trabaja);
  }
}

int leer_entero_validado(char mensaje[], int min, int max)
{
  int valor;
  do
  {
    printf("%s", mensaje);
    scanf("%d", &valor);
    if (valor < min || valor > max)
    {
      printf("Invalido, intente de nuevo\n");
    }
  } while (valor < min || valor > max);

  return valor;
}

float obtener_porcentaje(float cantidad, float total)
{
  return cantidad / total * 100;
}

Informe_Porcentajes armar_informe(FILE *file)
{

  Informe_Porcentajes informe = {0};
  Poblador poblador = {0};
  char headers[60];

  fgets(headers, sizeof(headers), file);

  while (fscanf(file, "%d-%d-%d-%d-%d", &poblador.sexo, &poblador.edad, &poblador.estado_civil, &poblador.estudia, &poblador.trabaja) == 5)
  {
    if (poblador.sexo == 1)
    {
      informe.varones += 1;
    }
    else
    {
      informe.mujeres += 1;
    }

    if (poblador.trabaja)
    {
      if (poblador.edad < 18)
      {

        informe.menores_18_trabajando += 1;
      }
      if (poblador.estudia)
      {
        informe.trabajando_estudiando += 1;
      }
      if (poblador.sexo == 2)
      {
        informe.mujeres_trabajando += 1;
      }
    }

    if (poblador.estado_civil == 1)
    {
      informe.solteros += 1;
    }
    else if (poblador.estado_civil == 2)
    {
      informe.casados += 1;
    }
  }

  int total_encuestados = informe.varones + informe.mujeres;
  informe.varones = obtener_porcentaje(informe.varones, total_encuestados);
  informe.mujeres = obtener_porcentaje(informe.mujeres, total_encuestados);
  informe.menores_18_trabajando = obtener_porcentaje(informe.menores_18_trabajando, total_encuestados);
  informe.casados = obtener_porcentaje(informe.casados, total_encuestados);
  informe.solteros = obtener_porcentaje(informe.solteros, total_encuestados);
  informe.trabajando_estudiando = obtener_porcentaje(informe.trabajando_estudiando, total_encuestados);
  informe.mujeres_trabajando = obtener_porcentaje(informe.mujeres_trabajando, total_encuestados);

  return informe;
}

void mostrar_informe(Informe_Porcentajes informe)
{
  printf("Informe de porcentajes\n");
  printf("Varones: %.1f%%\n", informe.varones);
  printf("Mujeres: %.1f%%\n", informe.mujeres);
  printf("Menores de 18 trabajando: %.1f%%\n", informe.menores_18_trabajando);
  printf("Solteros: %.1f%%\n", informe.solteros);
  printf("Casados: %.1f%%\n", informe.casados);
  printf("Trabajan y Estudian: %.1f%%\n", informe.trabajando_estudiando);
  printf("Mujeres que trabajan: %.1f%%\n", informe.mujeres_trabajando);
}