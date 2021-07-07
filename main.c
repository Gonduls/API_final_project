#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM_LEN 10

int main(){
    unsigned D, K;
    if(scanf("%u %u", &D, &K) != 2){
        printf("Failed to get input, closing program\n");
        return 1;
    }

    unsigned MAX_LINE_LEN = D*(MAX_NUM_LEN + 1);
    char line[MAX_LINE_LEN];
    while(fgets(line, MAX_LINE_LEN, stdin) != NULL)
        printf("%s", line);
    return 0;
}