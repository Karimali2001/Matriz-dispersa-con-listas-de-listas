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
Node *crearNode(int column, int value){
	Node *newNode;
    if((newNode=(Node *)malloc(sizeof(Node)))==NULL){ //se verifica que exista espacio suficiente en la memoria
		printf("crearNode: error en malloc");
		exit(1); //termina la ejecucion del programa y retorna 1
	}
	newNode->column=column; 
	newNode->value=value;
	newNode->next=NULL;
	return newNode;
	
}

//crea un nodo con el valor de una fila de la matriz 
NodeRow *crearNodeRow(int row){
	NodeRow *newNode;
    if((newNode=(NodeRow *)malloc(sizeof(NodeRow)))==NULL){//se verifica que exista espacio suficiente en la memoria
		printf("crearNodeRow: error en malloc"); 
		exit(1); //termina la ejecucion del programa y retorna 1
	}
	newNode->row=row;
	newNode->begin=NULL;
	newNode->end=NULL;
	newNode->next=NULL; //el siguiente apunta a NULL porque no se sabe si es la ultima fila 
}


//crea un nodo que almacena la cantidad de filas y columnas que tendra la matriz
Array *crearArray(int rows, int columns){//se verifica que exista espacio suficiente en la memoria
   Array *newNode;
   if((newNode=(Array *)malloc(sizeof(Array)))==NULL){ //se verifica que exista espacio suficiente en la memoria
		printf("crearArray: error en malloc"); 
		exit(1); //termina la ejecucion del programa y retorna 1
	}
	newNode->rows=rows;
	newNode->columns=columns;
	newNode->begin=NULL;
	newNode->end=NULL;
	return newNode; 
}

//agrega una fila al final del array disperso sin orden 
Array *agregarFilaFinal(Array *matriz, NodeRow *newRow){
	if(!(matriz->begin)){ //si la matriz no tiene ninguna fila 
        matriz->begin=matriz->end=newRow; //la matriz comienza y termina en la nueva fila
	}else{ //si la matriz ya tiene filas
		matriz->end->next=newRow; //la ultima fila apunta a la nueva ultima fila  
		matriz->end=newRow; //la ultima fila de la matriz ahora es la nueva fila 
	}
	return matriz;
}

//agrega un elemento al final de la fila del array disperso sin orden 
NodeRow *agregarElementoFinal(NodeRow *auxFila, Node *newElemento){
	if(!(auxFila->begin)){ //si la fila no tiene ningun elemento 
        auxFila->begin=auxFila->end=newElemento; //la fila comienza y termina en el mismo nuevo elemento
	}else{ //si la fila ya tiene elementos 
		auxFila->end->next=newElemento; //el ultimo elemento apunta al nuevo ultimo elemento de la fila  
		auxFila->end=newElemento; //el ultimo elemento de la fila ahora es el nuevo ultimo elemento  
	}
	return auxFila;
}


//imprime la matriz sin los valores nulos 
void imprimir2(Array *matriz){
	NodeRow *auxFila; //para recorrer las filas
	Node *auxElementos; //para recorrer los elementos de la fila actual
	printf("\n\n\n"); //dejo espacio
	printf("matriz: %i:%i\n", matriz->rows, matriz->columns);
	printf("|\n");
	for(auxFila=matriz->begin;auxFila!=NULL;auxFila=auxFila->next){ //recorro la primera fila de la matriz hasta la ultima 
		printf("Fila %i -> ", auxFila->row);
		for(auxElementos=auxFila->begin;auxElementos!=NULL;auxElementos=auxElementos->next){ //recorro el primer elemento de la fila hasta a la ultima 
			printf("C:%i:V:%i->", auxElementos->column, auxElementos->value);
		}
		printf("NULL\n");
		printf("|\n");
	}
	printf("NULL\n");
}

