#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LEN 15

typedef struct {
    unsigned posizione;
    unsigned valore;
} doppio;

typedef struct {
    doppio* array;
    unsigned riempimento;
} lista_sequenziale;

void input_matrix(unsigned *matrix, int dim);
unsigned dijkstra(unsigned *matrix, int dim);
void print_top(lista_sequenziale* lista);
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

    char line[MAX_LINE_LEN];    // può contenere al massimo la stringa 'Aggiungigrafo\n\0'
    unsigned grafo[D][D - 1];
    unsigned i = 0;
    doppio best[K];
    lista_sequenziale heap;     // uso un max-heap per contenere le metriche dei grafi migliori e la loro posizione (da stampare)
    heap.array = best;
    heap.riempimento = 0;       // tiene traccia di quanti elementi liberi ci sono nell'array (lista sequenziale)

    // uso fgets per leggere aggiunfigrafo e topk, principalmente per pigrizia: non incide tanto sulla velocità finale
    while(fgets(line, MAX_LINE_LEN, stdin) != NULL){

        if(strcmp(line, "AggiungiGrafo\n") == 0){

            input_matrix(grafo[0], D);
            gestisci_top(&heap, dijkstra(grafo[0], D - 1), i, K);
            i ++;
            continue;
        }

        if(strcmp(line, "TopK\n") == 0){

            print_top(&heap);
            continue;
        }

        printf("errore: lettura riga non valida\n");
    }

    return 0;
}

void input_matrix(unsigned *matrix, int dim){
    int i, j, row;
    unsigned number = 0;
    char digit;
    for (i= 0; i < dim; i++){
        // non mi serve il primo numero di ogni riga: è la distanza verso il nodo 0, inutile
        do
            digit = getchar_unlocked();
        while(digit != ',');

        // calcolo una sola volta il parametro row, per inserire con efficacia i numeri nella matrice
        row = i*(dim-1);
        j = 0;

        do{

            digit = getchar_unlocked();
            if(digit == ','){
                matrix[row + j] = number;
                j++;
                number = 0;
                continue;
            }

            if(digit >= '0' && digit <= '9')
                number = number * 10 + (unsigned) (digit - '0');

        }    
        while(digit != '\n');
        matrix[row + j] = number;
        number = 0;

    }
}


void print_top(lista_sequenziale* lista){
    unsigned i;

    // uso le printf invece dei putchar() di nuovo per pigrizia, c'è margine di miglioramento temporale
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
    // direttamente dagli appunti di api
    unsigned i;

    if(lista->riempimento <= 1)
        return;

    // max_heapify e min_heapify si comportano in modo diverso, per il diverso comportamento con gli 0
    for(i = lista->riempimento/2; i>0; i--){
        if(MAX)
            max_heapify(lista, i);
        else
            min_heapify(lista, i);
    }
}

void max_heapify(lista_sequenziale* lista, unsigned position){
    // direttamente dagli appunti di api, in caso di parità porta verso la cima dell'albero chi ha posizione maggiore
    unsigned left, right, pos, max;
    doppio temp;
    left = 2*position - 1;
    right = 2*position;
    pos = position -1;  // per tenere conto del fatto che le numerazioni in informatica partono dallo 0

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
    // da appunti di api, ma tratta lo 0 come se fosse il numero più grande possibile, non si preoccupa dei casi di parità
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
        
    if(min != pos){
        temp = lista->array[min];
        lista->array[min] = lista->array[pos];
        lista->array[pos] = temp;
        min_heapify(lista, min+1);
    }
    
}

unsigned dijkstra(unsigned *matrix, int dim){
    // nota: dim = D-1 = #nodi != nodo 0
    unsigned i, j, result, row, new_val;
    doppio to_add[dim]; // contiene i nodi ancora da aggiungere (nelle posizioni) con i relativi pesi minimi con cui ci si arriva (nei valori)
    lista_sequenziale percorsi; // serve per trattare doppio come un min-heap, da passare a build_heap

    for ( i = 0; i < dim; i++){

        to_add[i].posizione = i;
        to_add[i].valore = matrix[i];
    }
    percorsi.array = to_add;
    percorsi.riempimento = dim;
    // fine inizializzazione
    
    build_heap(&percorsi, false); // percorsi.array usato come min heap

    result = 0;
    for (i = 0; i< dim; i++ ){ // mi serve calcolare la distanza da 0 ai restanti nodi al massimo dim volte, essendoci dim nodi

        if(to_add[i].valore == 0)
            break;
        
        row = (to_add[i].posizione + 1)* dim;   // calcolo valore utile per navigazione matrice

        // to_add alla fine sarà ordinato in maniera crescente, effetto non utilizzato
        percorsi.riempimento --;                // inizializzo parametri per min_heapify
        percorsi.array = percorsi.array + 1;    // sposto puntatore (per considerare soltanto il restante array)
        result += to_add[i].valore;             // aggiungo percorso minimo trovato al risultato

        for (j = 0; j<percorsi.riempimento; j++){
            // cambio i valori della matrice, aggiungendo il peso necessario ad arrivarci, per il nuovo nodo aggiunto, considerando solo i pesi dei nodi ancora da raggiungere
            new_val = matrix[percorsi.array[j].posizione + row] + to_add[i].valore;

            // verifico se il nuovo nodo aggiunto abbia dei percorsi a peso minore (o diverso da 0) dei nodi rimasti in 'percorsi.array'
            if(matrix[percorsi.array[j].posizione + row] && (new_val < percorsi.array[j].valore || percorsi.array[j].valore == 0))
                percorsi.array[j].valore = new_val;
            
        }
        build_heap(&percorsi, false);
    }
    
    return result;
}

// viene passato un valore da considerare e la relativa posizione, per vedere se deve rientrare o meno nel max-heap dei migliori grafi
void gestisci_top(lista_sequenziale* lista, unsigned new, unsigned position, unsigned dim){
    if(lista->riempimento < dim){
        lista->array[lista->riempimento].valore = new;
        lista->array[lista->riempimento].posizione = position;
        lista->riempimento ++;

        if(lista->riempimento == dim) // solo quando la lista dei migliori è piena la ordino, per risparmiare tempo (proprietà degli heap)
            build_heap(lista, true);
    
        return;
    }

    // sostituisco il nuovo valore con il max del max-heap, poi faccio scendere il valore nella sua giusta posizione dell'heap
    if(new < lista->array->valore){
        lista->array->valore = new;
        lista->array->posizione = position;
        max_heapify(lista, 1);
    }
}