#include "stdio.h"

int main(){
	char input = 0, firstOne = 0;
	scanf("%hhu", &input);
	printf("Full 8 bits: 0b");
	for(int i = 7; i >= 0; i--){
		printf((1 & (input >> i )) ? "1" : "0");
		if(1 & (input >> i) && firstOne <= i){
			firstOne = i;
		}
	}
	
	printf("\nShortened: 0b");
	
	for(int i = firstOne; i >= 0; i--){
		printf(1 & (input >> i) ? "1" : "0");
	}
	printf("\n");
	return 0;
}
