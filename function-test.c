#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void printHello(){
	printf("Hello world!\n");
}

void printRandomNumber(){
	int random = rand();
	printf("Some random number: %i\n", random);
}

int main(int argc, char *argv[])
{
	printHello();
	srand(time(NULL));
	printf("printing 10 random numbers:\n");
	for(int i = 0; i < 10; i++){
		printRandomNumber();
	}
	for(int i = 0; i < 100; i++){
		int random = rand();
		if(random % 5 == 0){
			printf("The number %i is divisable by 5\n", random);
		}
		else{
			printf("The number %i is not divisible by 5\n", random);
		}

	}
	return 0;
}
