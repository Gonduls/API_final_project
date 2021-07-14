#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUM_LEN 10

typedef struct {
    unsigned posizione;
    unsigned valore;
} doppio;

typedef struct {
    doppio* array;
    unsigned riempimento;
} lista_sequenziale;

void print_top(lista_sequenziale* lista);
unsigned dijkstra(unsigned *matrix, int dim);
void input_matrix(unsigned *matrix, char* line, int dim);
void build_heap(lista_sequenziale* lista, bool MAX);
void max_heapify(lista_sequenziale* lista, unsigned position);
void min_heapify(lista_sequenziale* lista, unsigned position);
void gestisci_top(lista_sequenziale* lista, unsigned new, unsigned position, unsigned dim);



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
            gestisci_top(&heap, dijkstra(grafo[0], D - 1), i, K);
            //printf("i=%u\n", i);
            i ++;
            continue;
        }
        if(strcmp(line, topk) == 0){
            print_top(&heap);
            continue;
        }
        printf("errore: lettura riga non valida\n");
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
        printf("\n");
        return;
    }
    printf("%u", lista->array->posizione);

    for(i = 1; i< lista->riempimento; i++)
        printf(" %u", lista->array[i].posizione);
    printf("\n");
}

void build_heap(lista_sequenziale* lista, bool MAX){
    unsigned i;
    if(lista->riempimento <= 1)
        return;

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
    // sorts by lower valore, leaving 0 at the end
    unsigned left, right, pos, min;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;
    if(left < lista->riempimento && lista->array[left].valore && (!lista->array[pos].valore || lista->array[pos].valore > lista->array[left].valore))
        min = left;
    else
        min = pos;

    if(right < lista->riempimento && lista->array[right].valore && (!lista->array[min].valore || lista->array[min].valore > lista->array[right].valore ))
        min = right;
    
    //printf("pa: %u, left: %u, right: %u, min: %u\n", lista->array[pos].valore, lista->array[left].valore, lista->array[right].valore, lista->array[min].valore);
    
    if(min != pos){
        temp = lista->array[min];
        lista->array[min] = lista->array[pos];
        lista->array[pos] = temp;
        min_heapify(lista, min+1);
    }
    
}

unsigned dijkstra(unsigned *matrix, int dim){
    unsigned i, j, result, row, new_val;
    doppio to_add[dim];
    //unsigned added[dim];
    lista_sequenziale percorsi;

    for ( i = 0; i < dim; i++){
        //added[i] = 0;
        to_add[i].posizione = i;
        to_add[i].valore = matrix[i];
        //printf("%u\t", matrix[i]);
    }
    percorsi.array = to_add;
    percorsi.riempimento = dim;
    
    build_heap(&percorsi, false);

    result = 0;
    for (i = 0; i< dim; i++ ){
        //printf("val = %u\n", to_add[i].valore);

        if(to_add[i].valore == 0){
            //printf("non raggiungibile\n");
            break;
        }
        
        //added[to_add[i].posizione] = to_add[i].valore;
        row = (to_add[i].posizione + 1)* dim;   // calcolo valore utile per navigazione matrice
        percorsi.riempimento --;                // inizializzo parametri per min_heapify
        percorsi.array = percorsi.array + 1;    // sposto puntatore
        result += to_add[i].valore;             // aggiungo percorso trovato al risultato

        for (j = 0; j<percorsi.riempimento; j++){
            new_val = matrix[percorsi.array[j].posizione + row] + to_add[i].valore;

            if(matrix[percorsi.array[j].posizione + row] && (new_val < percorsi.array[j].valore || percorsi.array[j].valore == 0))
                percorsi.array[j].valore = new_val;
            
            //print_top(&percorsi);
        }
        build_heap(&percorsi, false);
    }
    
    //printf("result = %u\n", result);
    return result;
}

void gestisci_top(lista_sequenziale* lista, unsigned new, unsigned position, unsigned dim){
    if(lista->riempimento <= dim - 1){
        lista->array[lista->riempimento].valore = new;
        lista->array[lista->riempimento].posizione = position;
        lista->riempimento ++;

        if(lista->riempimento == dim)
            build_heap(lista, true);
    
        return;
    }

    if(new < lista->array->valore){
        lista->array->valore = new;
        lista->array->posizione = position;
        max_heapify(lista, 1);
    }
}