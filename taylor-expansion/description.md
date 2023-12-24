# Taylor series

## Definition:
Taylor expansion is a mathematical technique used to approximate a function by representing it as an infinite sum of terms, 
each derived from the function's derivatives at a specific point. Named after the mathematician Brook Taylor, 
this expansion is particularly useful for approximating complex functions with simpler polynomial expressions.

![](https://i.pinimg.com/originals/d8/ce/7d/d8ce7d45df6eacfdc1086ebc296aaf11.gif)
*[Source](https://www.pinterest.com/pin/842736149007640110/)*

## My function to investigate:

$\arctan (x) \simeq \frac{x}{\sqrt{1+x^2}} \cdot \sum_{k=0}^{500} \frac{(2 \cdot k) !}{(k !)^2 \cdot 4^k \cdot(2 \cdot k+1)} \cdot\left(\frac{x^2}{1+x^2}\right)^k, \text { on }-\infty<x<\infty$

## Code breakdown:

```C
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
```

First, the constants are calculated:

$C1 = \frac{x}{\sqrt{1 + x^2}}$

$C2 = \frac{x^2}{1 + x^2}$

Then, a loop runs for specified amount of iterations:

$aPrev = aPrev×recursiveElement(i)×C2$, where $\text{{recursiveElement(K)}} = \frac{{4K^2 + 1 - 4K}}{{4K^2 + 2K}}$

$taylor = taylor + aPev$

Then, final value of taylor series is:

$taylor = taylor * C1$

This way, the series can be computed much more efficiently, calculating only vairables that change instead of the whole expression each iteration.

# Taylor series error:
Due to Taylor series being an infinitie sum of terms, it is expected that the error will be present for an expansion with
finite amount of terms (iterations).

The graph below demonstrates how the function of `atan(x)`, calculated using Taylor series approaches the function calculated with `math` library.

![](/taylor-expansion/iterations-plot/taylor.png)

The graph below demonstrates the error of function of `atan(x)`, calculated using Taylor series vs the function calculated with `math` library.

![](/taylor-expansion/errors/errors.png)
