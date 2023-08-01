#!/usr/bin/env python2

import numpy as np
import math
import matplotlib.pyplot as plt


np.random.seed(1)

def sigmoid(x):
    """
    args: x - some number
    return: some value between 0 and 1 based on sigmoid function
    """
    sigmoid = 1/(1+np.exp(-x))

    return sigmoid

def sigmoid_derivative(x):
    """
    args: x - some number
    return: derivative of sigmoid given x
    """
    sig_prime = x*(1-x)

    return sig_prime

def perceptron():

    """
    **********************************************
    create training dataset
    **********************************************
    """
    tempx = np.random.normal(6,2,size=100)
    tempy = np.random.normal(2,1,size=100)
    dat1 = np.array((tempx,tempy)).T

    tempx = np.random.normal(2,3,size=100)
    tempy = np.random.normal(8,1,size=100)
    dat2 = np.array((tempx,tempy)).T

    dat = np.append(dat1, dat2, axis=0) # [200x2]

    y = np.expand_dims(np.append(np.ones((100,1)),0*np.ones((100,1))),axis=1) # [200x1]


    """    shuffle dataset    """
    temp = np.append(dat,y,axis=1)
    np.random.shuffle(temp)
    dat = temp[:,:2]
    tempy = temp[:,-1]
    y = np.expand_dims(tempy,axis=1)


    """
    **********************************************
    create validation dataset
    **********************************************
    """
    v_tempx = np.random.normal(6,2,size=10)
    v_tempy = np.random.normal(2,1,size=10)
    v_dat1 = np.array((v_tempx,v_tempy)).T

    v_tempx = np.random.normal(2,3,size=10)
    v_tempy = np.random.normal(8,1,size=10)
    v_dat2 = np.array((v_tempx,v_tempy)).T

    v_dat = np.append(v_dat1, v_dat2, axis=0) # [10x2]

    v_y = np.expand_dims(np.append(np.ones((10,1)),0*np.ones((10,1))),axis=1) # [10x1]


    """    shuffle dataset    """
    v_temp = np.append(v_dat,v_y,axis=1)
    np.random.shuffle(v_temp)
    v_dat = v_temp[:,:2]
    v_tempy = v_temp[:,-1]
    v_y = np.expand_dims(v_tempy,axis=1)


    """
    **********************************************
    network parameters
    **********************************************
    """
    epochs = 50

    w = np.random.random((3,1)) # starting weight for each column (synapse)
    bias = np.ones((len(dat),1)) # bias
    v_bias = np.ones((len(v_dat),1)) # bias

    error_arr1 = np.zeros((epochs,1)) # training error
    error_arr2 = np.zeros((epochs,1)) # validation error

    """
    **********************************************
    perceptron single layer network
    **********************************************
    """
    print "Weights Before Training: "
    print w
    print

    for i in range(epochs):
        """
        neuron
        """
        input = dat
        input = np.append(input,bias,axis=1)

        v_input = v_dat
        v_input = np.append(v_input,v_bias,axis=1)

        xw = np.dot(input,w)
        v_y_hat = np.dot(v_input,w)
        y_hat = sigmoid(xw)

        error = y - y_hat
        v_error = v_y - v_y_hat


        error_arr1[i] = sum(error)
        error_arr2[i] = sum(v_error)

        adjustments = error * sigmoid_derivative(y_hat)

        w = w + np.dot(input.T,adjustments)


        # Validation phase
        v_input = v_dat
        v_input = np.append(v_input,v_bias,axis=1)

        v_y_hat = np.dot(v_input,w)

        v_error = v_y - v_y_hat
        error_arr2[i] = sum(v_error)

    print "Weights After Training: "
    print w
    print

    print "Network Percent Error (%):"
    percent_error=(sum(y-np.round(y_hat,0))/epochs)*100
    print percent_error[0]
    print

    y_hat = np.dot(input,w)
    v_y_hat = np.dot(v_input,w)

    """
    **********************************************
    plotting
    **********************************************
    """
    fig1 = plt.figure()
    plt.plot(dat1.T[0], dat1.T[1], "ro", label="dat1")
    plt.plot(dat2.T[0], dat2.T[1], "bo", label="dat2")
    plt.title("Perceptron Classification: Training Dataset")
    plt.xlim(-5,10)
    plt.ylim(-4,14)
    plt.legend()

    fig2 = plt.figure()
    plt.plot(dat1.T[0], dat1.T[1], "ro", label="dat1")
    plt.plot(dat2.T[0], dat2.T[1], "bo", label="dat2")
    for i in range(len(y_hat)):
    	if (y_hat[i]<0):
    		plt.plot(dat[i][0], dat[i][1],"b.")
    	else:
    		plt.plot(dat[i][0], dat[i][1],"r.")
    plt.title("Perceptron Classification: Trained Output")
    plt.xlim(-5,10)
    plt.ylim(-4,14)
    plt.legend()

    fig3 = plt.figure()
    plt.plot(abs(error_arr1), label="Error")
    plt.title("Network Percent Error")
    plt.xlabel("Epoch")
    plt.ylabel("Error Percent")
    plt.xlim(-2,epochs)
    plt.ylim(-2,110)
    plt.legend()

    fig4 = plt.figure()
    plt.plot(v_dat1.T[0], v_dat1.T[1], "ro", label="dat1")
    plt.plot(v_dat2.T[0], v_dat2.T[1], "bo", label="dat2")
    plt.title("Perceptron Classification: Validation Dataset")
    plt.xlim(-5,10)
    plt.ylim(-4,14)
    plt.legend()

    fig5 = plt.figure()
    plt.plot(v_dat1.T[0], v_dat1.T[1], "ro", label="dat1")
    plt.plot(v_dat2.T[0], v_dat2.T[1], "bo", label="dat2")
    for i in range(len(v_y_hat)):
    	if (v_y_hat[i]<0):
    		plt.plot(v_dat[i][0], v_dat[i][1],"b.")
    	else:
    		plt.plot(v_dat[i][0], v_dat[i][1],"r.")
    plt.title("Perceptron Classification: Validation Output")
    plt.xlim(-5,10)
    plt.ylim(-4,14)
    plt.legend()


def main():
    perceptron()
    plt.show()

if __name__ == '__main__':
    main()
