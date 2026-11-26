# notas

## Archivos

Dispositivo fisico capaz de transmitir y almacenar información

## Flujos

- Binario: codigo binario o base 64.
- Texto: usan ascii.
- Estandar: creados por el SO

## Funciones para trabajar con archivos

- Abrir un archivo: `fopen()`, este retorna un puntero a un tipo FILE

```C
    // El segundo parametro es el modo de apertura.
    FILE *file = fopen("archivo.txt", "r");
```

### Modos de apertura

- Lectura: `r`
- Escritura: `w`
- Añadir: `a` (se añade lo que se escribe, si el archivo no existe se crea)
- Lectura y escritura: `r+` (si no existe tira error)
- Escritura y lectura: `w+` (si no existe lo crea)
- Todos los modos tienen una variante binaria agregando `b` al final, por ejemplo: `rb`, `wb`, `ab`, `r+b`, `w+b`.

- Cerrar un archivo: `fclose()`

```C
    // 0 si se cerró correctamente, -1 si hubo error
    int closed = fclose(file);
```

## Archivos de acceso secuencial

Para poder leer o encontrar cierta palabra en una archivo debemos realizar una busqueda secuencial

## Escritura de un byte

```C
    // Escribe un byte en el archivo
    putc(int byte, FILE *file);
```

## Leer un byte

```C
    // Lee un byte del archivo
    int byte = getc(FILE *file);
```

## Escritura de un string

```C
    // Escribe un string en el archivo
    // Retorna un valor negativo si hubo error, 0 si se escribió correctamente
    int status = fputs(const char *str, FILE *file);
```

## Leer string

```C
    // Lee un string del archivo
    // Retorna un puntero al string leído, NULL si hubo error o fin de archivo
    // El segundo parametro es la cantidad de caracteres a leer
    char *str = fgets(char *str, int n, FILE *file);
```

## Escribir bloque completo de bytes

```C
    // Escribe un bloque de bytes en el archivo
    // Retorna la cantidad de elementos escritos correctamente
    size_t written = fwrite(const void *ptr, size_t size, size_t count, FILE *file);
```
