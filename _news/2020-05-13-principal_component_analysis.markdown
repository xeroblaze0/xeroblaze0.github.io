---
layout: post
title:  Principal Component Analysis
date:   2020-05-13
description: Using PCA to determine number of presynaptic inputs of a cell
tags: math stats neuroscience matlab
---

<p>
  <a href=""></a><div class=""></div>
  <a href="https://github.com/alexanderhay2020/408/blob/master/hw/hw5/homework5.m"><div class="color-button">GitHub</div></a>
</p>

### Neuron Anatomy

Neurons generally have four functional regions; input, integration, conduction, and output. Inputs are generated current flowing in and out of the cell. Inputs are aggregated, and if triggered, generate an action potential and releasing neurotransmitters. In this exercise I examine the intracellular activity of a cell and determine how many presynaptic cells are providing an input, as well as the activity level of each input.

<div class="img_row">
  <img class="col three" src="/assets/pca/fig_01.png">
</div>
<div class="col three caption">
  Figure 1: General functional regions of the neuron
</div>

### Initial Data

To visualize the data I plotted it as a heat map. The left image shows all of the data, the right image displays fewer samples, highlighting the different inputs the cell is receiving.

<div class="img_row">
  <img class="col three" src="/assets/pca/fig_02.png">
</div>
<div class="col three caption">
  Figure 2: left, all of the sample data plotted; right, samples showing different responses
</div>

The data is a series of voltage measurements over time; if we look at a covariance matrix (Figure 3) it would be able to show us how the voltage measured at each time point vary together.

<div class="img_row">
  <img class="col three" src="/assets/pca/fig_03.png">
</div>
<div class="col three caption">
  Figure 3: Covariance matrix of the cell voltage data
</div>


### Principal Component Analysis (PCA)

From there we can run PCA on the data, seen in Figure 4. Three PCs stand out in that they explain more fractional variance than the other PCs, but ultimately we would need hundreds to explain all of the data. By plotting those three principal components we can clearly see three signal responses (Figure 5, left). Looking at the histogram (Figure 5, right) confirms that the 4th PC has a gaussian centered at 0, a strong indicator of noise.

<div class="img_row">
  <img class="col" src="/assets/pca/fig_04.png">
</div>
<div class="col three caption">
  Figure 4: Principal components plotted as percent of variance explained
</div>

<div class="img_row" style="margin-right:1.5rem; margin-left:1.5rem;" >
  <img class="col two" style="float:left; padding-right: 1rem;" src="/assets/pca/fig_05_l.png">
  <img class="col two" style="float:right; padding-left: 1rem;" src="/assets/pca/fig_05_r.png">
</div>

<div class="col three caption">
  Figure 5: Left, signal response of principal components 1-3; right, histogram scores
</div>

### K-means Classification and Event Identification

Now that we have a waveform with which to use, we can use a classifier. In this exercise I use the K-means tool in MATLAB to comb through the data and 'classify' the inputs based on the PCA, counting each time a synapse event occurs. In this example each event occurred 587, 108, and 127 times respectively. There's a number of guides and videos on how K-means works.

<!-- <div class="img_row" > -->
  <img class="col three" src="/assets/pca/fig_06.png">
<!-- </div> -->

<div class="col three caption">
  Figure 6: Results of K-means classification
</div>
