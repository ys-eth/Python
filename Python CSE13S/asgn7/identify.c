#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"
#include "ht.h"
#include "bv.h"
#include "text.h"
#include "pq.h"
#include <getopt.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void usage(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "    Identifies the author of some anonymous text passed through stdin.\n"
                    "    Computes k-nearest neighbors, where k = 1 by default.\n"
                    "    The number of noise words that are removed is tunable.\n"
                    "    Uses either Euclidean, Manhattan, or cosine distance as metric.\n"
                    "\n"
                    "USAGE\n"
                    "    ./identify.c [OPTIONS]\n"
                    "\n"
                    "OPTIONS\n"
                    "    -d database     Database of authors and texts [default: lib.db]\n"
                    "    -k matches      Set number of top matches to display [default: 5]\n"
                    "    -n noisefile    Set file of words to ignore [default: noise.txt]\n"
                    "    -l limit        Set noise word limit [default: 100]\n"
                    "    -e              Set distance metric as Euclidean distance [default]\n"
                    "    -m              Set distance metric as Manhattan distance\n"
                    "    -c              Set distance metric as cosine distance\n"
                    "    -v              Enable verbose printing of program run\n"
                    "    -h              Display program help and usage\n");
}

// main function for the identify.c program //
int main(int argc, char **argv) {
    char const *optd = "lib.db";
    char const *optn = "noise.txt";
    int optk = 5;
    int optl = 100;
    Metric metric = EUCLIDEAN;

    // Getopt switch cases for each of the options //
    int opt;
    while ((opt = getopt(argc, argv, "d:n:k:l:emch")) != -1) {
        switch (opt) {
        case 'd': optd = optarg; break;
        case 'n': optn = optarg; break;
        case 'k': optk = atoi(optarg); break;
        case 'l': optl = atoi(optarg); break;
        case 'e': metric = EUCLIDEAN; break;
        case 'm': metric = MANHATTAN; break;
        case 'c': metric = COSINE; break;
        case 'h':
        default: usage(); return EXIT_FAILURE;
        }
    }
    FILE *noisefile = fopen(optn, "r");
    if (noisefile == NULL) {
        fprintf(stderr, "unable to open noisefile %s\n", optn);
        perror(argv[0]);
        exit(1);
    }

    Text *noisetxt = text_create(noisefile, NULL);

    Text *anontxt = text_create(stdin, noisetxt);

    FILE *authordbfile = fopen(optd, "r");

    if (authordbfile == NULL) {
        fprintf(stderr, "unable to open authordbfile %s\n", optd);
        perror(argv[0]);
        exit(1);
    }
    char buffer[1024];
    int n;
    if (!fgets(buffer, sizeof(buffer), authordbfile) || sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "unable to read number of author text pairs.\n");
        exit(1);
    }

    typedef struct AuthorTexts {
        char *author;
        char const *path;
        Text *txt;
    } AuthorTexts;

    AuthorTexts *author_texts = (AuthorTexts *) calloc(n, sizeof(AuthorTexts));

    PriorityQueue *pq = pq_create(n);
    for (int i = 0; i < n; i++) {
        if (author_texts[i].txt != NULL) {
            double dist = text_dist(anontxt, author_texts[i].txt, metric);
            printf("%d) %s [%f]\n", i, author_texts[i].author, dist);
            enqueue(pq, author_texts[i].author, dist);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!fgets(buffer, sizeof(buffer), authordbfile)) {
            fprintf(stderr, "unable to read %d author from authordbfile.\n", i);
            exit(1);
        }

        buffer[strlen(buffer) - 1] = 0;
        author_texts[i].author = strdup(buffer);

        if (!fgets(buffer, sizeof(buffer), authordbfile)) {
            fprintf(stderr, "unable to read %d path from authordbfile.\n", i);
            exit(1);
        }

        buffer[strlen(buffer) - 1] = 0;
        author_texts[i].path = strdup(buffer);

        FILE *authorfile = fopen(author_texts[i].path, "r");
        if (authorfile != NULL) {
            author_texts[i].txt = text_create(authorfile, noisetxt);
            double dist = text_dist(anontxt, author_texts[i].txt, metric);
            enqueue(pq, author_texts[i].author, dist);
        }
    }

    char *author;
    double dist;
    int cu = 0;
    bool de = true;
    printf("Top %u, metric: %s, noise limit: %u\n", optk, metric_names[metric], optl);
    while (cu < optk && de) {
        de = dequeue(pq, &author, &dist);
        printf("%d) %s [%f]\n", cu + 1, author, dist);
        cu++;
    }
}
