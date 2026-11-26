// Crear un programa que permita almacenar los datos de 10 personas (DNI, nombre, sexo, edad) y mediante el ingreso de una posición “I” realizar la lectura de dicha posición en el archivo de manera directa. El programa debe terminar cuando se ingresa I = -1.

#include <stdio.h>

typedef struct
{
  int dni;
  char nombre[50];
  char sexo;
  int edad;
} Persona;

void cargar_personas(FILE *file, Persona personas[], int n);
void mostrar_personas(FILE *file, int n);
void reemplazar_persona(FILE *file, int idx, Persona nueva_persona);

int main()
{

  FILE *file = fopen("personas.txt", "wb+");

  if (file == NULL)
  {
    printf("No se pudo abrir el archivo");
    return 1;
  }

  int n = 2;
  Persona personas[n];

  cargar_personas(file, personas, n);
  mostrar_personas(file, n);
  reemplazar_persona(file, 1, personas[1]);
  mostrar_personas(file, n);

  fclose(file);
  return 0;
}

void limpiar_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void cargar_personas(FILE *file, Persona personas[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("Persona %d\n", i + 1);
    printf("Ingrese dni\n> ");
    scanf("%d", &personas[i].dni);
    limpiar_buffer();
    printf("Ingrese nombre\n> ");
    fgets(personas[i].nombre, sizeof(personas[i].nombre), stdin);
    printf("Ingrese sexo (M: masculino; F: Feminino)\n> ");
    scanf("%c", &personas[i].sexo);
    printf("Ingrese edad\n> ");
    scanf("%d", &personas[i].edad);
  }

  fwrite(personas, sizeof(Persona), n, file);
}

int es_indice_valido(int idx, int n)
{
  if (idx == -1)
  {
    printf("Bye\n");
    return 0;
  }
  if (idx > n || idx <= 0)
  {
    printf("Indice invalido\n");
    return 0;
  }
}

void mostrar_personas(FILE *file, int n)
{
  int idx = 0;

  while (idx != -1)
  {
    printf("Ingrese el indice\n> ");
    scanf("%d", &idx);
    if (!es_indice_valido(idx, n))
    {
      continue;
    }

    fseek(file, (idx - 1) * sizeof(Persona), SEEK_SET);
    Persona persona = {0};
    fread(&persona, sizeof(Persona), 1, file);
    printf("Dni: %d; Nombre: %s; Sexo: %c; Edad: %d\n", persona.dni, persona.nombre, persona.sexo, persona.edad);
  }
}

void reemplazar_persona(FILE *file, int idx, Persona nueva_persona)
{
  Persona persona;
  fseek(file, (idx - 1) * sizeof(Persona), SEEK_SET);
  fread(&persona, sizeof(Persona), 1, file);
  printf("Anterior persona: Dni: %d; Nombre: %s; Edad: %d; Sexo: %c\n", persona.dni, persona.nombre, persona.edad, persona.sexo);
  fseek(file, (idx - 1) * sizeof(Persona), SEEK_SET);

  printf("Nueva persona: Dni: %d; Nombre: %s; Edad: %d; Sexo: %c\n", nueva_persona.dni, nueva_persona.nombre, nueva_persona.edad, nueva_persona.sexo);
  fwrite(&nueva_persona, sizeof(Persona), 1, file);
}