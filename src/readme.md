# **Funciones tellg y seekg**

## **Seekg()**

Es una función en la biblioteca iostream (parte de la biblioteca estándar) que te permite buscar una posición arbitraria en un archivo. Se utiliza en el manejo de archivos para establecer la posición del siguiente carácter que se extraerá del flujo de entrada de un archivo determinado.

```c
istream & seekg (posición de streampos);
istream & seekg (desplazamiento de flujo de salida, ios_base::seekdir dir);
```

> fichero.seekg(10, ios::cur); // Saltar 10 bytes

> fichero.seekg(0, ios::beg); // Volver al principio

> fichero.seekg(0, ios::end); // Ir al final del fichero

## **Tellg()**

La función tellg() se usa con flujos de entrada y devuelve la posición actual de "obtención" del puntero en el flujo.
Para saber en qué posición estamos se usa "tellg" (para lectura de ficheros) o "tellp" (para escritura en fichero).

Podremos saber cual es la longitud en bytes de dicho fichero:

> tamano = fichero.tellg(); // Ver posicion para saber tamaño

Para leer un bloque de información usaremos
>"fichero.read(bloque, tamaño);" // y para escribir un bloque "fichero.write(bloque, tamaño);".
