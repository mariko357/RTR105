```C
//
// File:	laneEmden.c
// Author:	Margaret Dorsey
//
// MATH 411 Numerical Analysis Project 3
//
// This program assists in the analysis of stellar approximations,
// specifically the Lane-Emden Equation.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// global for simplicity
double n;
double surface_eta;
#define PI 3.14159265359

#define THETA 0
#define ETA 1
#define MHAT 2
#define IHAT 3
#define OMEGAHAT 4

// fourth order Runge Kutta
double RK4(double (*f)(double, double), double x0, double y0, double x, double h);
// runge kutta solver for second order eqn split into a first order system
double RK4_2(void (*f)(double, double, double, double *, double *), double x0, double y0, double yp0, double x, double h, int *flag);
// runge kutta solver for full system of eqns for lane emden
void RK4_Sys(void (*f)(double, double *, double *), double xi0, double theta0, double eta0, double mhat0, double ihat0,
             double omegahat0, double x, double h, double *results);

void laneEmden(double xi, double theta, double eta, double *x, double *y)
{
    if (xi == 0)
    {
        *x = eta;
        *y = 0;
        return;
    }
    *x = eta; // derivative of theta with respect to xi  is eta
    *y = -2 * eta / xi - pow(theta, n);
}

void printArray(double *arr)
{
    printf("%lf %lf %lf %lf %lf\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
}

void laneEmdenSystem(double xi, double inputs[], double outputs[])
{
    if (xi == 0)
    {
        outputs[THETA] = inputs[ETA];
        outputs[ETA] = 0;
        outputs[MHAT] = 0;
        outputs[IHAT] = 0;
        outputs[OMEGAHAT] = 0;
        return;
    }
    outputs[THETA] = inputs[ETA]; // derivative of theta with respect to xi is eta
    outputs[ETA] = -2 * inputs[ETA] / xi - pow(inputs[THETA], n);
    outputs[MHAT] = 4 * PI * pow(inputs[THETA], n) * pow(xi, 2);
    outputs[IHAT] = (8.0 / 3.0) * PI * pow(inputs[THETA], n) * pow(xi, 4);
    outputs[OMEGAHAT] = 4 * PI * inputs[MHAT] * pow(inputs[THETA], n) * xi;
}

void printResults(double *results, double xi)
{
    printf("xi:\t %lf \t theta:\t %lf\n", xi, results[THETA]);
    printf("mhat:\t %lf \t ihat:\t %lf \t omegahat:\t %lf\n", results[MHAT], results[IHAT], results[OMEGAHAT]);
    printf("\n");
}

int main()
{
    double step;
    double h;
    printf("Enter n for Lane-Emden: ");
    scanf("%lf", &n);
    printf("Enter step size for the points: ");
    scanf("%lf", &step);
    printf("Enter stepsize: ");
    scanf("%lf", &h);

    double x = 0;
    int flag = 0;
    double theta;
    // find big xi, the end of the star
    while (flag != 1)
    {
        theta = RK4_2(laneEmden, 0, 1, 0, x, h, &flag);
        x += .0001; // small step size to try to get high precision
    }
    double surface = x;

    x = 0;
    printf("Big Xi: %lf Eta at Surface: %lf\n", surface, surface_eta);
    printf("\ntheta(xi) \t\ttheta^n(xi)\n");
    while (x < surface)
    {
        theta = RK4_2(laneEmden, 0, 1, 0, x, h, &flag);
        printf("[%lf,%lf] \t [%lf,%lf]\n", x, theta, x, pow(theta, n));
        if (flag == 1)
            break;
        x += step;
    }
    x = 0; // reset for another round

    printf("\n\n");
    double *results = (double *)malloc(sizeof(double) * 5);
    while (x < surface)
    {
        RK4_Sys(laneEmdenSystem, 0, 1, 0, 0, 0, 0, x, h, results);
        if (results[MHAT] != 0)
        {
            results[IHAT] = results[IHAT] / (results[MHAT] * pow(surface, 2)); // make dimensionless
            results[OMEGAHAT] = results[OMEGAHAT] * surface / pow(results[MHAT], 2);
        }
        printResults(results, x);
        x += step;
    }
    RK4_Sys(laneEmdenSystem, 0, 1, 0, 0, 0, 0, surface, h, results);
    results[IHAT] = results[IHAT] / (results[MHAT] * pow(surface, 2));
    results[OMEGAHAT] = results[OMEGAHAT] * surface / pow(results[MHAT], 2);
    printResults(results, surface);
    free(results);
}

// fourth order Runge Kutta
double RK4(double (*f)(double, double), double x0, double y0, double x, double h)
{
    int n = (int)((x - x0) / h);
    double k1, k2, k3, k4;
    double y = y0;
    for (int i = 1; i <= n; i++)
    {
        k1 = h * f(x0, y);
        k2 = h * f(x0 + .5 * h, y + 0.5 * k1);
        k3 = h * f(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * f(x0 + h, y + k3);

        // update next value of y
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);

        x0 = x0 + h;
    }
}
// runge kutta solver for second order eqn split into a first order system
double RK4_2(void (*f)(double, double, double, double *, double *), double x0, double y0, double yp0, double x, double h, int *flag)
{
    *flag = 0;
    int n = (int)((x - x0) / h);
    double k1, k2, k3, k4, m1, m2, m3, m4;
    double temp;
    double y = y0, yp = yp0; // two things to keep track of now that we're second order
    for (int i = 1; i <= n; i++)
    {
        f(x0, y, yp, &k1, &m1);
        f(x0 + .5 * h, y + 0.5 * h * k1, yp + 0.5 * h * m1, &k2, &m2);
        f(x0 + 0.5 * h, y + 0.5 * h * k2, yp + 0.5 * h * m2, &k3, &m3);
        f(x0 + h, y + h * k3, yp + h * m3, &k4, &m4);

        // update next value of y
        temp = y + (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        if (temp < 0)
        {
            *flag = 1;
            surface_eta = yp;
            break;
        }
        else
            y = temp;
        yp = yp + (h / 6.0) * (m1 + 2 * m2 + 2 * m3 + m4);
        x0 = x0 + h;
    }
    return y;
}

// runge kutta solver for full system of eqns for lane emden
void RK4_Sys(void (*f)(double, double[], double[]), double xi0,
             double theta0, double eta0, double mhat0, double ihat0,
             double omegahat0, double x, double h, double *y)
{
    int n = (int)((x - xi0) / h);
    double y1[5], y2[5], y3[5], k1[5], k2[5], k3[5], k4[5];
    double temp; // for checking if theta has become negative, ie we have left the star.
    y[THETA] = theta0,
    y[ETA] = eta0,
    y[MHAT] = mhat0,
    y[IHAT] = ihat0,
    y[OMEGAHAT] = omegahat0;

    // do our four steps
    for (int i = 1; i <= n; i++)
    {
        f(xi0, y, k1);
        y1[THETA] = y[THETA] + 0.5 * h * k1[THETA],
        y1[ETA] = y[ETA] + 0.5 * h * k1[ETA],
        y1[MHAT] = y[MHAT] + 0.5 * h * k1[MHAT],
        y1[IHAT] = y[IHAT] + 0.5 * h * k1[IHAT],
        y1[OMEGAHAT] = y[OMEGAHAT] + 0.5 * h * k1[OMEGAHAT];

        f(xi0 + .5 * h, y1, k2);
        y2[THETA] = y[THETA] + 0.5 * h * k2[THETA],
        y2[ETA] = y[ETA] + 0.5 * h * k2[ETA],
        y2[MHAT] = y[MHAT] + 0.5 * h * k2[MHAT],
        y2[IHAT] = y[IHAT] + 0.5 * h * k2[IHAT],
        y2[OMEGAHAT] = y[OMEGAHAT] + 0.5 * h * k2[OMEGAHAT];
        f(xi0 + 0.5 * h, y2, k3);
        y3[THETA] = y[THETA] + h * k3[THETA],
        y3[ETA] = y[ETA] + h * k3[ETA],
        y3[MHAT] = y[MHAT] + h * k3[MHAT],
        y3[IHAT] = y[IHAT] + h * k3[IHAT],
        y3[OMEGAHAT] = y[OMEGAHAT] + h * k3[OMEGAHAT];
        f(xi0 + h, y3, k4);

        // update next value of all our systems
        temp = y[THETA] +
               (h / 6.0) * (k1[THETA] + 2 * k2[THETA] + 2 * k3[THETA] + k4[THETA]);
        if (temp < 0)
            break; // stop after we leave the star
        y[THETA] = temp;
        y[ETA] = y[ETA] + (h / 6.0) * (k1[ETA] + 2 * k2[ETA] + 2 * k3[ETA] + k4[ETA]);
        y[MHAT] = y[MHAT] +
                  (h / 6.0) * (k1[MHAT] + 2 * k2[MHAT] + 2 * k3[MHAT] + k4[MHAT]);
        y[IHAT] = y[IHAT] +
                  (h / 6.0) * (k1[IHAT] + 2 * k2[IHAT] + 2 * k3[IHAT] + k4[IHAT]);
        y[OMEGAHAT] = y[OMEGAHAT] +
                      (h / 6.0) * (k1[OMEGAHAT] + 2 * k2[OMEGAHAT] + 2 * k3[OMEGAHAT] + k4[OMEGAHAT]);
        xi0 = xi0 + h;
    }
}

```

