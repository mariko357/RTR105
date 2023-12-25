# Integral
In mathematics, an integral is the continuous analog of a sum, which is used to calculate areas, volumes, and their generalizations.
Integration, the process of computing an integral, is one of the two fundamental operations of calculus, 
the other being differentiation. 
Integration started as a method to solve problems in mathematics and physics, 
such as finding the area under a curve, or determining displacement from velocity.

*[source](https://en.wikipedia.org/wiki/Integral)*

With integral being continuous, the area can be treated as sum of areas of rectangles under the function with
infinitelly small horizontal sides. This would obviously be impossible to compute, so the size of horizontal side
is usually chosen such that the integral can be computed within reasonable amount of time and / or desired precision.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e3/Riemann_Integration_and_Darboux_Lower_Sums.gif/600px-Riemann_Integration_and_Darboux_Lower_Sums.gif)

*[source](https://en.wikipedia.org/wiki/Integral#/media/File:Riemann_Integration_and_Darboux_Lower_Sums.gif)*

## Precision
As stated above, precision of integration depends on the "step" chosen.
Thus, for applications, where specified precision needs to be reached such
algorithm can be implemented:

![](/integral/Screenshot_20231224_200454.png)

Graph below demonstrates amount of steps required to integrate `atan(x)` on range [-10; 5] for different precision:

![](/integral/iterations.png)

The same graph with bezier smoothing applied:

![](/integral/iterations-xlog10.png)

Note that the x axis scale is logarithmic.

## Verification:
To calculate integral of `atan(x)` with specified precision and margins `integral.c`
can be used.

Below are some verifications of the calculated values (calculated with [WolframAlpha](https://wolframalpha.com)):

***
![](/integral/Screenshot_20231225_125506.png)

![](/integral/Screenshot_20231225_125559.png)
***
![](/integral/Screenshot_20231225_125717.png)

![](/integral/Screenshot_20231225_125709.png)
***
![](/integral/Screenshot_20231225_125841.png)

![](/integral/Screenshot_20231225_125853.png)