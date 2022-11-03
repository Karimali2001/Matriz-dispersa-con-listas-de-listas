#ifndef matriz_h
#define matriz_h
//declaracion de la estructura total de la matriz
typedef struct node{
	int column;       //columna 
	int value;        //valor
	struct node *next; //apunta al siguiente nodo 
}Node;   

typedef struct noderow{
	int row;        //fila actual
	Node *begin, *end;   //apuntadores a elemento inicial y final
	struct noderow *next; 
}NodeRow;

typedef struct array{
	int rows;          //Numero de filas
	int columns;       //Numero de columnas
	NodeRow *begin, *end; //apuntadores a fila incial y final 
}Array;


//crea un nodo donde se almacenara la columna y el valor de un elemento de la matriz
Node *crearNode(int column, int value);
//crea un nodo con el valor de una fila de la matriz 
NodeRow *crearNodeRow(int row);
//crea un nodo que almacena la cantidad de filas y columnas que tendra la matriz
Array *crearArray(int rows, int columns);
//agrega una fila al final del array disperso sin orden 
Array *agregarFilaFinal(Array *matriz, NodeRow *newRow);
//agrega un elemento al final de la fila del array disperso sin orden 
NodeRow *agregarElementoFinal(NodeRow *auxFila, Node *newElemento);
//imprime la matriz sin los valores nulos 
void imprimir2(Array *matriz);
//busca si la columna existe en la fila de la matriz
int existeColumnaObtener(int j, Node *auxElementos);
//busca si la fila existe en la matriz
int existeFilaObtener(int i, int j, NodeRow *auxFila);
//obtiene el elemento de la fila i de la columna j de la matriz
int ObtenerElemento(int i, int j, Array *M);
//funcion que suma dos filas de una matriz y retorna una nueva fila
NodeRow *sumarFilas(NodeRow *auxF1, NodeRow *auxF2);
//funcion que devuelve la copia de una fila dada
NodeRow *copiarFila(NodeRow *auxF);
//devuelve la matriz resultante al sumar M1 y M2
Array *Sumar(Array *M1, Array *M2);
//crea la matriz con datos recibidos del terminal
Array *leerMatrizTerminal();
// Funcion para agregar un nuevo elemento a una matriz
Array *AsignarElemento(Array *M, int row, int column, int value);
//crea la matriz leida por un archivo de texto
Array *leerMatrizArchivo();
//Crear una matriz nueva
Array *crearMatriz();
// Funcion utilizada para multiplicar todos los valores de la matriz por un numero e
Array *productoPorEscalar(int e, Array *M);
// Sumar a un elemento de la matriz un numero
Array *sumar_fila_columna(Array *M, int row, int column, int value);
// Multiplicacion de dos matrices
Array *multiplicacion(Array *M1, Array *M2);
// Genera la transpuesta de la matriz recibida
Array *transpuesta(Array *M);
// Imprimir la matriz (incluyendo los 0)
void imprimir(Array *M);
//imprime la matriz en un archivo de texto
void imprimirMatrizArchivo(Array *matriz);

#endif
