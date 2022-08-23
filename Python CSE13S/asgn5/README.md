# Assignment 5: Public Key Cryptography (README.md)

## Short description:

	This assignment requires us to implement three programs: a key generator, encryptor, and decryptor. The keygenerator program will be in charge of key generation, producing RSA public and private key pairs. The encryption program will encrypt files using a public key, and the decryption program will decrypt the encrypted files using the corresponding private key. In the assignment, we will also need to implement two libraries and a random state module that will be used for each of these programs. Out of these two, one library should focus on holding functions relating to the mathematics behind RSA, while the other should contain implementations of routines for RSA. In addition, we will need to utilize a library which can be portrayed in other words as the GNU multiple precision arithmetic library.

## Build

        To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o keygen keygen.c encrypt encrypt.c decrypt decrypt.c" on the command line.
        If this doesn't work, type "make" on the command line with the Makefile from the directory.

## Running

        ./keygen ./encrypt ./decrypt

## Cleaning

        To clean, use "rm -f keygen.o keygen encrypt.o encrypt decrypt.o decrypt" on the command line.
        If this doesn't work, type "clean" on the command line.
