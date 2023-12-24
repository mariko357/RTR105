# Finite difference:
Finite difference is a numerical method used to approximate derivatives of a function.
It is particularly useful when an analytical expression for the derivative is difficult to obtain or when dealing with discrete data points.
$$f'(x_0) \approx \frac{f(x_0 + h) - f(x_0)}{h}$$

![](https://www.iue.tuwien.ac.at/phd/heinzl/img543.png)
*[source](https://www.iue.tuwien.ac.at/phd/heinzl/node27.html)*

# 1st and 2nd order derivatives of `atan(x)` using finite difference:

![](/derivative/derivative.png)

When comparing to the graph, drawn by a calculator:

![](/derivative/Screenshot_20231224_172133.png)

*[source](https://www.desmos.com/calculator)*

It can be seen that the derivative, calculated using finite difference is very close to the one, give by definition[^1].

# Errors:
By definition, the formula of derivative is:
$$
f'(x_0) = \lim_{{h \to 0}} \frac{{f(x_0 + h) - f(x_0)}}{h}.
$$
When comparing it to the finite difference formula:
$$
f'(x_0) \approx \frac{f(x_0 + h) - f(x_0)}{h}
$$
It can be seen that the main source of error is `h` not being an infinitesimal, but rather  discrete value.
The larger the step `h` is, the bigger the error will be.

The graph below demonstrates the error of finite difference, compared to the
derivative, calculated by formula[^1].

![](/derivative/errors.png)

[^1]: Note, all the calculations were made with the precision (step) equal to 1E-3.