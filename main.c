#include "string.h"
#include <stdio.h>
#include <stdlib.h>

/** Data type definitions */
typedef struct _node {
    int value;
    struct _node *next;
} _Node;

typedef _Node * Nodo;
typedef _Node * _Pila;
typedef _Node ** Pila;

/** Method prototypes **/
Pila stackinit(Pila s);
void push(Pila s, int v);
Nodo pop(Pila pila);
Nodo top(Pila s);

int empty(_Pila s);
int count(_Pila s);

void flushstack(Pila s);
void showall(_Pila s);

int main(int argc, char const *argv[]) {
    _Pila stack;
    Pila sp = stackinit(&stack);
    FILE * archivo;
    int linea = 0;
    int pc = 0, pa = 0, cc = 0, ca = 0, lc = 0, la = 0;
    char simbolo;
    Nodo aux;

    archivo = fopen("expr.txt", "r");
    simbolo = fgetc(archivo);


    while (simbolo != EOF) {

        if(simbolo == '\n'){
            linea++;
            simbolo = fgetc(archivo);
            continue;
        }

        switch (simbolo) {
            case '(':
                push(sp, 0);
                break;
            case '[':
                push(sp, 1);
                break;
            case '{':
                push(sp, 2);
                break;
            case ')':
                if(top(sp) != NULL) {
                    if(pop(sp)->value != 0) {
                        pa++;
                    }
                }
                break;
            case ']':
                if(top(sp) != NULL) {
                    if(pop(sp)->value != 1) {
                        ca++;
                    }
                }
                break;
            case '}':
                if(top(sp) != NULL) {
                    if(pop(sp)->value != 2) {
                        la++;
                    }
                }
                break;
        }

        simbolo = fgetc(archivo);
    }

    if(empty(stack) && pa == 0 && ca == 0 && la == 0){
        printf("\nLa expresion se evaluo correctamente, no se encontraron errores.\n");
    } else {
        aux = pop(sp);
        while (aux != NULL) {
            switch (aux->value) {
                case 0:
                    pc++;
                    break;
                case 1:
                    cc++;
                    break;
                case 2:
                    lc++;
                    break;
            }
            aux = pop(sp);
        }
        printf("\nSE ENCONTRARON %d ERRORES:\n", pc + pa);
        if(pc > 0)
            printf("  - Hacen falta %d parentesis de cierre\n", pc);
        if(pa > 0)
            printf("  - Hacen falta %d parentesis de apertura\n", pa);
        if(cc > 0)
            printf("  - Hacen falta %d corchetes de cierre\n", cc);
        if(ca > 0)
            printf("  - Hacen falta %d corchetes de apertura\n", ca);
        if(lc > 0)
            printf("  - Hacen falta %d llaves de cierre\n", lc);
        if(la > 0)
            printf("  - Hacen falta %d llaves de apertura\n", la);
    }

    return 0;
}

/**
	* Initializes a given Stack
	*/
Pila stackinit(Pila stack){
    *stack = NULL;
    return stack;
}

/**
	* Inserts a node to the end of the stack
	*/
void push(Pila stack, int v)
{
    Nodo newnode;
    newnode = (Nodo)malloc(sizeof(_Node));
    newnode->value = v;

    newnode->next = *stack;
    *stack = newnode;
}

Nodo pop(Pila pila)
{
    if(empty(*pila)){
        return NULL;
    }
    else
    {
        Nodo aux = *pila;
        *pila = aux->next;
        return aux;
    }
}

Nodo top(Pila stack)
{
    return *stack;
}

/**
	* Checks if the stack is empty
	*/
int empty(_Pila stack)
{
    if(stack == NULL)
    {
        return 1;
    }
    return 0;
}

int count(_Pila stack)
{
    Nodo aux;
    aux = stack;
    int i = 0;
    while (aux)
    {
        aux = aux->next;
        i++;
    }
    return i;
}

/**
	* Removes all elements in the stack
	*/
void flushstack(Pila stack)
{
    Nodo node;

    while(*stack)
    {
        node = *stack;
        *stack = node->next;
        free(node);
    }
}

/**
	* Prints to stdout all nodes, indicating its HEX RAM address
	*/
void showall(_Pila stack)
{
    Nodo node = stack;

    if(empty(stack))
    {
        printf("Pila vacia\n");
    }
    else
    {
        int i = 0;
        while(node)
        {
            printf("Nodo #%d en RAM{%p}: %d\n", i, node, node->value);
            node = node->next;
            i++;
        }
        printf("\n");
    }
}
