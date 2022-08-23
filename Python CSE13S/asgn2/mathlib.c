#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

//Exponential function
double Exp(double x) {
    double trm = 1.0;
    double sum = trm;
    double k = 1.0;

    while (trm > EPSILON) {
        trm = trm * (Abs(x) / k);
        sum += trm;
        k += 1.0;
    }

    if (x > 0) {
        return sum;
    } else {
        return (1.0 / sum);
    }
}

//modulus function designed for sine and cos
double modulus(double n, double m) {
    double r;
    int l = n / m;
    r = n - m * (l);
    if (n < 0) {
        return -Abs(r);
    } else {
        return Abs(r);
    }
}

// sine function
double Sin(double x) {
    double p = 3.141592653589797;
    x = modulus(x, 2 * p);
    double s = 1.0;
    double v = x;
    double t = x;
    double k = 3.0;
    while (Abs(t) > EPSILON) {
        t = t * (x * x) / ((k - 1) * k);
        s = -s;
        v += s * t;
        k += 2.0;
    }
    return v;
}

//cosine function
double Cos(double x) {
    double p = 3.141592653589797;
    x = modulus(x, 2 * p);
    double c = 1.0;
    double v = 1;
    double t = 1;
    double k = 2.0;
    while (Abs(t) > EPSILON) {
        t = t * (x * x) / ((k - 1) * k);
        c = -c;
        v += c * t;
        k += 2.0;
    }
    return v;
}

//square root function
double Sqrt(double x) {
    double z = 0.0;
    double y = 1.0;
    double f = 1.0;
    while (x > 1) {
        x /= 4.0;
        f *= 2.0;
    }
    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }
    return y * f;
}

//logarithmic function
double Log(double x) {
    double y = 1.0;
    double p = Exp(y);
    double e = 2.7182818284590455;
    double f = 0.0;
    while (x > e) {
        x /= e;
        f += 1.0;
    }
    while (Abs(p - x) > EPSILON) {
        y = y + x / p - 1;
        p = Exp(y);
    }
    return f + y;
}
