#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

void usage(void) { // Usage function for the main program //
    fprintf(stderr, "SYNOPSIS\n"
                    "   Decrypts data using RSA encryption.\n"
                    "   Encrypted data is encrypted by the encrypt program.\n"
                    "\n"
                    "USAGE\n"
                    "   ./decrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to decrypt (default: stdin).\n"
                    "   -o outfile      Output file for decrypted data (default: stdout).\n"
                    "   -d pvfile       Private key file (default: rsa.priv).\n");
}

// main function for the decrypt.c program //
int main(int argc, char **argv) {
    bool v = false;

    char *input = NULL;
    char *output = NULL;
    char *priv = "rsa.priv";
    uint64_t opt = 0; // initialized for the getopt switch cases //

    // Getopt switch cases for each of the options //
    while ((opt = getopt(argc, argv, "hvi:o:d:")) != -1) {
        switch (opt) {
        case 'h': usage(); return EXIT_FAILURE;
        case 'v': v = true; break;
        case 'i': input = optarg; break;
        case 'o': output = optarg; break;
        case 'd': priv = optarg; break;
        default: usage(); return EXIT_FAILURE;
        }
    }
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    FILE *pvfile = fopen(priv, "r"); // initialized to open the private key file //
    FILE *infile = stdin;

    // if the input is not equal to the output, then read the input file and print a stderr message //
    if (input != NULL) {
        infile = fopen(input, "r");
        if (infile == NULL) {
            fprintf(stderr, "Error Opening File\n");
            fclose(pvfile);
            mpz_clears(n, d, NULL);
            return EXIT_FAILURE;
        }
    }

    rsa_read_priv(n, d, pvfile); // reads the private key file from pvfile

    // prints the output for verbose
    if (v) {
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    // sets the output file to the stdout (default) //
    FILE *outfile = stdout;

    // if the output is not equal to the output, then read the output file and print a stderr message //
    if (output != NULL) {
        outfile = fopen(output, "w");
        if (outfile == NULL) {
            fprintf(stderr, "Error Writing File\n");
            fclose(pvfile);
            fclose(outfile);
            mpz_clears(n, d, NULL);
            return EXIT_FAILURE;
        }
    }

    rsa_decrypt_file(infile, outfile, n,
        d); // decrypts the contents of infile, writing the decrypted contents to outfile.
    fclose(pvfile); // closes the pvfile
    fclose(infile); // closes the infile
    fclose(outfile); // closes the outfile

    mpz_clears(n, d, NULL); // clears the mpz variables
}
