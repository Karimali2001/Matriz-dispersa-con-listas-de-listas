//menu
#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(){

    int opc, i,j, x, e; //variable para menu //fila columna y elemento 
    printf("                MATRICES DISPERSA CON LISTAS ENLAZADAS\n");//encabezado
    Array *M1=crearMatriz(), *M2; //creacion la matriz 1 y 2 
    //menu
    do{ 
        printf("\n\n\n"); //dejo espacios arriba
        printf("Ingrese la operacion que desea realizar\n\n");
        printf("   1. Obtener elemento de la matriz\n");
        printf("   2. Asignar elemento en una posicion dada de la matriz\n");
        printf("   3. Sumar dos matrices\n"); 
        printf("   4. Multiplicar la matriz por un escalar\n");
        printf("   5. Multiplicar dos matrices\n");
        printf("   6. Trasponer la matriz\n");
        printf("   7. Imprimir la matriz (incluyendo valores nulos)\n");
        printf("   8. Imprimir la matriz (sin incluir valores nulos)\n");
        printf("   9. Escribir la matriz en un archivo de texto\n");
        printf("   0. Salir\n");
        scanf("%i", &opc);
        switch (opc){
        case 1:
            printf("Ingrese la fila y la columna del elemento que desea obtener\n");
            scanf("%i %i", &i, &j);
            printf("El elemento de la fila %i de la columna %i es: %i\n",i,j, ObtenerElemento(i,j,M1));
            break;
        case 2:
            printf("Ingrese la fila, la columna y el elemento que desea asignar en la matriz\n");
            scanf("%i %i %i", &i, &j, &x);
            M1=AsignarElemento(M1,i,j,x);
        break; 
        case 3:
            printf("Ingrese la segunda matriz\n\n");
            M2=crearMatriz(); //matriz dos
            M1=Sumar(M1, M2);
            break;
        case 4:
            printf("Ingrese el escalar por el que desea multiplicar la matriz\n");
            scanf("%i", &e);
            M1=productoPorEscalar(e,M1);
            break;
        case 5:
            printf("Ingrese la segunda matriz\n\n");
            M2=crearMatriz(); //matriz dos

            M1=multiplicacion(M1, M2);
            break;
        case 6:
            M1=transpuesta(M1);
            break;
        case 7:
            imprimir(M1);
            break;
        case 8:
            imprimir2(M1);
            break;
        case 9:
            imprimirMatrizArchivo(M1);
            break;
        case 0:
            break;      
        default:
            printf("No ingresaste una opcion valida\n");
            break;
        }

    }while(opc); //opc distinto de cero
    return 0;
}
