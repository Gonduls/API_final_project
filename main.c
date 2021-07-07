#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUM_LEN 10
#define HI printf("hi\n");
#define a_capo printf("\n");

typedef struct {
    unsigned posizione;
    unsigned somma;
} papabile;

typedef struct {
    papabile* array;
    unsigned riempimento;
} migliori;

void print_top(migliori* lista);
void dijkstra(unsigned *matrix, char* line, int dim, unsigned posizione);
void input_matrix(unsigned *matrix, char* line, int dim);


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

    while(fgets(line, MAX_LINE_LEN, stdin) != NULL){
        //printf("%s", line);
        //printf("top: %d, aggiungi: %d\n", strcmp(line, topk), strcmp(line, aggiungi));
        if(strcmp(line, aggiungi) == 0){
            //dijkstra(grafo, line, D, i);
            input_matrix(grafo[0], line, D);
            for(int j = 0; j< D; j++)
                for(int k = 0; k< D-1; k++)
                    printf("%u, ", grafo[j][k]);
            a_capo
            i ++;
            continue;
        }
        if(strcmp(line, topk) == 0){
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


void print_top(migliori* lista){
    unsigned i;
    if (lista->riempimento == 0){
        printf("\n");
        return;
    }
    printf("%u", lista->array->posizione);

    for(i = 1; i< lista->riempimento; i++)
        printf(" %u", lista->array[i].posizione);
}

void dijkstra(unsigned *matrix, char* line, int dim, unsigned posizione){
    //unsigned i;

}