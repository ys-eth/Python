#include "functions.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//usage function utilized for the ./integrate blank cases
void usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "   Performs numerical integrations using composite Simpson's 1/3 rule.\n"
                    "\n"
                    "USAGE\n"
                    "   ./integ OPTIONS\n"
                    "\n"
                    "OPTIONS\n"
                    "   -a               sqrt(1 - x^4)\n"
                    "   -b               1/log(x)\n"
                    "   -c               exp(-x^2)\n"
                    "   -d               sin(x^2)\n"
                    "   -e               cos(x^2)\n"
                    "   -f               log(log(x))\n"
                    "   -g               sin(x)/x\n"
                    "   -h               exp(-x)/x\n"
                    "   -i               exp(exp(x))\n"
                    "   -j               sqrt(sin^2(x) + cos^2(x))\n"
                    "   -n partitions    Maximum number of partitions.\n"
                    "   -p low           Set low end of integral interval.\n"
                    "   -q high          Set high end of integral interval.\n"
                    "   -H               Display program synopsis and usage.\n");
}

//integrate function designed for overall code integration
double integrate(double (*f)(double x), double a, double b, uint32_t n) {
    double h = (b - a) / n; //calculates the sum of right side of the function
    double sum = f(a) + f(b); //calculates the sum of left side of the function
    for (uint32_t j = 2; j < n; j += 2) {
        sum += 2 * f(a + j * h); //calculates the sum of first sigma on simpsons one third rule
    }
    for (uint32_t j = 1; j <= n; j += 2) {
        sum += 4 * f(a + j * h); //calculates the sum of 2nd sigma on simpsons one third rule
    }
    sum *= h * 1 / 3; //takes sum and divides it by one third
    return sum;
}

// main function designed to take in bool as input and result usage as output if conditions not met
int main(int argc, char **argv) {

    int opt = 0;
    int n = 100;
    int s = 10;
    double p;
    double q;
    bool a_a = false;
    bool b_b = false;
    bool c_c = false;
    bool d_d = false;
    bool e_e = false;
    bool f_f = false;
    bool g_g = false;
    bool h_h = false;
    bool i_i = false;
    bool j_j = false;

    //while loop with switch cases for every condition on usage page
    while ((opt = getopt(argc, argv, "abcdefghijn:p:q:H")) != -1) {
        switch (opt) {
        case 'a': a_a = true; break;
        case 'b': b_b = true; break;
        case 'c': c_c = true; break;
        case 'd': d_d = true; break;
        case 'e': e_e = true; break;
        case 'f': f_f = true; break;
        case 'g': g_g = true; break;
        case 'h': h_h = true; break;
        case 'i': i_i = true; break;
        case 'j': j_j = true; break;
        case 'n': n = strtod(optarg, NULL); break;
        case 'p': p = strtod(optarg, NULL); break;
        case 'q': q = strtod(optarg, NULL); break;
        case 'H': usage(); break;
        default: usage(); return EXIT_FAILURE;
        }
    }
    if ((a_a || b_b || c_c || d_d || e_e || f_f || g_g || h_h || i_i || j_j) == false) {
        usage();
    } // Multiple if statements with for loops checking integrate
    if (a_a) {
        printf("sqrt(1-x^4),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(a, p, q, s));
        }
    }

    if (b_b) {
        printf("1/log(x),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(b, p, q, s));
        }
    }

    if (c_c) {
        printf("exp(-x^2),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(c, p, q, s));
        }
    }

    if (d_d) {
        printf("sin(x^2),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(d, p, q, s));
        }
    }

    if (e_e) {
        printf("cos(x^2),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(e, p, q, s));
        }
    }

    if (f_f) {
        printf("log(log(x)),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(f, p, q, s));
        }
    }

    if (g_g) {
        printf("sin(x)/x,%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(g, p, q, s));
        }
    }

    if (h_h) {
        printf("exp(-x)/x, %f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(h, p, q, s));
        }
    }

    if (i_i) {
        printf("exp(exp(x)),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(i, p, q, s));
        }
    }

    if (j_j) {
        printf("sqrt(sin^2(x) + cos^2(x)),%f,%f,%d\n", p, q, s);
        for (int s = 2; s <= n; s += 2) {
            printf("%d,%0.15f\n", s, integrate(j, p, q, s));
        }
    }
    return 0;
}
