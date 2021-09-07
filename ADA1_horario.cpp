#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha
{   
	int hora;
	int minuto;
};

struct Asignatura
{
	char *nombreAsignatura;
	int diaSemana;
	Fecha *horarioEntrada;
	Fecha *horarioSalida;
	struct Asignatura *next;
};

typedef struct Asignatura Asignatura;
typedef struct Fecha Fecha;
//funciones
void cabecera(void);
void insertarUltima(Asignatura **first, Asignatura *second);
void InsertarInicio(Asignatura** inicioLista, Asignatura* new_node);
void InsertarResto(Asignatura** inicioLista, Asignatura* new_node);
void ordenarDia(Asignatura** inicioLista, Asignatura* new_node);
Asignatura* newAsignatura();
void imprimir(Asignatura* head);
void agregar(Asignatura *head);
Asignatura* entradadeControl(Asignatura *head);

//cabecera
void cabecera(void)
{
	printf("	Horario\n");
	printf("***********************\n");
	return;
}

//Se agrega en la parte final de la lista
void insertarUltima(Asignatura **first, Asignatura *second)
{
	Asignatura *lista=*first;
	if(*first == NULL)
	{
		*first = second;
	}else{
		while (lista->next !=NULL)
		{
			lista = lista->next;
		}
		lista->next=second;
	}
}


//Se agrega en la mitad/resto de la lista
void InsertarResto(Asignatura** inicioLista, Asignatura* new_node)
{
	Asignatura* actual;
	actual = *inicioLista;
	
	while(actual-> next !=NULL && actual->next->diaSemana < new_node->diaSemana) {
		actual = actual->next;
	}
	
	new_node->next = actual->next;
	actual->next = new_node;
}
//Se agrega en el inicio de la lista
void InsertarInicio(Asignatura** inicioLista, Asignatura* new_node)
{
	new_node->next = *inicioLista;
	*inicioLista=new_node;
}


//orden ascendente
void ordenarDia(Asignatura** inicioLista, Asignatura* new_node)
{
	if(*inicioLista == NULL || (*inicioLista)->diaSemana>= new_node->diaSemana){
		InsertarInicio(inicioLista, new_node);
	}
	else{
		InsertarResto(inicioLista, new_node);
	}
}

Asignatura* newAsignatura()
{
	Asignatura* new_node = (Asignatura*)malloc(sizeof(Asignatura));
	
	return new_node;
}

//Se pide la informacion
void agregar(Asignatura *head)
{
	Asignatura *currentNode;
	currentNode = head;
	char nombre[50];
	system("cls");
	cabecera();
	printf("\nNombre de la asignatura: ");
	fflush(stdin);
	scanf("%s", nombre);
	fflush(stdin);
	currentNode->nombreAsignatura = (char *)malloc(sizeof(char)*(strlen(nombre)));
	strcpy(currentNode->nombreAsignatura,nombre);
	printf("Ingrese el dia de la semana: ");
	scanf("%d", &currentNode->diaSemana);
	currentNode->horarioEntrada=(Fecha *)malloc(sizeof(Fecha));
	printf("Hora de entrada: ");
	scanf("%d", &currentNode->horarioEntrada->hora);
	printf("Minutos de entrada: ");
	scanf("%d", &currentNode->horarioEntrada->minuto);
	currentNode->horarioSalida = (Fecha *)malloc(sizeof(Fecha));
	printf("Hora de salida: ");
	scanf("%d", &currentNode->horarioSalida->hora);
	printf("Minutos de salida: ");
	scanf("%d", &currentNode->horarioSalida->minuto);
	currentNode->next = NULL;

}
void imprimir(Asignatura* head)
{
	//Se imprime el horario en orden
	system("cls");
	cabecera();
	Asignatura* lista = head;
	while (lista !=NULL){//comprobar que no sea nula
		printf("\nAsignatura: %s", lista->nombreAsignatura);
		printf("\nDia de la semana: %d", lista->diaSemana);
		printf("\nHora de entrada: %d:%d", lista->horarioEntrada->hora, lista->horarioEntrada->minuto);
		printf("\nHora de salida: %d:%d\n", lista->horarioSalida->hora, lista->horarioSalida->minuto);
		lista=lista->next;
	}
}

Asignatura* entradadeControl(Asignatura *head)
{
	//Se valida si se desea agregar otra Asignatura
	Asignatura* new_node = newAsignatura();
	
	char respuesta='s';
	
	while(respuesta=='s')
	{
		new_node = newAsignatura();
		agregar(new_node);
		ordenarDia(&head, new_node);
		printf("\nDesea agregar una Asignatura? s/n: ");
		scanf("%s", &respuesta);
	}
	return head;
}

int main() {
	Asignatura* head=NULL;
	head=entradadeControl(head);
	
	imprimir(head);
	return 0;
}