//busca si la columna existe en la fila de la matriz
int existeColumnaObtener(int j, Node *auxElementos){
		for(;auxElementos!=NULL;auxElementos=auxElementos->next){ //recorro los elementos de la fila actual 
			if(auxElementos->column==j){ //si existe la columna dada entonces retorno el elemento
				return auxElementos->value;
			}
		}
		return 0; //retorno cero porque el elemento es nulo 

} 
//busca si la fila existe en la matriz
int existeFilaObtener(int i, int j, NodeRow *auxFila){
	for(;auxFila!=NULL;auxFila=auxFila->next){ //recorro cada fila de la matriz
		if(auxFila->row==i){ //si existe entonces busco si la columna existe en esa fila 
			return existeColumnaObtener(j, auxFila->begin);
		}
	}
	return 0; //la fila es parte de la matriz pero tiene solo elementos nulos y por eso no se almaceno
}

//obtiene el elemento de la fila i de la columna j de la matriz
int ObtenerElemento(int i, int j, Array *M){
	if((i<M->rows) && (j<M->columns) && (i>=0) && (j>=0)){ //si i y j no se salen de los limites de la matriz 
		return existeFilaObtener(i,j,M->begin);
	}
	return 0;
}

//inserta un elemento ordenado en una fila dada 
NodeRow *agregarElementoOrdenado(NodeRow *auxFila, Node *auxElementos){
	
	if(!(auxFila->begin)){ //si la fila no tiene ningun elemento 
        auxFila->begin=auxFila->end=auxElementos; //la fila comienza y termina en el mismo nuevo elemento
	}else{ //si la fila ya tiene elementos 
		Node *auxElement2,*auxElement3; //limite inferior y posterior para recorrer los elementos de la fila
		if(auxElementos->column<auxFila->begin->column){ //verifico si va al principio
			auxElement2=auxFila->begin; //guardo el puntero hacia el nodo inicial  
			auxFila->begin=auxElementos; //nuevo primer elemento de la fila
			auxElementos->next=auxElement2; //el nuevo primer elemento apunta al viejo
		}else if(auxElementos->column>auxFila->end->column){ //verifico si va al final 
			auxElement2=auxFila->end; //guardo el puntero hacia el nodo final
			auxFila->end=auxElementos; //nuevo ultimo elemento de la fila
			auxElement2->next=auxElementos; //el viejo ultimo elemento apunta al nuevo 
		}else{ //si no va ni al principio ni al final entonces tengo que recorrer la lista
			for(auxElement2=auxFila->begin, auxElement3=auxFila->begin->next;auxElement3!=NULL;auxElement2=auxElement2->next, auxElement3=auxElement3->next){
			if((auxElementos->column > auxElement2->column)&&(auxElementos->column < auxElement3->column)){
				auxElement2->next=auxElementos; //el limite inf apunta al nuevo elemento
				auxElementos->next=auxElement3; //el nuevo elemnto apunta al limite posterior
				break; //rompo el ciclo
			}
		}
		}

	}
	return auxFila;
}

