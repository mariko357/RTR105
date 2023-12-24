#undef __STRICT_ANSI__

#include <stdio.h>
#include <math.h>

#define STEP 1E-3f
#define RANGE_START -10.0f
#define RANGE_END 10.0f

double atanDerivative(double x){
    return 1 / (1 + x * x);
}
double atan2Derivative(double x){
    return -((2 * x) / ((1 + x * x) * (1 + x * x)));
}

//the function to be investigated is atan(x)

int main()
{
    FILE *pFile;
    
    pFile = fopen("derivative.dat", "w");
    fprintf(pFile, "\tx\t\tatan(x)\t\tatan\'(x) (fd)\t\tatan\'\'(x) (fd)\t\tatan\'(x) (def)\t\tatan\'\'(x) (def)\t\terror1\t\t error2\n");

    double prev2Derivative = 0.0f;
    
    for(double x = RANGE_START; x < RANGE_END; x += STEP){
        double derivative = (atan(x + STEP) - atan(x)) / STEP;
        double derivative2 = (((atan(x + STEP + STEP) - atan(x + STEP)) / STEP) - derivative) / STEP;
        double error = derivative - atanDerivative(x);
        double error2 = derivative2 - atan2Derivative(x);
        fprintf(pFile, "%10.8f\t%10.8f\t%10.8f\t%10.8f\t%10.8f\t%10.8f\t%10.8f\t%10.8f\n", x, atan(x), derivative, derivative2, atanDerivative(x), atan2Derivative(x), error, error2);
    }
    fclose(pFile);
    return 0;
}