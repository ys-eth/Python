#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "randstate.h"

// designed to compute the greatest common divisor of a and b, storing the value of the computed divisor in d. //
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    // initializes mpz variables
    mpz_t t, tmpa, tmpb;
    mpz_inits(t, tmpa, tmpb, NULL);
    mpz_set(tmpa, a);
    mpz_set(tmpb, b);
    while (mpz_cmp_ui(tmpb, 0) != 0) {
        mpz_set(t, tmpb);
        mpz_mod(tmpb, tmpa, tmpb);
        mpz_set(tmpa, t);
    }
    mpz_set(d, tmpa);
    mpz_clears(t, tmpa, tmpb, NULL);
}

// computes the inverse i of a modulo n. When mod inverse is not found, it will set i to zero//
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

    // initializes mpz variables
    mpz_t m, m1, s, s1, r, r1, t, t1, temp, temp1, q;
    mpz_inits(m, m1, s, s1, r, r1, t, t1, temp, temp1, q, NULL);
    mpz_set(r, n);
    mpz_set(r1, a);
    mpz_set_ui(m, 0);
    mpz_set_ui(s, 0);
    mpz_set_ui(m1, 0);
    mpz_set_ui(s1, 0);
    mpz_set_ui(q, 0);
    mpz_set_ui(t, 0);
    mpz_set_ui(t1, 1);
    while (mpz_cmp_ui(r1, 0) != 0) {
        mpz_fdiv_q(q, r, r1); // creates first equation r - r1

        mpz_set(temp, r); //sets temp var to r
        mpz_set(r, r1);

        mpz_mul(m, q, r1);
        mpz_sub(s, temp, m); //subtracts temp var from m
        mpz_set(r1, s);

        mpz_set(temp1, t);
        mpz_set(t, t1);
        mpz_mul(m1, q, t1); // multiplies q and t1
        mpz_sub(s1, temp1, m1);
        mpz_set(t1, s1); // sets t to return final output
    }
    if (mpz_cmp_ui(r, 1) > 0) { // checks if r is greater than 1, then returns no inverse//
        mpz_set_ui(i, 0);
        mpz_clears(m, m1, s, s1, r, r1, t, t1, temp, temp1, q, NULL);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) { // checks if t is less than 0, if so then returns t //
        mpz_add(t, t, n);
    }
    mpz_set(i, t);
    mpz_clears(
        m, m1, s, s1, r, r1, t, t1, temp, temp1, q, NULL); //clears mpz variables to avoid errors //
    return;
}

// computes fast modular exponentiation, computing base raise to the exponent power modulo modulus, and stores output.//
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p, tmp;
    mpz_inits(v, p, tmp, NULL); // initializes mpz variables
    mpz_set_ui(v, 1); // sets v equal to 1
    mpz_set(p, base);
    mpz_set(tmp, exponent);
    while (mpz_cmp_ui(tmp, 0) > 0) { // creates a while loop that runs when d is greater than 0
        if (mpz_odd_p(tmp) != 0) { // If tmp is odd, then set v equal to v times p
            mpz_mul(v, v, p); // multiplies v and p together
            mpz_mod(v, v, modulus); // divides v and modulus
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);
        mpz_fdiv_q_ui(tmp, tmp, 2); // stores output in tmp
    }
    mpz_set(out, v); // sets out equal to v, allowing output to finish running
    mpz_clears(v, p, tmp, NULL); // clears mpz variables to avoid valgrind errors
    return;
}

// conducts the Miller-Rabin test to indiciate whether or not n is a prime//
bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t temp, temp2, temp3, r, y, t, j, a, s, s1;
    mpz_inits(temp, temp2, temp3, r, y, t, j, a, s, s1, NULL); // initializes mpz variables
    mpz_sub_ui(temp, n, 1); // subtracts 1 from n
    mpz_set_ui(temp2, 2);
    mpz_sub_ui(temp3, n, 3);
    mpz_set_ui(s, 0);
    mpz_sub_ui(r, n, 1);

    if (mpz_cmp_ui(n, 0) == 0
        || mpz_even_p(n) != 0) { // compares if y is not equal to 1 and if y is not equal to n - 1
        mpz_clears(temp, temp2, temp3, r, y, t, j, a, s, s1,
            NULL); // clears mpz variables to avoid valgrind errors
        return false;
    }

    if (mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 2) == 0
        || mpz_cmp_ui(n, 3) == 0) { //checks if n = 1, n = 2, n = 3 //
        mpz_clears(temp, temp2, temp3, r, y, t, j, a, s, s1, NULL); // clears mpz variables
        return true;
    }

    while (mpz_even_p(r) != 0) { // loops through conditions if r is an even number
        mpz_add_ui(s, s, 1);
        mpz_tdiv_q(r, r, temp2);
    }
    mpz_sub_ui(temp, temp, 3);
    mpz_set_ui(a, 0);
    mpz_set_ui(s, 0);
    mpz_sub_ui(temp2, n, 1);
    mpz_sub_ui(s1, s, 1);
    mpz_set_ui(j, 1);
    mpz_set_ui(t, 2);
    for (uint64_t i = 0; i < iters;
         i++) { // sets a for loop that checks if loops when iters is greater than i
        mpz_urandomm(a, state, temp); // set a equal to the random state
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n); // makes a call to the power mod function
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, temp2) != 0) { // checks if y = 1 and y = temp2 //
            mpz_set_ui(j, 1);
            while (mpz_cmp(j, s1) <= 0
                   && mpz_cmp(y, temp2) != 0) { // while j = s1 and y = temp2, then call pow_mod //
                pow_mod(y, y, t, n); // calls pow_mod
                if (mpz_cmp_ui(y, 1) == 0) { // checks if y = 1 //
                    mpz_clears(temp, temp2, temp3, r, y, t, j, a, s, s1, NULL); // clears mpz vars
                    return false;
                }
                mpz_add_ui(j, j, 1); // adds the output back to j
            }
            if (mpz_cmp(y, temp2) != 0) { // checks if y = temp2 //
                mpz_clears(temp, temp2, temp3, r, y, t, j, a, s, s1, NULL); //clears mpz vars
                return false;
            }
        }
    }
    mpz_clears(temp, temp2, temp3, r, y, t, j, a, s, s1, NULL); //clears mpz vars
    return true;
}

// Generates a new prime number stored in p, which is tested using is_prime //
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t v, t, r;
    mpz_inits(v, t, r, NULL); // initializes mpz variables
    mpz_set_ui(t, 2); // sets t = 2//
    mpz_pow_ui(v, t, bits); // sets v = t^bits//
    while (is_prime(p, iters) != true) { // runs through a loop if p is a prime //
        mpz_rrandomb(p, state, bits); // set p to a random var
        mpz_add(p, p, v); // add prime # back to the random var
    }
    mpz_clears(v, t, r, NULL); //clear mpz vars
    return;
}
