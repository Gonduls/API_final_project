#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUM_LEN 10
#define HI printf("hi\n");
#define capo printf("\n");

typedef struct {
    unsigned posizione;
    unsigned valore;
} doppio;

typedef struct {
    doppio* array;
    unsigned riempimento;
} lista_sequenziale;

void print_top(lista_sequenziale* lista);
unsigned dijkstra(unsigned *matrix, char* line, int dim);
void input_matrix(unsigned *matrix, char* line, int dim);
void build_heap(lista_sequenziale* lista, bool MAX);
void max_heapify(lista_sequenziale* lista, unsigned position);
void min_heapify(lista_sequenziale* lista, unsigned position);



int main(){
    int D, K;
    if(scanf("%i %i\n", &D, &K) != 2){
        printf("Failed to get input, closing program\n");
        return 1;
    }

    unsigned MAX_LINE_LEN = (unsigned) D*(MAX_NUM_LEN + 1);
    char line[MAX_LINE_LEN];
    unsigned grafo[D][D - 1];
    char* aggiungi = "AggiungiGrafo\n", *topk = "TopK\n";
    unsigned i = 0;
    doppio best[K];
    lista_sequenziale heap;
    heap.array = best;
    heap.riempimento = 0;

    while(fgets(line, MAX_LINE_LEN, stdin) != NULL){
        if(strcmp(line, aggiungi) == 0){
            input_matrix(grafo[0], line, D);
            //dijkstra(grafo, line, D, i);
            i ++;
            continue;
        }
        if(strcmp(line, topk) == 0){
            print_top(&heap);
            continue;
        }
        printf("\terrore\n");
    }
    return 0;
}

void input_matrix(unsigned *matrix, char* line, int dim){
    int i, j, row;
    unsigned MAX_LINE_LEN = dim*(MAX_NUM_LEN + 1);
    char *token;
    for (i= 0; i < dim; i++){

        if(fgets(line, MAX_LINE_LEN, stdin) != NULL){
            token = strtok(line, ","); // non mi serve il primo numero di ogni riga: è la distanza verso il nodo 0, inutile
            j = 0;
            row = i*(dim-1);
            while(token != NULL && j<dim-1){
                token = strtok(NULL, ",");
                matrix[row + j] = atoi(token);
                j++;
            }
        }
        else
            printf("errore 2\n");
    }
}


void print_top(lista_sequenziale* lista){
    unsigned i;
    if (lista->riempimento == 0){
        capo
        return;
    }
    printf("%u", lista->array->posizione);

    for(i = 1; i< lista->riempimento; i++)
        printf(" %u", lista->array[i].posizione);
    capo
}

void build_heap(lista_sequenziale* lista, bool MAX){
    unsigned i;
    for(i = lista->riempimento/2; i>0; i--){
        if(MAX)
            max_heapify(lista, i);
        else
            min_heapify(lista, i);
    }
}

void max_heapify(lista_sequenziale* lista, unsigned position){
    // sorts by higher valore, if vaolres match then it prefers higher posiziones
    unsigned left, right, pos, max;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;
    if(left < lista->riempimento && (lista->array[pos].valore < lista->array[left].valore || (lista->array[pos].valore == lista->array[left].valore && lista->array[pos].posizione < lista->array[left].posizione)))
        max = left;
    else
        max = pos;

    if(right < lista->riempimento && (lista->array[max].valore < lista->array[right].valore || (lista->array[max].valore == lista->array[right].valore && lista->array[max].posizione < lista->array[right].posizione)))
        max = right;
    
    if(max != pos){
        temp = lista->array[max];
        lista->array[max] = lista->array[pos];
        lista->array[pos] = temp;
        max_heapify(lista, max+1);
    }
    
}

void min_heapify(lista_sequenziale* lista, unsigned position){
    // sorts by lower valore, if vaolres match then it prefers lower posiziones
    unsigned left, right, pos, min;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;
    if(left < lista->riempimento && (lista->array[pos].valore > lista->array[left].valore || (lista->array[pos].valore == lista->array[left].valore && lista->array[pos].posizione > lista->array[left].posizione)))
        min = left;
    else
        min = pos;

    if(right < lista->riempimento && (lista->array[min].valore > lista->array[right].valore || (lista->array[min].valore == lista->array[right].valore && lista->array[min].posizione > lista->array[right].posizione)))
        min = right;
    
    if(min != pos){
        temp = lista->array[min];
        lista->array[min] = lista->array[pos];
        lista->array[pos] = temp;
        min_heapify(lista, min+1);
    }
    
}

unsigned dijkstra(unsigned *matrix, char* line, int dim){
    //unsigned i;
    return 0;
}