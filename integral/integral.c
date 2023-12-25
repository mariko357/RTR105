#include "stdio.h"
#include "math.h"

double fn(double x){
    return atan(x);
}


double dabs(double x){
    return x >= 0.0 ? x : -x;
}


double integral(double (*function)(double), double left, double right, unsigned long iterations){
    double step = ((right - left) / iterations);
    double integral = 0.0f;
    
    for(unsigned long i = 0; i < iterations; i++){
        integral += (fn(left + i * step) * step);
    }

    return integral;
}

int main(){

    double left, right, precision;
    printf("Please enter the left, right margins and precision respectively:\n");
    scanf("%lf %lf %lf", &left, &right, &precision);

    unsigned long iterations = 1;

    while(dabs(integral(fn, left, right, iterations) - integral(fn, left, right, iterations * 2)) > precision){
        iterations *= 2;
    }

    printf("The integral is: %.10f\n", integral(fn, left, right, iterations));

    return 0;
}