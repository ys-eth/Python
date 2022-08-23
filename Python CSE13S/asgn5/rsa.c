#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"
#include <stdlib.h>
#include <assert.h>

// lcm function created to calculate the least common multiple for a prime # //
void lcm(mpz_t l, mpz_t a, mpz_t b) {
    mpz_t t, ab, g;
    mpz_inits(t, ab, g, NULL); // initializes mpz variables
    mpz_mul(t, a, b);
    mpz_abs(ab, t);
    gcd(g, a, b); // computes the greatest common divisor of a and b
    mpz_tdiv_q(l, ab, g);
    mpz_clears(t, ab, g, NULL);
}

// Creates parts of a new RSA public key: two large primes p and q, their product n, and the public exponent e. //
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t l, gl, p1, q1;
    mpz_inits(l, gl, p1, q1, NULL); // initializes mpz variables //
    uint64_t pbits = (rand() % (nbits / 2)) + (nbits / 4); // calculates pbits
    uint64_t qbits = nbits - pbits; // calculates qbits
    make_prime(p, pbits, iters); // checks p and q and makes them prime #'s //
    make_prime(q, qbits, iters);
    mpz_mul(n, p, q); // calculates the product of the two prime numbers
    size_t x = mpz_sizeinbase(n, 2);
    while (x < nbits) { // runs a loop to make numbers prime when x is less than nbits
        make_prime(q, qbits, iters);
        mpz_mul(n, p, q);
        x = mpz_sizeinbase(n, 2);
    }

    make_prime(q, qbits, iters); // makes q into a prime number
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    lcm(l, p1, q1); // calls lcm function to compute the least common multiple between p1 and q1
    mpz_mul(n, p, q); // multiplies the product of two prime numbers
    mpz_urandomb(e, state, nbits);
    gcd(gl, e, l); // computes the greatest common divisor of e and l
    while (
        mpz_cmp_ui(gl, 1)
        != 0) { // runs a while loop to check when gl is equal to 1, if so then compute the greatest common divisor
        mpz_urandomb(e, state, nbits);
        gcd(gl, e, l);
    }
    mpz_clears(l, gl, p1, q1, NULL);
}

// Writes a public RSA Key to pbfile.
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

// Reads a public RSA Key to pbfile.
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

// Creates a new RSA private key when given two primes and an exponent.
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t l, p1, q1, m;
    mpz_inits(l, p1, q1, m, NULL);
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    lcm(l, p1, q1); // calls the lcm function to find the least common multiple between p1 and q1
    mod_inverse(d, e, l); // calculates the inverse modular of e and l
    mpz_clears(l, p1, q1, m, NULL);
}

// Writes a private RSA Key to pvfile.
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

// Reads a private RSA Key to pvfile.
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

// performs RSA encryption, computing ciphertext c by encrypting message m using public exponent e and modulus n.
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

// Encrypts the contents of infile, writing the encrypted message to outfile.
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {

    mpz_t c, m;
    mpz_inits(c, m, NULL); // initializes mpz variables
    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8; // calculates the block size k.
    uint8_t *buffer = malloc(sizeof(uint8_t) * k); // creates heap memory array
    buffer[0] = 0xFF;
    size_t numBytesRead = fread(buffer + 1, sizeof(uint8_t), k - 1,
        infile); // reads from the heap and calculates the bytes read
    while (numBytesRead > 0) {
        mpz_import(m, numBytesRead + 1, 1, sizeof(uint8_t), 1, 0,
            buffer); // imports bytes read and outputs value to m
        rsa_encrypt(c, m, e, n); // encrypts RSA message
        gmp_fprintf(outfile, "%Zx\n", c); // prnts message from the outfile
        numBytesRead = fread(buffer + 1, sizeof(uint8_t), k - 1,
            infile); // reads from the heap and calculates the bytes read
    }
    free(buffer); // frees buffer //
    mpz_clears(c, m, NULL); // clears mpz vars //
}

// Performs RSA decryption, computingmessage m by decrypting ciphertext c using private key d and public modulus n.
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n); // calls pow mod function with the message
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {

    mpz_t c, m;
    mpz_inits(c, m, NULL); //initializes mpz variables
    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8, k1 = 1; //calculates block size
    uint8_t *block = malloc(sizeof(uint8_t) * k); // creates heap memory and stores it on the stack
    while (gmp_fscanf(infile, "%Zx\n", m)
           != EOF) { //scans infile and writes decrypted message to the heap
        rsa_decrypt(c, m, d, n);
        mpz_export(block, &k1, 1, sizeof(uint8_t), 1, 0, c);
        fwrite(block + 1, sizeof(uint8_t), k1 - 1,
            outfile); // writes outfile with the decrypted message
    }
    free(block); // frees block //
    mpz_clears(c, m, NULL); // clears mpz variables //
}

// Performs RSA signing, producing signature s by signing message m using private key d and public modulus n.
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

// Performs RSA verification, returning true if signature s is verified and false otherwise.
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n); // calls power mod to calculate the modulus of a exponent//
    if (mpz_cmp(t, m) == 0) { // compares t with m //
        mpz_clear(t); // clears mpz variable //
        return true;
    } else {
        mpz_clear(t);
        return false;
    }
}
