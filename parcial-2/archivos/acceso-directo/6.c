#include <stdio.h>

typedef struct
{
  int cod_producto;
  char descripcion[40];
  int stock_actual;
  int punto_reposicion;
} Producto;

typedef struct
{
  int cod_producto;
  int idx;
} Indice;

int main()
{

  FILE *file = fopen("productos.dat", "wb+");
  FILE *fileI = fopen("indices.txt", "w+");
  FILE *fileC = fopen("compras.txt", "w+");

  if (file == NULL || fileI == NULL || fileC == NULL)
  {
    printf("fallo un archivo\n");
    return 1;
  }

  Producto productos[3] = {
      {101, "Arroz", 25, 10},
      {102, "Aceite", 3, 5},
      {103, "Azucar", 30, 15}};

  fwrite(productos, sizeof(Producto), 3, file);

  for (int i = 0; i < 3; i++)
  {
    fprintf(fileI, "%d %d\n", productos[i].cod_producto, i);
  }
  fflush(file);
  fflush(fileI);
  rewind(file);
  rewind(fileI);

  int busqueda = 110;

  Producto producto = {.cod_producto = 0};
  Indice indice;
  while (fscanf(fileI, "%d %d", &indice.cod_producto, &indice.idx) == 2)
  {
    if (indice.cod_producto == busqueda)
    {
      fseek(file, indice.idx * sizeof(Producto), SEEK_SET);
      fread(&producto, sizeof(producto), 1, file);
      break;
    }
  }

  if (producto.cod_producto != 0)
  {
    if (producto.stock_actual < producto.punto_reposicion)
    {
      fprintf(fileC, "Comprar: %s, faltan %d unidades\n", producto.descripcion, (producto.punto_reposicion - producto.stock_actual));
    }
  }
  else
  {
    printf("Producto no encontrado\n");
  }

  return 0;
}
