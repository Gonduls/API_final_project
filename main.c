#include <stdlib.h>
#include <stdio.h>
#define INPUT stdin //"./tests/open_tests/input_1"

int main(){
    char c;
    int i;
    FILE* input;
    input = fopen(INPUT, "r");
    printf("hi\n");
    i = fscanf(input, "%c", &c);
    //c = fgetc(input);
    printf("%c", c);

    //c = getc(stdin);
    while(i != EOF){
        printf("%c", c);
        //c = getc(stdin);
        i = fscanf(input, "%c", &c);
        //c = fgetc(input);
    }
    unsigned int a = __UINT32_MAX__;
    printf("%u\n", a);
    return 0;
}