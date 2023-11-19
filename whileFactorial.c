#include "stdio.h"

int main(){

    unsigned char dataType;
    printf("Please enter the data type to use (0 - char, 1 - int, 2 - long long):\n");
    scanf("%hhu", &dataType);
    printf("Please enter the number to calculate the factorial of:\n");

    if(dataType == 0){
        char a;

        scanf("%hhd", &a);

        char factorial = 1;

        while(a > 0){
            if((char)((char)(factorial * a) / a) != factorial){
                printf("Error in specified values, check selected data types or value of input\n");
                return -1;
            }
            factorial *= a;
            a -= 1;
        }

        printf("%hhd\n", factorial);
    }
    else if(dataType == 1){
        int a;

        scanf("%d", &a);

        int factorial = 1;

        while(a > 0){
            if((int)((int)(factorial * a) / a) != factorial){
                printf("Error in specified values, check selected data types or value of input\n");
                return -1;
            }
            factorial *= a;
            a -= 1;
        }

        printf("%d\n", factorial);
    }
    else if(dataType == 2){
        long long a;

        scanf("%lld", &a);

        long long factorial = 1;

        while(a > 0){
            if((long long)((long long)(factorial * a) / a) != factorial){
                printf("Error in specified values, check selected data types or value of input\n");
                return -1;
            }
            factorial *= a;
            a -= 1;
        }

        printf("%lld\n", factorial);
    }
    return 0;
}