//verifica si existe la columna en la fila recibida para asignar un elemento
void existeColumnaAsignar(int j, int x, NodeRow *auxFila){
	Node *auxElementos;
	for(auxElementos=auxFila->begin;auxElementos!=NULL;auxElementos=auxElementos->next){
		if(auxElementos->column==j){ //si encuentro la columna
			auxElementos->value=x;
			break; //rompo el ciclo apuntando al nodo actual
		}	
	}
	if(!auxElementos){ //si apunta a nulo entonces no consiguio la columna 
		auxFila=agregarElementoOrdenado(auxFila, crearNode(j,x));
	}
}
//inserta una fila de forma ordenada en la matriz
Array *InsertarFilaOrdenado(Array *M, NodeRow *auxFila){
	
if(!(M->begin)){ //si la matriz no tienen ninguna fila 
        M->begin=M->end=auxFila; //la matriz comienza y termina en la misma nueva fila
	}else{ //si la matriz ya tiene filas
		NodeRow *auxFila2,*auxFila3; //limite inferior y posterior para recorrer la lista de filas
		if(auxFila->row < M->begin->row){ //verifico si va al principio
			auxFila2=M->begin; //guardo el puntero hacia el nodo inicial  
			M->begin=auxFila; //nueva primera fila de la matriz
			auxFila->next=auxFila2; //la nueva primera fila apunta a la vieja 
		}else if(auxFila->row > M->end->row){ //verifico si va al final 
			auxFila2=M->end; //guardo el puntero hacia el nodo final
			M->end=auxFila; //nueva ultima fila de la matriz
			auxFila2->next=auxFila; //la vieja ultima fila apunta a la nueva
		}else{ //si no va ni al principio ni al final entonces tengo que recorrer la lista
			for(auxFila2=M->begin, auxFila3=M->begin->next;auxFila3!=NULL;auxFila2=auxFila2->next, auxFila3=auxFila3->next){
			if((auxFila->row > auxFila2->row)&&(auxFila->row < auxFila3->row)){
				auxFila2->next=auxFila; //el limite inf apunta a la nueva fila
				auxFila->next=auxFila3; //la nueva fila apunta al limite posterior
				break; //rompo el ciclo porque ya no es necesario iterar
			}
		}
		}

	}
	return M;	

}
//verifica si existe la fila en la matriz para asignar el elemento
void existeFilaAsignar(int i, int j, int x, Array *M){
			NodeRow *auxFila;
			for(auxFila=M->begin;auxFila!=NULL;auxFila=auxFila->next){
				if(auxFila->row==i){
					existeColumnaAsignar(j,x, auxFila); //tomo el valor de la fila actual
					break; //rompo el ciclo para guardar la ultima posicion de auxFila
				}
			}	
			if(!auxFila){ //quiere decir que no encontro la fila
				auxFila=crearNodeRow(i); 
				M=InsertarFilaOrdenado(M, auxFila); //agrego la fila en la matriz
				auxFila=agregarElementoFinal(auxFila,crearNode(j,x)); //agrego el elemento en la fila
			}
}

//asigna un elemento x en la fila i en la columna j de la matriz m
void AsignarElemento(int i, int j, int x, Array *M){
	if(x){ //si x es cero o se sale de los limites se retorna la matriz sin modificaciones
		if((i<M->rows) && (j<M->columns) && (i>=0) && (j>=0)){ //si i y j no se salen de los limites de la matriz
			existeFilaAsignar(i,j,x,M);		
		}
	}
}
//funcion que suma dos filas de una matriz y retorna una nueva fila
NodeRow *sumarFilas(NodeRow *auxF1, NodeRow *auxF2){
	NodeRow *filaN=crearNodeRow(auxF1->row); //la fila nueva que se va a retornar
	Node *auxC1=auxF1->begin, *auxC2=auxF2->begin; //auxiliares para recorrer los elementos de las filas F1 y F2
	while(auxC1 && auxC2){ //mientras no sean null
		if(auxC1->column==auxC2->column){ //si las columnas actuales de ambas filas son iguales  
			if(auxC1->value + auxC2->value){ //si la suma es distinto de cero inserto una copia en la misma columna con valor igual a la suma 
				filaN=agregarElementoFinal(filaN,crearNode(auxC1->column,auxC1->value + auxC2->value));
			}//si es cero no agrego nada
			auxC1=auxC1->next;
			auxC2=auxC2->next;
		}else if (auxC1->column<auxC2->column){ //si la columna actual de la fila 1 es menor a la de la fila 2 
			filaN=agregarElementoFinal(filaN,crearNode(auxC1->column,auxC1->value)); //agrego solo una copia del valor de la columna de la fila 1
			auxC1=auxC1->next; //solo cambio de nodo en la fila 1 porque fue el unico que use
		}else{ //si la columna actual de la fila 1 es mayor a la de la fila 2 
			filaN=agregarElementoFinal(filaN,crearNode(auxC2->column,auxC2->value)); //agrego solo una copia del valor de la columna de la fila 2
			auxC2=auxC2->next; //solo cambio de nodo en la fila 2 porque fue el unico que use
		}

	}
		//como no se si llegue al final de la fila 1 o llegue al final de f2 o al mismo tiempo entonces tengo que agregar las restantes si es que hace falta
	    while(auxC1){ //mientras auxC1 no sea NULL
			filaN=agregarElementoFinal(filaN, crearNode(auxC1->column,auxC1->value)); //inserto al final de la fila nueva una copia
			auxC1=auxC1->next;
		}

		while(auxC2){ //mientras auxC2 no sea NULL
			filaN=agregarElementoFinal(filaN, crearNode(auxC2->column,auxC2->value)); //inserto al final de la fila nueva una copia
			auxC2=auxC2->next;
		}
	return filaN;
}

