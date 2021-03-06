//  
//  Random.cpp
//  QueueSystem
//
//  Create by Euryugasaki on 2014-03-25.
//  Copyright (c) 2014 Euryugasaki. All rights reserved.
// 

#include "Random.h"
#include <iostream>
#include <cmath>

// 生成[0,1)之间的一个随机值
double uniform()
{
    return (double)rand() / (RAND_MAX);
}
// 返回服从泊松分布的随机变量的一个随机值
double getPoisson(double lambda)
{
    int t = 0;
    double p = exp(-lambda);
    double f = p;
    double u = uniform();
    while (true)
    {
        if (f > u)
            break;
        t++;
        p = p*lambda / t;
        f += p;
    }
    return t;
}
// 返回服从负指数分布的随机变量的一个随机值
double getExponentail(double lambda)
{
    return -log(1 - uniform()) / lambda;
}


// 返回服从Gamma分布的随机变量的一个随机值：X～Gamma(alpha, beta)
double getGamma(double alpha, double beta)
{
    double value;
    if (alpha == 1){
        value = getExponentail(1);
    }
    else if (alpha<1){
        double b = (exp(1.0) + alpha) / exp(1.0);
        do{
            double u1 = uniform();
            double p = b*uniform();
            double y;
            if (p>1){
                y = -log((b - p) / alpha);
                if (u1<pow(y, alpha - 1)){
                    value = y;
                    break;
                }
            }
            else{
                y = pow(p, 1 / alpha);
                if (u1<exp(-y)){
                    value = y;
                    break;
                }
            }
        } while (1);
    }
    else {
        while (1)
        {
            double u1 = uniform();
            double u2 = uniform();
            double v = sqrt(2 * alpha - 1)*log(u2 / (1 - u2));
            double t = alpha*exp(v);
            if (log(u1*u2*u2)<alpha - log(4.0) + (alpha + sqrt(2 * alpha - 1))*v - t){
                value = t;
                break;
            }
        }
    }
    value *= beta;
    return value;
}

// 返回服从Beta分布的随机变量的一个随机值：X～Beta(alpha1, alpha2)
double getBeta(double alpha1, double alpha2)
{
    double u1 = getGamma(alpha1, 1);
    double u2 = getGamma(alpha2, 1);
    return u1 / (u1 + u2);
}

// 返回服从正态分布的随机变量的一个随机值：X～N(miu, sigma)
double getNormal(double miu, double sigma)
{
    double v1, v2, w, value;
    do{
        v1 = uniform() * 2 - 1;
        v2 = uniform() * 2 - 1;
        w = v1*v1 + v2*v2;
    } while (w>1);
    value = v1*sqrt(-2 * log(w) / w);
    value = value*sigma + miu;
    return value;
}

// 返回服从离散均匀分布的随机变量的随机值：http://en.wikipedia.org/wiki/Uniform_distribution_(discrete)
int getDiscreteUniform(int from, int to)
{
    return ( from + (int)((to - from + 1)*uniform()) );
}
// 返回服从几何分布的随机变量的随机值：X～Geo(p)
int getGeometric(double p)
{
    return (int)(log(1 - uniform()) / log(1 - p));
}
// 返回服从二项分布的随机变量的随机值：X～B(n, p)
int getBinomial(int n, double p)
{
    int s = 0;
    for (int i = 0; i<n; i++){
        if (uniform()<p)s++;
    }
    return s;
}
