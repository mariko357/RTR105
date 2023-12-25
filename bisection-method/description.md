# Bisection method

## Description:
The bisection method is a numerical technique used to find the root of a continuous function within a specified interval.
The main idea behind this method is based on the Intermediate Value Theorem, which states that if a 
continuous function takes on different signs at the endpoints of an interval, then there must be at least one root within that interval.

![](https://x-engineer.org/wp-content/uploads/2016/11/The-Bisection-Method-animation.gif)

*[source](https://x-engineer.org/bisection-method/)*

## Code breakdown:
My function to find the roots for:

$$
\arctan(x)
$$

Code that is responsible for root calculation:

```C
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
```
Here $$fn(x) = \arctan(x)$$

1. The left and right margins are selected.
2. Then, until the root is found or the maximum allowed number of iterations is reached:

    1. Midpoint is calculated, if function at that point is 0, or the difference between left and right position is less then precision, __the root is at the midpoint__, program ends.
    2. If the sign of function at midpoint is the same as the sign of function at left position, left position becomes equal to midpoint. Else, right position becomse equal to midpoint.

## Usage:
To run the program yourself:
```
git clone https://github.com/mariko357/RTR105.git
cd RTR105/bisection-method
gcc -lm main.c
./a.out
```

*** 

[Wolfram alpha](https://www.wolframalpha.com/input?i=roots+of+atan%28x%29):
![](/bisection-method/Screenshot_20231224_170628.png)

My program:
![](/bisection-method/Screenshot_20231224_170759.png)