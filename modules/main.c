#include "main.h"
int main(void){
    printf("Function with arguments and return value: %c\n", modChar(100));
    printf("Function with arguments but no return value:\n");
    printChar(102);
    printf("Function without arguments but with return value: %d\n", getRandomNumber());
    printf("Function without arguments and without return value: \n");
    printHello();
    return 0;
}