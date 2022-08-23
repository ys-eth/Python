#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "randstate.h"
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

void usage(void) { // Usage function for the main program //
    fprintf(stderr, "SYNOPSIS\n"
                    "   Generates an RSA public/private key pair.\n"
                    "\n"
                    "USAGE\n"
                    "   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -b bits         Minimum bits needed for public key n.\n"
                    "   -c confidence   Miller-Rabin iterations for testing primes (default: 50).\n"
                    "   -n pbfile       Public key file (default: rsa.pub).\n"
                    "   -d pvfile       Private key file (default: rsa.priv).\n"
                    "   -s seed         Random seed for testing.\n");
}

// main function for the keygen.c program //
int main(int argc, char **argv) {
    uint64_t seed = time(NULL);
    uint64_t nbits = 256, iters = 50;
    bool v = false;
    char *pub = "rsa.pub";
    char *priv = "rsa.priv";

    uint64_t opt = 0; // initialized for the getopt switch cases //

    // Getopt switch cases for each of the options //
    while ((opt = getopt(argc, argv, "hb:i:n:d:s:v")) != -1) {
        switch (opt) {
        case 'h': usage(); return EXIT_FAILURE;
        case 'b': nbits = strtoul(optarg, NULL, 10); break;
        case 'i': iters = strtoul(optarg, NULL, 10); break;
        case 'n': pub = optarg; break;
        case 'd': priv = optarg; break;
        case 's': seed = strtoul(optarg, NULL, 10); break;
        case 'v': v = true; break;
        default: usage(); return EXIT_FAILURE;
        }
    }
    char *username = getenv("USER"); // gets the username of the user in the form of a char
    FILE *pbfile = fopen(pub, "w"); // initialized for file pub input //
    FILE *pvfile = fopen(priv, "w"); // initialized for file priv input//
    mpz_t b, p, q, n, e, d, m, s;
    mpz_inits(b, p, q, n, e, d, m, s, NULL); // initializes the mpz variables

    uint64_t num = fileno(pvfile);
    fchmod(num, 0600);

    randstate_init(seed); // initializes the random seed
    rsa_make_pub(p, q, n, e, nbits,
        iters); // makes the public key for two large primes p and q along with their product and exponent
    rsa_make_priv(
        d, e, p, q); // makes the private key for two large primes p and q and public exponent e
    mpz_set_str(m, username, 62); // sets the string of base 62 for username equal to m
    rsa_sign(s, m, d, n); // signs the rsa message
    rsa_write_pub(n, e, s, username, pbfile); // writes the public key file to pbfile
    rsa_write_priv(n, d, pvfile); //writes the private key file to pvfile
    fclose(pbfile); // closes pbfile
    fclose(pvfile); // closes pvfile

    // prints the output for verbose
    if (v == true) {
        printf("user = %s\n", username);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%zu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%zu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    mpz_clears(b, p, q, n, e, d, m, s, NULL); // clears mpz variables
    randstate_clear(); // clears randstate seed
}