# [Source](https://github.com/Abhalphiest/NumericalAnalysis/blob/master/applications/laneEmden.c)

***

# Short breakdown:
This code is used to solve the **Lane-Emdem** equation, which is
used in astrophysics. It is 2nd order ODE (ordinary differential equation).
Differential equations are not easy to be solved by analytical methods
and this is where numerical methods come into help. The method used here is 
[**Runge-Kutta solver**](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods),
which can be used to find approximate solutions for [Simultaneous nonlinear equations](https://en.wikipedia.org/wiki/Simultaneous_nonlinear_equations).

***

## Algorithm:
Given an initial value problem $y' = f(t, y)$, where $y(t_0) = y_0$:
1. Choose a step size $h$.
2. Compute intermediate values $k_1, k_2, k_3$, and $k_4$ using the following formulas:
   - $k_1 = h \cdot f(t_n, y_n)$
   - $k_2 = h \cdot f(t_n + \frac{h}{2}, y_n + \frac{k_1}{2})$
   - $k_3 = h \cdot f(t_n + \frac{h}{2}, y_n + \frac{k_2}{2})$
   - $k_4 = h \cdot f(t_n + h, y_n + k_3)$
3. Update the solution:
   - $y_{n+1} = y_n + \frac{1}{6}(k_1 + 2k_2 + 2k_3 + k_4)$
4. Repeat until the desired endpoint is reached.

***

# Code walkthrough:

## `main()`:

```C
    double step;
    double h;
    printf("Enter n for Lane-Emden: ");
    scanf("%lf", &n);
    printf("Enter step size for the points: ");
    scanf("%lf", &step);
    printf("Enter stepsize: ");
    scanf("%lf", &h);
```

With the help of the code above, user can input:
- `step` - used for precision.
- `h` - used for precision when solving with RK4 method.
- `n` (global) - polytropic index, which is a measure of how compressible a substance is under pressure.


```C
double x = 0;
    int flag = 0;
    double theta;
    // find big xi, the end of the star
    while (flag != 1)
    {
        theta = RK4_2(laneEmden, 0, 1, 0, x, h, &flag);
        x += .0001; // small step size to try to get high precision
    }
    double surface = x;
```

The code above is used to calculate `surface` (`x`) and `theta` the precision for `x` is
fixed (due to `x += .0001`), while the precision for `theta` can vary.

After the loop finishes, the program will have calculated values for `surface` and `surface_eta`. `RK4_2` also calculates the `theta`, though, it is not used afterwards. 


```C
    x = 0;
    printf("Big Xi: %lf Eta at Surface: %lf\n", surface, surface_eta);
```

As we can see, `x` is reused for multiple calculations and is reset to 0 after each loop.

The code above prints out the calculated values of `surface` and `surface_eta`. They 
are used to charecterize the astronomical bodies using Lane-Emdem eq.


```C
    printf("\ntheta(xi) \t\ttheta^n(xi)\n");
    while (x < surface)
    {
        theta = RK4_2(laneEmden, 0, 1, 0, x, h, &flag);
        printf("[%lf,%lf] \t [%lf,%lf]\n", x, theta, x, pow(theta, n));
        if (flag == 1)
            break;
        x += step;
    }
    x = 0; // reset for another round
```

`x` is being reset once again. The code here is similar to the previous loop, but here the
values of `theta` are being used and printed out. This loop is used to show the how `theta`
and `theta ^ n` are related to `Xi` (`x`)

```C
    printf("\n\n");
    double *results = (double *)malloc(sizeof(double) * 5);
```

Code above prints 2 new lines and allocates array `results[]` with the size of 40 (8 * 5) bytes, for 5 `double` fp numbers.

```C
    while (x < surface)
    {
        RK4_Sys(laneEmdenSystem, 0, 1, 0, 0, 0, 0, x, h, results);
        if (results[MHAT] != 0)
        {
            results[IHAT] = results[IHAT] / (results[MHAT] * pow(surface, 2)); // make dimensionless
            results[OMEGAHAT] = results[OMEGAHAT] * surface / pow(results[MHAT], 2);
        }
        printResults(results, x);
        x += step;
    }
```

The code is once again somewhat similar to the previous loop, but this time `RK4_Sys` is used
to calculate the results. It is similar to `RK4_2`, but solves the equation for 5
orders of `n`. `laneEmdenSystem()` is used as input function instead of the `LaneEmden()`.
Thus, at each iteration we get an array of 5 values (5 orders) which are being
printed with `printResults()` function.


```C
    RK4_Sys(laneEmdenSystem, 0, 1, 0, 0, 0, 0, surface, h, results);
    results[IHAT] = results[IHAT] / (results[MHAT] * pow(surface, 2));
    results[OMEGAHAT] = results[OMEGAHAT] * surface / pow(results[MHAT], 2);
    printResults(results, surface);
```

Code above calculates the last values directly at the surface of the object.
This is done so, because selected precision (`step`) can be selected too big and the
calculations will finish without reaching the surface.


```C
    free(results);
```

Free up the memory used by the array.

***

## `RK4_2()`:

```C
double RK4_2(void (*f)(double, double, double, double *, double *), double x0, double y0, double yp0, double x, double h, int *flag)
{
    *flag = 0;
    int n = (int)((x - x0) / h);
    double k1, k2, k3, k4, m1, m2, m3, m4;
    double temp;
    double y = y0, yp = yp0; // two things to keep track of now that we're second order
    for (int i = 1; i <= n; i++)
    {
        f(x0, y, yp, &k1, &m1);
        f(x0 + .5 * h, y + 0.5 * h * k1, yp + 0.5 * h * m1, &k2, &m2);
        f(x0 + 0.5 * h, y + 0.5 * h * k2, yp + 0.5 * h * m2, &k3, &m3);
        f(x0 + h, y + h * k3, yp + h * m3, &k4, &m4);

        // update next value of y
        temp = y + (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        if (temp < 0)
        {
            *flag = 1;
            surface_eta = yp;
            break;
        }
        else
            y = temp;
        yp = yp + (h / 6.0) * (m1 + 2 * m2 + 2 * m3 + m4);
        x0 = x0 + h;
    }
    return y;
}
```

The code above is Runge-Kutta solver for 2nd order differential equations.

Inputs are:
- `f` - The function, for which solution needs to be found. In our case this is Lane-Emdev eq.
- `x` and `x0` - judginng by this (`int n = (int)((x - x0) / h);`) code, these are the end
and start of the range respectively.
- `h` - Precision (step size) to be used in calculations,
number of steps is calculated using its. (`int n = (int)((x - x0) / h);`).
- `flag` - variable used to show that the calculations are finished.
- `y0` and `yp0` - input parameters for the Lane-Emdem.

`double k1, k2, k3, k4, m1, m2, m3, m4; double temp;` - temporary variables that are used during the calculations. 

It can be noted, that the function ends when the `temp` value is < 0. The `flag` is set to 1
and the function return y value and also sets the `surface_eta` global variable to `yp`. It
can also be said that the `y` approaches 0, as it is set to temp each iteration.

The calculations are also recursive, as the values from the previous iteration are reused
in the next one:

```C
else y = temp;
yp = yp + (h / 6.0) * (m1 + 2 * m2 + 2 * m3 + m4);
x0 = x0 + h;
```

We can also see that `RK4_2()` indeed utilizes Runge-Kutta method, according to the code above.
The only difference being that the step can vary, thus `(h / 6.0)` is used instead of `1.0 / 6.0`.

***

## `LaneEmdem()`:

```C
void laneEmden(double xi, double theta, double eta, double *x, double *y)
{
    if (xi == 0)
    {
        *x = eta;
        *y = 0;
        return;
    }
    *x = eta; // derivative of theta with respect to xi  is eta
    *y = -2 * eta / xi - pow(theta, n);
}
```

Lane-Emdem equation function.

***

## `LaneEmdemSystem()`:

```C
void laneEmdenSystem(double xi, double inputs[], double outputs[])
{
    if (xi == 0)
    {
        outputs[THETA] = inputs[ETA];
        outputs[ETA] = 0;
        outputs[MHAT] = 0;
        outputs[IHAT] = 0;
        outputs[OMEGAHAT] = 0;
        return;
    }
    outputs[THETA] = inputs[ETA]; // derivative of theta with respect to xi is eta
    outputs[ETA] = -2 * inputs[ETA] / xi - pow(inputs[THETA], n);
    outputs[MHAT] = 4 * PI * pow(inputs[THETA], n) * pow(xi, 2);
    outputs[IHAT] = (8.0 / 3.0) * PI * pow(inputs[THETA], n) * pow(xi, 4);
    outputs[OMEGAHAT] = 4 * PI * inputs[MHAT] * pow(inputs[THETA], n) * xi;
}
```

Lane-Emdem function for all the orders.

Inputs:

- `xi` number used in calculations.
- `inputs[]` - array of inputs, that are used for calculations.

Outputs:

- `outputs[]` - calculated results are places in this array.

***

## `RK_Sys()`:

```C
// runge kutta solver for full system of eqns for lane emden
void RK4_Sys(void (*f)(double, double[], double[]), double xi0,
             double theta0, double eta0, double mhat0, double ihat0,
             double omegahat0, double x, double h, double *y)
{
    int n = (int)((x - xi0) / h);
    double y1[5], y2[5], y3[5], k1[5], k2[5], k3[5], k4[5];
    double temp; // for checking if theta has become negative, ie we have left the star.
    y[THETA] = theta0,
    y[ETA] = eta0,
    y[MHAT] = mhat0,
    y[IHAT] = ihat0,
    y[OMEGAHAT] = omegahat0;

    // do our four steps
    for (int i = 1; i <= n; i++)
    {
        f(xi0, y, k1);
        y1[THETA] = y[THETA] + 0.5 * h * k1[THETA],
        y1[ETA] = y[ETA] + 0.5 * h * k1[ETA],
        y1[MHAT] = y[MHAT] + 0.5 * h * k1[MHAT],
        y1[IHAT] = y[IHAT] + 0.5 * h * k1[IHAT],
        y1[OMEGAHAT] = y[OMEGAHAT] + 0.5 * h * k1[OMEGAHAT];

        f(xi0 + .5 * h, y1, k2);
        y2[THETA] = y[THETA] + 0.5 * h * k2[THETA],
        y2[ETA] = y[ETA] + 0.5 * h * k2[ETA],
        y2[MHAT] = y[MHAT] + 0.5 * h * k2[MHAT],
        y2[IHAT] = y[IHAT] + 0.5 * h * k2[IHAT],
        y2[OMEGAHAT] = y[OMEGAHAT] + 0.5 * h * k2[OMEGAHAT];
        f(xi0 + 0.5 * h, y2, k3);
        y3[THETA] = y[THETA] + h * k3[THETA],
        y3[ETA] = y[ETA] + h * k3[ETA],
        y3[MHAT] = y[MHAT] + h * k3[MHAT],
        y3[IHAT] = y[IHAT] + h * k3[IHAT],
        y3[OMEGAHAT] = y[OMEGAHAT] + h * k3[OMEGAHAT];
        f(xi0 + h, y3, k4);

        // update next value of all our systems
        temp = y[THETA] +
               (h / 6.0) * (k1[THETA] + 2 * k2[THETA] + 2 * k3[THETA] + k4[THETA]);
        if (temp < 0)
            break; // stop after we leave the star
        y[THETA] = temp;
        y[ETA] = y[ETA] + (h / 6.0) * (k1[ETA] + 2 * k2[ETA] + 2 * k3[ETA] + k4[ETA]);
        y[MHAT] = y[MHAT] +
                  (h / 6.0) * (k1[MHAT] + 2 * k2[MHAT] + 2 * k3[MHAT] + k4[MHAT]);
        y[IHAT] = y[IHAT] +
                  (h / 6.0) * (k1[IHAT] + 2 * k2[IHAT] + 2 * k3[IHAT] + k4[IHAT]);
        y[OMEGAHAT] = y[OMEGAHAT] +
                      (h / 6.0) * (k1[OMEGAHAT] + 2 * k2[OMEGAHAT] + 2 * k3[OMEGAHAT] + k4[OMEGAHAT]);
        xi0 = xi0 + h;
    }
}
```

The function has similar features and same task as the `RK4_2()`, with the difference being
that everything is "scaled" by 5 (to calculate the values for all possible orders).

***

## `printResults()`

```C
void printResults(double *results, double xi)
{
    printf("xi:\t %lf \t theta:\t %lf\n", xi, results[THETA]);
    printf("mhat:\t %lf \t ihat:\t %lf \t omegahat:\t %lf\n", results[MHAT], results[IHAT], results[OMEGAHAT]);
    printf("\n");
}
```

The code above prints the results according to `Xi`. The output looks like this:

```
xi:      3.150100        theta:  0.000507
mhat:    39.478363       ihat:   0.259971        omegahat:       0.752032
```

***

## Definitions and Includes:

```C
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// global for simplicity
double n;
double surface_eta;
#define PI 3.14159265359

#define THETA 0
#define ETA 1
#define MHAT 2
#define IHAT 3
#define OMEGAHAT 4
```

Above are includes for the neccesary libraries; Declaration of 2 global variables, that are used later
and definitions of the order of Lane-Emdem function, to be more human-readable.