//funcion que devuelve la copia de una fila dada
NodeRow *copiarFila(NodeRow *auxF){
	NodeRow *filaN=crearNodeRow(auxF->row); //fila copia
	Node *auxElementos=auxF->begin; //para recorrer los elementos de la fila
	for(;auxElementos!=NULL;auxElementos=auxElementos->next){
		filaN=agregarElementoFinal(filaN,crearNode(auxElementos->column,auxElementos->value)); //voy copiando cada nodo de la fila dada en la fila copia
	}
	return filaN;
}
//devuelve la matriz resultante al sumar M1 y M2
Array *Sumar(Array *M1, Array *M2){
	if((M1->rows == M2->rows) && (M1->columns == M2->columns)){ //verifica que las matrices tengan dimension iguales
		Array *mNueva=crearArray(M1->rows,M1->columns);
		NodeRow *auxF1=M1->begin, *auxF2=M2->begin; //auxiliares para recorrer las filas de las matrices
		while(auxF1 && auxF2){ //mientras no sean null
			if(auxF1->row==auxF2->row){ //verifico si la fila actual de M1 es igual a la actual de M2
				mNueva=agregarFilaFinal(mNueva,sumarFilas(auxF1,auxF2));
				auxF1=auxF1->next;
				auxF2=auxF2->next;
			}else if(auxF1->row<auxF2->row){ //si la fila actual de M1 es menor que la fila actual de M2 
				mNueva=agregarFilaFinal(mNueva,copiarFila(auxF1));
				auxF1=auxF1->next;//solo avanzo a la siguiente fila de M1 porque falta operar la fila de M2
			}else{ //si la fila actual de M1 es mayor que la fila actual de M2
				mNueva=agregarFilaFinal(mNueva,copiarFila(auxF2)); 
				auxF2=auxF2->next; ////solo avanzo a la siguiente fila de M2 porque falta operar la fila de M1
			}
		}
		//como no se si auxF1 no llego primero a null o fue auxf2 o al mismo tiempo entonces tengo que agregar las restantes si es que hace falta
	    while(auxF1){ //mientras auxF1 no sea NULL
			mNueva=agregarFilaFinal(mNueva, copiarFila(auxF1)); //inserto al final de la matriz una copia
			auxF1=auxF1->next;
		}
		while(auxF2){ //mientras auxF2 no sea NULL
			mNueva=agregarFilaFinal(mNueva, copiarFila(auxF2)); //inserto al final de la matriz una copia
			auxF2=auxF2->next;
		}
		return mNueva;
	}
	printf("No se pueden sumar matrices de distintas dimensiones\n");
	return NULL; //no se pueden sumar dos matrices con dimensiones diferentes
}
//crea la matriz con datos recibidos del terminal
Array *leerMatrizTerminal(){
	int n, m, i, j, e;
	printf("Ingrese el numero de filas y de columnas de la matriz\n");
	scanf("%i %i", &n, &m);
	Array *newArray=crearArray(n,m); //se crea la cabeza del array
	NodeRow *auxFila; //se crea una variable donde se iran almacenando los elementos de la fila actual para despues almacenarlos en la la matriz
	//empiezo a pedir los elementos del array
	for(i=0;i<n;i++){
		auxFila=crearNodeRow(i); //creo la fila actual
		for(j=0;j<m;j++){
			printf("Ingrese el elemento de la fila %i y la columna %i de la matriz\n", i, j);
			scanf("%i", &e);
			if(e){
				if(!auxFila->begin){ //verifico si es la primera vez que crea la fila
					auxFila=crearNodeRow(i); //creo la fila actual
				}
				auxFila=agregarElementoFinal(auxFila, crearNode(j,e)); //almaceno un elemento en la fila actual 
			}
		}
		if(auxFila->begin){ //verifico que la fila haya sido creada
			newArray=agregarFilaFinal(newArray,auxFila); //agrego la nueva fila a la matriz
	    }
	}
	return newArray;
}
// Funcion para agregar un nuevo elemento a una matriz
Array *nuevo_elemento(Array *M, int row, int column, int value) {
    if (M->begin == NULL) {     // Si la matriz esta vacia
    	// Se crea un nuevo elemento y una nueva fila
    	// El elemento es asignado al puntero 'begin' y 'end' de la fila
    	// La fila es asignada al puntero 'begin' y 'end' de la matriz
        Node *element = crearNode(column, value);
        NodeRow *new_row = crearNodeRow(row);
        new_row->begin = new_row->end = element;
        M->begin = M->end = new_row;

		// Se retorna la matriz
        return M;
    }

    NodeRow *rows = M->begin;
    NodeRow *prev_row = NULL;
    // Se recorre la lista de filas mientras la fila recibida en la funcion sea mayor o igual al indice de la fila actual
    while (rows != NULL && row >= rows->row) {
        if (rows->row == row) {		// Si la fila actual es la que se recibio en la funcion
            prev_row = rows;
            break;
        }
        
        // Se almacena la fila actual en una variable auxiliar y se pasa a la siguiente fila
        prev_row = rows;
        rows = rows->next;
    }
    
    // Si la variable auxiliar es igual a NULL, se inserta una fila al inicio de la lista de filas
    if (prev_row == NULL) {
        Node *element = crearNode(column, value);
        NodeRow *new_row = crearNodeRow(row);
        new_row->begin = new_row->end = element;
        new_row->next = rows;
        M->begin = new_row;
    } else if (prev_row->row != row) {  // Si el indice de prev_row es distinto de la fila recibida en la funcion
        // Se crea una nueva fila con el nuevo elemento y se agrega en una posicion X de la lista
        Node *element = crearNode(column, value);
        NodeRow *new_row = crearNodeRow(row);
        new_row->begin = new_row->end = element;
        new_row->next = rows;
        prev_row->next = new_row;
    } else if (rows == NULL) {	// Si se recorrio toda la lista de filas hasta el final
    	// Se inserta una nueva fila con el nuevo elemento al final de la lista de filas
        Node *element = crearNode(column, value);
        NodeRow *new_row = crearNodeRow(row);
        new_row->begin = new_row->end = element;
        prev_row->next = new_row;
        M->end = new_row;
    } else {
    	// Si la fila no tiene columnas, se agrega el nuevo elemento
        if (prev_row->begin == NULL) {
            Node *element = crearNode(column, value);
            prev_row->begin = prev_row->end = element;

            return M;
        }  

        Node *elements = prev_row->begin;
        Node *prev_element = NULL;
        // Se recorre la lista de columnas mientras la columna recibida en la funcion sea mayor o igual al indice de la columna actual
        while (elements != NULL && column >= elements->column) {
            if (elements->column == column) {	// Si se encuentra una coincidencia
                printf("El elemento ya existe dentro de la matriz\n");
                return M;
            }
            
            prev_element = elements;
            elements = elements->next;
        }

		// Se inserta el elemento al inicio de la lista
        if (prev_element == NULL) {
            Node *element = crearNode(column, value);
            element->next = elements;

            prev_row->begin = element;
        } else {	// Se inserta el elemento en una posicion X de la lista
            Node *element = crearNode(column, value);
            element->next = elements;

            prev_element->next = element;
        }

        if (elements == NULL) {		// Se inserta el elemento al final de la lista
            Node *element = crearNode(column, value);
            prev_row->end = element;
        }
    } 

    return M;
}

