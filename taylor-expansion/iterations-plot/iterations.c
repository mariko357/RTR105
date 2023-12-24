//Program to demonstrate how taylor expansion works

#include "stdio.h"
#include "math.h"

#define ITERATIONS 13

double recursiveElement(unsigned int k){
    double value = 0;
    double K = (double)k;
    value = (4 * K * K + 1 - 4 * K) / (4 * K * K + 2 * K);
    return value;
}

double taylor(double x, unsigned long int iterations){
    double C1 = (x) / sqrt(1 + x * x);
    double C2 = (x * x) / (1 + x * x);

    double aPrev = 1.0f;
    double taylor = 1.0f;

    double error = 0.0f;

    for(unsigned long int i = 1; i < iterations; i++){
        aPrev *= recursiveElement(i) * C2;
        taylor += aPrev;
    }

    taylor *= C1;

    return taylor;
}

int main(){

    unsigned long int iterations[ITERATIONS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 1000, 100000};

    for (int iter = 0; iter < ITERATIONS; iter++){

        FILE *pFile;
        char buff[64];
        sprintf(buff, "%u.dat", iterations[iter]);
        pFile = fopen(buff, "w");

        printf("x    atan    \n");
        fprintf(pFile, "x    atan    \n");

        for (double x = -10.0f; x <= 10.0f; x+=0.001f){

            printf("%.4f %.15f\n", x, taylor(x, iterations[iter]));
            fprintf(pFile, "%.4f %.15f\n", x, taylor(x, iterations[iter]));
        }


        fclose(pFile);
    }
    
    return 0;
}
