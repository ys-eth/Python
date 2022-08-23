#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

void usage(void) { // Usage function for the main program //
    fprintf(stderr, "SYNOPSIS\n"
                    "   Encrypts data using RSA encryption.\n"
                    "   Encrypted data is decrypted by the decrypt program.\n"
                    "\n"
                    "USAGE\n"
                    "   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to encrypt (default: stdin).\n"
                    "   -o outfile      Output file for encrypted data (default: stdout).\n"
                    "   -n pbfile       Public key file (default: rsa.pub).\n");
}

// main function for the encrypt.c program //
int main(int argc, char **argv) {
    bool v = false;
    char *pub = "rsa.pub";
    char *input = NULL;
    char *output = NULL;

    uint64_t opt = 0; // initialized for the getopt switch cases //

    // Getopt switch cases for each of the options //
    while ((opt = getopt(argc, argv, "hvi:o:n:")) != -1) {
        switch (opt) {
        case 'h': usage(); return EXIT_FAILURE;
        case 'v': v = true; break;
        case 'i': input = optarg; break;
        case 'o': output = optarg; break;
        case 'n': pub = optarg; break;
        default: usage(); return EXIT_FAILURE;
        }
    }

    char username[256]; // initializes the username to the base 256 //
    FILE *pbfile = fopen(pub, "r"); // initialized for input //
    FILE *infile = stdin; // sets infile to standard file stdin //

    // if input is not equal to the file, then print a stderr message //
    if (input != NULL) {
        infile = fopen(input, "r");
        if (infile == NULL) {
            fprintf(stderr, "Error Opening File\n");
            return EXIT_FAILURE;
        }
    }

    mpz_t m, n, e, s;
    mpz_inits(m, n, e, s, NULL); // intializes mpz variables
    rsa_read_pub(n, e, s, username, pbfile); // reads a public rsa key from pbfile

    // prints the verbose output
    if (v) {
        printf("user = %s\n", username);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    mpz_set_str(m, username, 62); // set the username with base 62 to the string message

    // if rsa is not verified, print exit failure
    if (!rsa_verify(m, s, e, n)) {
        fclose(pbfile);
        fclose(infile);
        mpz_clears(m, s, e, n, NULL);
        return EXIT_FAILURE;
    }

    FILE *outfile = stdout;

    // if output is not valid, print exit failure
    if (output != NULL) {
        outfile = fopen(output, "w");
        if (outfile == NULL) {
            fprintf(stderr, "Error Writing File\n");
            mpz_clears(m, s, e, n, NULL);
            return EXIT_FAILURE;
        }
    }

    //prints encrypt file contents to infile
    rsa_encrypt_file(infile, outfile, n, e);

    fclose(pbfile); // closes pbfile //
    fclose(infile); // closes infile //
    fclose(outfile); // close outfile //

    mpz_clears(m, n, e, s, NULL); // clears mpz variables //
}