//crea la matriz leida por un archivo de texto
Array *leerMatrizArchivo(){
	Array* newArray;
	int rows,columns, fi,ci,vi; //variables para copiar los distintos datos del archivo  
	char ruta[100];
	FILE *archivo; //creo el archivo
	printf("Ingrese la ruta del archivo de texto\n");
	scanf("%s", ruta);
	archivo=fopen("archivo2.txt", "rb"); //le doy una ruta y el modo (rb:archivo binario para lectura)
	if(!archivo){ // si el archivo es null
		printf("Error en la apertura del archivo\n");
		return NULL;
	}else{
		fscanf(archivo, "%i %i", &rows,&columns); //leo la cantidad de filas y columnas de la matriz
		newArray=crearArray(rows,columns); //se crea la cabeza del array
		while(!feof(archivo)){ //la funcion feof indica cuando el archivo finaliza
			fscanf(archivo, "%i %i %i", &fi, &ci, &vi);//leo fila columna y valor 
			newArray=nuevo_elemento(newArray, fi, ci, vi);
		}
		
	}
	fclose(archivo); //cierro el archivo
	return newArray;
}


//Crear una matriz nueva
Array *crearMatriz(){
	int opc;
	printf("Ingrese la forma en la que desea ingresar la matriz\n\n");
	printf("    Ingrese '0' para leer los datos de la matriz de un archivo de texto\n");
	printf("    Ingrese '1' para leer los datos de la matriz por terminal\n");
	scanf("%i", &opc);
	if(opc==0){
		return leerMatrizArchivo();
	}else if(opc==1){
		return leerMatrizTerminal();
	}else{
		return NULL; //no es una opcion valida
	}

}

