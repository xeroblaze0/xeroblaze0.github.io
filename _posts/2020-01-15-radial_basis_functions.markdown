---
layout: post
title:  Function Approximation Using Radial Basis Functions
date:   2020-01-15
description: Using radial basis functions to approximate a linear mapping
tags: math stats biology matlab
thumbnail: /assets/rbf/Figure_3.png
---

<p>
  <a href=""></a><div class=""></div>
  <a href="https://github.com/alexanderhay2020/469_bme/blob/master/ps1/py/part1.py"><div class="color-button">GitHub</div></a>
</p>

### Color Specific Photoreceptors - Cones
Inside the retina are cone cells, photosensitive cells that differentiate color. Humans have 3 different types of cones; (S)mall, (M)edium, and (L)arge, corresponding to the length of the wavelength that excites it. The excitement amplitudes of each type of cone is perceived to us as color, and the color perceived is the sum of each cone response.

<div class="img_row">
    <img class="col three" src="/assets/rbf/figure_5.gif">
</div>
<div class="col three caption">
    The color perceived is the sum of each cone response
</div>

### Radial Basis Functions
A Radial Basis Function (RBFs) is a function whose value depends the distance between a query point and a fixed point. For this exercise I used the Gaussian Function:


$$
h(x)=exp(-\frac{(x-c^2)}{r^2})
$$


* *x* is the query point
* *c* is some fixed point, 0 if distance is measured from origin
* *h(x)* is the RBF

By using multiple RBFs you can approximate a function. By multiplying the RBF by some weight, summing a network of RBFs can approximate a function:

$$
f(x) = \sum_{j=1}^{m}  w_j h_j(x)
$$

* *h(x)* is the RBF
* *w* is the weight for the RBF
* *j* in the index for *m* samples of x

The weight vector can be found using linear regression, ultimately leading to this equation:

$$
 \overrightarrow{w} = (H^TH)^{-1}H^T\overrightarrow{y}
$$

* *H* is the *design matrix* of *h(x)*, or a *nxm* matrix of *n* samples and *m* RBFs
* *y* is f(x) vectorized

In this exercise we have the following dataset:
* *x* is drawn from a uniform random distribution, from *-10 < n < 10; n=1,000*
* *y = 2x + e*;  e is a normally distributed noise vector, $μ = 1, σ = 0$
* Use 48 RBFs, between -12 and 12 @ every 0.5 along the x axis

<div class="row mt-3">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/rbf/Figure_1.png" class="img-fluid rounded z-depth-1" %}
    </div>
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/rbf/Figure_2.png" class="img-fluid rounded z-depth-1" %}
    </div>
</div>

<div class="row mt-3">
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/rbf/Figure_3.png" class="img-fluid rounded z-depth-1" %}
    </div>
    <div class="col-sm mt-3 mt-md-0">
        {% include figure.html path="/assets/rbf/Figure_4.png" class="img-fluid rounded z-depth-1" %}
    </div>
</div>

[Fig. 1](https://alexanderhay2020.github.io/alexanderhay2020.github.io//portfolio/assets/img/Figure_1.png) - Dataset visualized

[Fig. 2](https://alexanderhay2020.github.io/alexanderhay2020.github.io//portfolio/assets/img/Figure_2.png) - 48 RBFs plotted

[Fig. 3](https://alexanderhay2020.github.io/alexanderhay2020.github.io//portfolio/assets/img/Figure_3.png) - Function prediction

[Fig. 4](https://alexanderhay2020.github.io/alexanderhay2020.github.io//portfolio/assets/img/Figure_4.png) - Error analysis

Modeling photoreceptor response provides insight to how information is gathered and processed at the cellular level. It's the network of these cone cells that provide the stimulus we interpret as color.
