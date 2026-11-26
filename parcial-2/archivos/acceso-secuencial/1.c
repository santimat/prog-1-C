// Crear un programa que permita ingresar cinco cadenas de caracteres por teclado de manera sucesiva en un archivo de texto “cadenas.txt”.

#include <stdio.h>
#include <string.h>

int main()
{

  FILE *fileW = fopen("cadenas.txt", "w");

  if (fileW == NULL)
  {
    printf("Es una mierda esto\n");
  }

  for (int i = 0; i < 3; i++)
  {
    char palabra[50];
    printf("Agregue la palabra nro (maximo 50 caracteres): %d\n> ", i + 1);
    gets(palabra);
    fputs(palabra, fileW);
    fputs("\n", fileW);
  }
  fclose(fileW);

  FILE *fileR = fopen("cadenas.txt", "r");
  // if (fileR == NULL)
  // {
  //   printf("ES UNA MIERDA ESTO\n");
  // }

  // int c = getc(fileR);
  // while (c != EOF)
  // {
  //   printf("%c", c);
  //   c = getc(fileR);
  // }

  char palabra[50];
  while (fgets(palabra, sizeof(palabra), fileR) != NULL)
  {
    printf("%s\n", palabra);
  }
  fclose(fileR);

  return 0;
}