// Funcion utilizada para multiplicar todos los valores de la matriz por un numero e
Array *productoPorEscalar(int e, Array *M) {
    NodeRow *rows = M->begin;

    // Se recorre la lista de filas de la matriz
    while (rows != NULL) {
        Node *element = rows->begin;

        // Se recorren los elementos de la fila actual
        while (element != NULL) {
            element->value *= e;    // Se multiplica el elemento actual por el escalar
            element = element->next;    // Se pasa al siguiente elemento
        }

        rows = rows->next;
    }
    
    return M;
}

// Sumar a un elemento de la matriz un numero
Array *sumar_fila_columna(Array *M, int row, int column, int value) {
    NodeRow *rows = M->begin;

    // Recorrer la lista de filas hasta encontrar la fila indicada
    while (rows != NULL && row >= rows->row) {
        if (rows->row == row) {     // Si se encuentra la fila
            Node *element = rows->begin;
            // Recorrer la lista de columnas hasta encontrar la columna indicada
            while (element != NULL && column >= element->column) {
                if (element->column == column) {    // Si se encuentra la columna dentro de la fila
                    element->value += value;    // Se le suma el nuevo valor al valor anterior
                    return M;
                }

                element = element->next;
            }

            // Si la columna no existe dentro de la fila se detiene la ejecucion del ciclo
            break;
        }        

        rows = rows->next;
    }

    // Si la fila o la columna no existen dentro de la matriz, se agrega como nuevo elemento
    return nuevo_elemento(M, row, column, value);
}

// Multiplicacion de dos matrices
Array *multiplicacion(Array *M1, Array *M2) {
    // Si el numero de columnas de M1 no es igual al numero de filas de M2
    if (M1->columns != M2->rows){
		printf("No se pueden multiplicar las matrices\n porque la cantidad de columnas de la primera matriz es distinta de las cantidad de filas de la segunda matriz\n");
		return NULL;
	}
        

    // Se crea la matriz resultante
    // El numero de filas es igual al numero de filas de M1
    // El numero de columnas es igual al numero de columnas de M2
    Array *new_M =crearArray(M1->rows, M2->columns);

    NodeRow *M1_rows = M1->begin;
    int value;
    while (M1_rows != NULL) {
        Node *element = M1_rows->begin;
        value = 0;

        while (element != NULL) {
            NodeRow *M2_rows = M2->begin;

            // Se recorre la lista de filas de M2
            while (M2_rows != NULL) {
                // Si el numero de la fila actual es igual al numero de la columna actual
                if (element->column == M2_rows->row) {
                    if (M2_rows->begin != NULL) {
                        Node *M2_element = M2_rows->begin;

                        while (M2_element != NULL) {
                            value = element->value * M2_element->value;

                            // Si el producto es mayor que 0, se modifica el elemento en la posicion actual
                            // La posicion actual esta dada por la fila actual de M1 y la columna actual del elemento de M2
                            if (value != 0) {
                                new_M = sumar_fila_columna(new_M, M1_rows->row, M2_element->column, value);
                            }

                            M2_element = M2_element->next;
                        }
                    }
                }

                M2_rows = M2_rows->next;
            }

            element = element->next;
        }

        M1_rows = M1_rows->next;
    }

    return new_M;
}

