#include "stdio.h"

unsigned char minx(unsigned char a, unsigned char b){
    return (a < b) ? a : b;
}

unsigned char maxx(unsigned char a, unsigned char b){
    return (a > b) ? a : b;
}

int main(){
    printf("Please enter 3 characters\n");
    unsigned char a, b, c;
    unsigned char mode;
    scanf("%c %c %c", &a, &b, &c);
    printf("Please enter the order you want the numbers to be sorted (0 = ascending, 1 = descending)\n");
    scanf("%hhu", &mode);

    unsigned char minn = minx(a, minx(b, c));
    unsigned char maxn = maxx(a, maxx(b, c));
    unsigned char avgn = (a + b + c) - minn - maxn;

    if(!mode){
        printf("%c %c %c \n", minn, avgn, maxn);

    }
    else{
        printf("%c %c %c \n", maxn, avgn, minn);
    }

    return 0;
}