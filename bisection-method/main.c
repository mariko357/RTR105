#include "stdio.h"
#include "math.h"


#define PRECISION 1.0E-5f
#define MAX_ITERATIONS 10000000
#define FUNCTION "atan(x)"
#define RANGE_MIN -300.0f
#define RANGE_MAX 10000.0f

//function for which the roots are to be found
//atan(x)
double fn(double x){
    return atan(x);
}

unsigned char sign(double x){
    return (x >= 0.0f) ? 1 : 0;
}


int main(void){
    
    printf("Starting the program, finding the roots for ");
    printf(FUNCTION);
    printf("\n");

    double rangeMin, rangeMax, precision;
    printf("Please enter range in which to fing the roots (min, max) and precision:\n");
    scanf("%lf %lf %lf", &rangeMin, &rangeMax, &precision);
    
    if((fn(rangeMax) > 0 && fn(rangeMin) > 0) || (fn(rangeMax) < 0 && fn(rangeMin) < 0)){
        printf("Wrong starting range. Function doesn't intersect X axis;\n");
        return -1;
    }
    else if(fn(rangeMax) == 0 || fn(rangeMin) == 0){
        printf("Root is on one of the starting ranges;\n");
        return -1;
    }

    unsigned long iterations = 0;

    double midpoint;
    double left = rangeMin;
    double right = rangeMax;

    while(iterations < MAX_ITERATIONS){
        iterations += 1;
        midpoint = (left + right) / 2;
        if(fn(midpoint) == 0 || (right - left) / 2 < precision){
            printf("The root is: %.10f\n", midpoint);
            return 0;
        }
        if (sign(fn(midpoint)) == sign(fn(left))) left = midpoint;
        else right = midpoint;
    }
    printf("Max iterations exceeded and no root found;\n");
    return -1;
}