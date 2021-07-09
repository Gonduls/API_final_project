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
} migliori;

void print_top(migliori* lista);
unsigned dijkstra(unsigned *matrix, char* line, int dim);
void input_matrix(unsigned *matrix, char* line, int dim);
void build_heap(doppio* array, unsigned dim, bool MAX);
void max_heapify(doppio* array, unsigned position, unsigned dim);
void min_heapify(doppio* array, unsigned position, unsigned dim);



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
    migliori heap;
    heap.array = best;
    heap.riempimento = 0;

    while(fgets(line, MAX_LINE_LEN, stdin) != NULL){
        //printf("%s", line);
        //printf("top: %d, aggiungi: %d\n", strcmp(line, topk), strcmp(line, aggiungi));
        if(strcmp(line, aggiungi) == 0){
            //dijkstra(grafo, line, D, i);
            input_matrix(grafo[0], line, D);
            //for(int j = 0; j< D; j++)
            //    for(int k = 0; k< D-1; k++)
            //        printf("%u, ", grafo[j][k]);
            //capo
            
            i ++;
            continue;
        }
        if(strcmp(line, topk) == 0){
            continue;
        }
        print_top(&heap);
        printf("\terrore\n");
    }
    doppio array[25];
    for (i = 0; i<25; i++){
        array[i].posizione = i;
        array[i].valore = i;
    }
    migliori boh;
    boh.array = array;
    boh.riempimento = 20;
    print_top(&boh);
    build_heap(array, 25, true);
    print_top(&boh);
    build_heap(array, 25, false);
    print_top(&boh);
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


void print_top(migliori* lista){
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

void build_heap(doppio* array, unsigned dim, bool MAX){
    unsigned i;
    for(i = dim/2; i>0; i--){
        if(MAX)
            max_heapify(array, i, dim);
        else
            min_heapify(array, i, dim);
    }
}

void max_heapify(doppio* array, unsigned position, unsigned dim){
    unsigned left, right, pos, max;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;
    if(left < dim && (!array[pos].valore || array[pos].valore < array[left].valore || (array[pos].valore == array[left].valore && array[pos].posizione > array[left].posizione)))
        max = left;
    else
        max = pos;

    if(right < dim && (!array[max].valore || array[max].valore < array[right].valore || (array[max].valore == array[right].valore && array[max].posizione > array[right].posizione)))
        max = right;
    
    if(max != pos){
        temp = array[max];
        array[max] = array[pos];
        array[pos] = temp;
        max_heapify(array, max+1, dim);
    }
    
}

void min_heapify(doppio* array, unsigned position, unsigned dim){
    unsigned left, right, pos, min;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;
    if(left < dim && array[left].valore && (!array[pos].valore || array[pos].valore > array[left].valore || (array[pos].valore == array[left].valore && array[pos].posizione > array[left].posizione)))
        min = left;
    else
        min = pos;

    if(right < dim && array[right].valore && (!array[min].valore || array[min].valore > array[right].valore || (array[min].valore == array[right].valore && array[min].posizione > array[right].posizione)))
        min = right;
    
    if(min != pos){
        temp = array[min];
        array[min] = array[pos];
        array[pos] = temp;
        min_heapify(array, min+1, dim);
    }
    
}

unsigned dijkstra(unsigned *matrix, char* line, int dim){
    //unsigned i;
    return 0;
}