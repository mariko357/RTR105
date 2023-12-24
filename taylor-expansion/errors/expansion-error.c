//Program to calculate error for different x values with different amount of iterations

#include "stdio.h"
#include "math.h"

#define ITERATIONS 5

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

    unsigned long int iterations[ITERATIONS] = {10, 100, 1000, 10000, 100000};

    for (int iter = 0; iter < ITERATIONS; iter++){

        FILE *pFile;
        char buff[64];
        sprintf(buff, "%lu.dat", iterations[iter]);
        pFile = fopen(buff, "w");

        printf("x    valueWithTaylor    valueWithAtan    err\n");
        fprintf(pFile, "x    valueWithTaylor    valueWithAtan    err\n");

        for (double x = -500.0f; x <= 500.0f; x+=0.1f){

            double t = taylor(x, iterations[iter]);

            printf("%.2f %.15f %.15f %.15f\n", x, t, atan(x), atan(x) - t);
            fprintf(pFile, "%.2f %.15f %.15f %.15f\n", x, t, atan(x), atan(x) - t);
            
        }


        fclose(pFile);
    }
    
    return 0;
}
