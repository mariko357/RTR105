#include <assert.h>
#include <stdio.h>
#include "string.h"
 
int main(void)
{
	//reading previous contents of file.
	char contents[128];
	FILE* f0 = fopen("file", "r");
	assert(f0);
	fread(contents, sizeof(contents[0]), 12, f0);
	puts(contents);
	fclose(f0);
	
	//writing a new message into file.
	char message[] = "hello world!";
	FILE* f1 = fopen("file", "w");
	assert(f1);
	fwrite(message, sizeof(message[0]), strlen(message), f1);
	fclose(f1);

	return 0;
}