// Genera la transpuesta de la matriz recibida
Array *transpuesta(Array *M) {
    if (M->begin == NULL)   // Si la matriz no tiene ningun elemento
        return M;
    
    // Se crea una nueva matriz
    // El numero de filas de la nueva matriz es el numero de columnas de la matriz a transponer
    // El numero de columnas de la nueva matriz es el numero de filas de la matriz a transponer
    Array *new_M = crearArray(M->rows, M->columns);
    NodeRow *rows = M->begin;

    while (rows != NULL) {  // Se recorre la lista de filas de la matriz
        Node *element = rows->begin;

        while (element != NULL) {   // Se recorre la lista de columnas de cada fila
            // Se inserta en la nueva matriz el elemento en la nueva posicion
            new_M = nuevo_elemento(new_M, element->column, rows->row, element->value);
            element = element->next;
        }

        rows = rows->next;
    }

    return new_M;
}

// Imprimir la matriz (incluyendo los 0)
void imprimir(Array *M) {
    if (M->begin == NULL) {
        printf("La matriz esta vacia!\n");
        return;
    }
    
    NodeRow *rows = M->begin;
    int i, j, k, m, n;

    i = 0;
    while (i < M->rows) {
        if (rows == NULL) {
            for (m = i; m < M->rows; m++) {
                for (n = 0; n < M->columns; n++)
                    printf("0 ");
                
                printf("\n");
            }
            return;
        } else if (i == rows->row) {
            Node *element = rows->begin;
        
            j = 0;
            while (j < M->columns) {
                if (element == NULL) {
                    for (k = j; k < M->columns; k++)
                        printf("0 ");

                    printf("\n");
                    
                    break;
                } else if (j == element->column) {
                    printf("%d ", element->value);
                    
                    j++;
                    element = element->next;

                    if (j == M->columns)
                        printf("\n");
                } else {
                    for (k = j; k < element->column; k++)
                        printf("0 ");

                    j = element->column;
                }
            }

            i++;
            rows = rows->next;
        } else {
            for (m = i; m < rows->row; m++) {
                for (n = 0; n < M->columns; n++)
                    printf("0 ");

                printf("\n");
            }
            i = rows->row;
        }        
    }
}

void imprimirMatrizArchivo(Array *matriz){
	char ruta[40];
	printf("Ingrese la ruta del archivo de texto\n");
	scanf("%s", &ruta);
	FILE *archivo=fopen(ruta, "w"); //creo y abro el archivo con la ruta dada con el modo de escritura
	if(!archivo){ //por si el disco esta protegido contra escritura o esta lleno
		printf("Error en la creacion del archivo\n\n");
	}else{
		NodeRow *auxFila; //para recorrer las filas
		Node *auxElementos; //para recorrer los elementos de la fila actual
	    fprintf(archivo, "%i %i\n", matriz->rows, matriz->columns);
	    for(auxFila=matriz->begin;auxFila!=NULL;auxFila=auxFila->next){ //recorro la primera fila de la matriz hasta la ultima 
		    for(auxElementos=auxFila->begin;auxElementos!=NULL;auxElementos=auxElementos->next){ //recorro el primer elemento de la fila hasta a la ultima 
			   fprintf(archivo, "%i %i %i\n",auxFila->row, auxElementos->column, auxElementos->value);
		    }
	    }
	}
	fclose(archivo);
}
