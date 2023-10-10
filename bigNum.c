#include "stdio.h"



int main(int argc, char *argv[])
{
	printf("Enter two large numbers to get their product\n");
	long long int a = 0, b = 0;
	scanf("%lld %lld", &a, &b);
	long long int product = a * b;
	printf("Product: %lld\n", product);

	return 0;
}
