//Different types of variables:

#include "stdio.h"
int main(int argc, char *argv[])
{
	char c;
	unsigned char uc;
	int i;
	unsigned int ui;
	long int li;
	float f;
	long l;
	long long ll;
	
	int someInt; //this is declaration, variable will have contents of previously used memory.
	//(basically garaabge), this can couse problems when, for example, you assume that the value of
	//variable is 0 and you try to add something to it.
	int someDefinedInt = 5; //this is definition, variable will have value 5. 

	printf("Size of char: %d\n", sizeof(c));
	printf("Size of unsigned char: %d\n", sizeof(uc));
	printf("Size of integer: %d\n", sizeof(i));
	printf("Size of unsigned integer: %d\n", sizeof(ui));
	printf("Size of long integer: %d\n", sizeof(li));
	printf("Size of float: %d\n", sizeof(f));
	printf("Size of long: %d\n", sizeof(l));
	printf("Size of long long: %d\n", sizeof(ll));

	// purpose of variable is to be changed and modified:
	// we can do it like so:
	someDefinedInt = 10;
	someDefinedInt = 10.0123; // the data after decimal point will simply be trunctaed.
	printf("someDefinedInt: %d\n", someDefinedInt);
	return 0;
}
