#include <stdio.h>

typedef struct
{
  int id;
  char direccion[100];
  int movimientos;
  float saldo_total;
} Cajero;

typedef struct
{
  int id_cajero;
  int operacion;
  float monto;
} Movimiento;

int main()
{

  FILE *movimientos = fopen("movimientos.txt", "r");
  FILE *cajeros = fopen("cajeros.dat", "wb+");

  if (movimientos == NULL || cajeros == NULL)
  {
    printf("No se abrieron los archivos");
    return 1;
  }

  Movimiento movimiento;
  while (fscanf(movimientos, "%d %d %f", &movimiento.id_cajero, &movimiento.operacion, &movimiento.monto) == 3)
  {
    Cajero cajero = {.id = movimiento.id_cajero, .movimientos = 0};

    // escribimos la dirección
    snprintf(cajero.direccion, sizeof(cajero.direccion), "Calle %d", cajero.id);

    while (movimiento.id_cajero == cajero.id)
    {
      cajero.movimientos++;
      if (movimiento.operacion == 1)
      {
        cajero.saldo_total += movimiento.monto;
      }
      else if (movimiento.operacion == 2)
      {
        cajero.saldo_total -= movimiento.monto;
      }
      if (fscanf(movimientos, "%d %d %f", &movimiento.id_cajero, &movimiento.operacion, &movimiento.monto) != 3)
      {
        break;
      }
    }

    fwrite(&cajero, sizeof(Cajero), 1, cajeros);
    printf("Guardado cajero %d con %d movimientos y saldo total de %.2f\n", cajero.id, cajero.movimientos, cajero.saldo_total);
  };

  Cajero ultimo_cajero = {0};
  fseek(cajeros, -sizeof(Cajero), SEEK_END);
  fread(&ultimo_cajero, sizeof(Cajero), 1, cajeros);
  fseek(cajeros, -sizeof(Cajero), SEEK_END);
  ultimo_cajero.movimientos = 0;
  fwrite(&ultimo_cajero, sizeof(Cajero), 1, cajeros);

  fseek(cajeros, -sizeof(Cajero), SEEK_END);
  fread(&ultimo_cajero, sizeof(Cajero), 1, cajeros);

  fclose(movimientos);
  fclose(cajeros);
  return 0;
}