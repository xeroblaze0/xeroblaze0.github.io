---
layout: post
title:  Computing Logic Funcitons using Perceptrons
date:   2019-11-20
description: Using layered perceptrons to compute logic functions
tags: nerual-net machine-learning python
thumbnail: /assets/perceptron/img/nn_02.png
---
<p>
  <a href=""></a><div class=""></div>
  <!-- <a href="/portfolio/assets/pdf/perceptron.pdf"><div class="color-button">Report</div></a> -->
  <a href="https://github.com/alexanderhay2020/alexanderhay2020.github.io/blob/master/portfolio/assets/py/"><div class="color-button">GitHub</div></a>
</p>

### Emulated Neurons
Neural networks are built on units called neurons, and for this exercise a special neuron called a perceptron is used.
Perceptrons are special in that they can represent fundamental logic functions: AND, OR, NAND, NOR. Though
a perceptron can’t represent XAND or XOR, layered perceptrons can, thus all logic functions can potentially be
built using a layered network structure.

<p>
    <img src="/assets/perceptron/img/nn_01.png" width="511" height="286" alt/>
    <br>
    <em><a href="https://medium.com/@lucaspereira0612/solving-xor-with-a-single-perceptron-34539f395182">images</a> showing perceptrons' logic structure</em>
</p>

Perceptrons work by multiplying a vector of inputs by a weight vector and passing the sum of that input-weight vectors through an activation function. For this exercise I used the sigmoid function, but there are many others. Weights are [nxm] matrices, where n is the dimension of the input and m is the dimension of the output.
<p>
    <img src="/assets/perceptron/img/nn_02.png" alt/>
    <br>
    <!-- <a href="https://missinglink.ai/guides/neural-network-concepts/neural-network-bias-bias-neuron-overfitting-underfitting/"><em>image</em></a> -->
    <em> image showing perceptron model</em>
</p>

<br>

Here is a sketch algorithm to implement a perceptron node:

<br>

$$
\Sigma (x_iw_i) = x_1w_1 + x_2w_2 + ... + x_nw_n
$$
$$
\sigma = \frac{1}{1+e^{\Sigma (x_iw_i )}}
$$
<br>

* *x* is the sample input
* *w* is the the associated weight for the input sample

For the perceptron to work properly, the weights need to be adjusted according to the desired output. To calculate and adjust the error we first subtract the predicted output from the actual output.

$$
\epsilon=y-\sigma
$$
<br>

* *ϵ* is the error
* *y* is the acutal output
* *σ* is defined above

Using gradient descent, we find the adjustment needed for the weights by computing the derivative of the sigmoid function and multiplying that by the error to give us the final adjustment for the weights:

$$
\sigma' = \sigma (1- \sigma)
$$
<br>

* *σ'* is the sigmoid derivative when given σ as above

$$
adjustment = \epsilon*\sigma'
$$
<br>

$$
w_i=w_i+ \hat{x}^T \cdot adjustments
$$

Networked together, perceptrons can be immensely powerful and are the foundations by which many neural nets are built. These new weights wouldn’t have changed much, but over many iterations they converge to their proper values of minimizing error. This method of adjusting the weights is called backpropagation.

To test the algorithm a small, simple sample set was used to provide easy-to-interpret results. The table below
shows the following dataset such that the output is 1 if first or second columns contained a 1, disregrading the third column:

|         | Variable 1 | Variable 2 | Variable 3 | Output |
|---------|------------|------------|------------|--------|
| Input 1 | 0          | 0          | 1          | 0      |
| Input 2 | 1          | 1          | 1          | 1      |
| Input 3 | 1          | 0          | 1          | 1      |
| Input 4 | 0          | 1          | 1          | 1      |

<!-- <p>
  <a href=""></a><div class=""></div>
  <a href="/assets/perceptron/py/perceptron.py"><div class="color-button">perceptron.py</div></a>
</p> -->
[perceptron.py](/assets/perceptron/py/perceptron.py) demonstrates the algorithm and predicted output. Given the input array and initial weights adjusted
200​ times, the predicted results are as follows:

|         | Variable 1 | Variable 2 | Variable 3 | Output |
|---------|------------|------------|------------|--------|
| Input 1 | 0          | 0          | 1          | 0.135  |
| Input 2 | 1          | 1          | 1          | 0.999  |
| Input 3 | 1          | 0          | 1          | 0.917  |
| Input 4 | 0          | 1          | 1          | 0.917  |

Given an infinite number of iterations the algorithm would converge to either 0 or 1, but in 200 iterations our results are close enough to see a clear distinction.

<!-- <p>
  <a href=""></a><div class=""></div>
  <a href="https://github.com/alexanderhay2020/alexanderhay2020.github.io/blob/master/portfolio/assets/py/classifier.py"><div class="color-button">classifier.py</div></a>
</p> -->

Applied to a larger dataset, [classifier.py](/assets/perceptron/py/classifier.py), we can create a linear classifier.

<p>
    <img src="/assets/perceptron/img/Figure_2-1.png" width="50%;" height="50%;" alt/><img src="/assets/perceptron/img/Figure_2-2.png" width="50%;" height="50%;" alt/>
    <br>
    <em>Left: Initial 2D dataset, Right: Perceptron classifier results</em>
</p>
<p>
    <img src="/assets/perceptron/img/Figure_2-4.png" width="50%;" height="50%;" alt/><img src="/assets/perceptron/img/Figure_2-5.png" width="50%;" height="50%;" alt/>
    <br>
    <em>Left: Initial validation dataset, Right: Perceptron validation classifier results</em>
</p>

The graph below shows the network error over 500 iterations. As expected the initial error is very high due to the weights being initially random. The error quicky drops after ~30 iterations, but never quite reaches zero. In this case error is ~4%, reflected in the misclassifed samples in both images on the right.

<p>
    <img src="/assets/perceptron/img/Figure_2-3.png" width="50%;" height="50%;" alt/>
    <br>
    <em>Network error percentage drops after each epoch, indicating a model is being learned</em>
</p>
