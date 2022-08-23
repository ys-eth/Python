#include "metric.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "ht.h"
#include "parser.h"
#include <regex.h>
#include "bf.h"
#include "text.h"
#include <string.h>

#define WORD "[a-zA-Z]+(('|-)[a-zA-Z]+)*"

extern uint32_t noiselimit; // Number of noise words to filter out.

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};

Text *text_create(FILE *infile, Text *noise) {
    Text *txt = (Text *) malloc(sizeof(Text)); // allocates memory for the text
    txt->ht = ht_create(1 << 19); // creates the hash table
    txt->bf = bf_create(1 << 21); // creates the bloom filter
    regex_t re; // sets the regex expression
    txt->word_count = 0; // initializes the word count to 0
    char *word = NULL; // sets the character word to null

    // if statements used to free hash table, bloom filter, and the regex
    if (txt == NULL) {
        return NULL;
    }

    if (txt->ht == NULL) {
        free(txt);
        txt = NULL;
        return NULL;
    }
    if (txt->bf == NULL) {
        free(txt->ht);
        txt->ht = NULL;
        free(txt);
        txt = NULL;
        return NULL;
    }
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        regfree(&re);
        free(txt->bf);
        txt->bf = NULL;
        free(txt->ht);
        txt->ht = NULL;
        free(txt);
        txt = NULL;
        return NULL;
    }

    // text
    while ((word = next_word(infile, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i++) { // loops through the length of the word
            word[i] = tolower(word[i]); // sets the word to lower case based on the iterations
        }
        if (noise == NULL) { // if there is no noise in the file
            ht_insert(txt->ht, word); // insert the word into the hash table
            bf_insert(txt->bf, word); // insert the word into the bloom filter
            txt->word_count++; // add to the word count
        }
        if (noise != NULL) { // if there is noise in the file
            if (text_contains(noise, word) == false) { // if the word doesnt contain noise
                ht_insert(txt->ht, word); // insert the word into the hash table
                bf_insert(txt->bf, word); // insert the word into the bloom filter
                txt->word_count++; // add to the word count
            }
        }
    }
    regfree(&re); // free the regex
    return txt; // return the text
}

void text_delete(Text **text) {
    ht_delete(&(*text)->ht); // delete the hash table pointer
    bf_delete(&(*text)->bf); // delete the bloom filter pointer
    free(*text); // free the text
    *text = NULL; // set the text to null
}

double text_dist(Text *text1, Text *text2, Metric metric) {
    double freq1 = 0;
    double freq2 = 0;
    double metr = 0;
    if (metric == EUCLIDEAN) { // if the metric is EUCLIDEAN
        HashTableIterator *hi1 = hti_create(text1->ht); // create a hash table iterator
        for (Node *a = ht_iter(hi1); a != NULL; a = ht_iter(hi1)) {
            bool b = text_contains(text2, a->word);
            if (b != false) {
                freq1 = text_frequency(text1, a->word);
                freq2 = text_frequency(text2, a->word);
                double temp = freq1 - freq2;
                if (temp < 0.0) {
                    temp = -temp;
                }
                metr += temp * temp;
            }
        }
        HashTableIterator *hi2 = hti_create(text2->ht);
        for (Node *a = ht_iter(hi2); a != NULL; a = ht_iter(hi2)) {
            bool b = text_contains(text1, a->word);
            if (b != false) {
                freq1 = text_frequency(text1, a->word);
                freq2 = text_frequency(text2, a->word);
                double temp = freq1 - freq2;
                if (temp < 0.0) {
                    temp = -temp;
                }
                metr += temp * temp;
            }
        }
        metr += sqrt(metr);
        return metr;
    }

    if (metric == COSINE) {
        HashTableIterator *hi1 = hti_create(text1->ht); // create a hash table iterator
        for (Node *a = ht_iter(hi1); a != NULL; a = ht_iter(hi1)) {
            bool b = text_contains(text2, a->word);
            if (b != false) {
                freq1 = text_frequency(text1, a->word);
                freq2 = text_frequency(text2, a->word);
                double temp = freq1 * freq2;
                if (temp < 0.0) {
                    temp = -temp;
                }
                metr += temp;
            }
        }
        metr = 1 - metr;
        return metr;
    }

    if (metric == MANHATTAN) {
        HashTableIterator *hi1 = hti_create(text1->ht); // create a hash table iterator
        for (Node *a = ht_iter(hi1); a != NULL; a = ht_iter(hi1)) {
            bool b = text_contains(text2, a->word);
            if (b != false) {
                freq1 = text_frequency(text1, a->word);
                freq2 = text_frequency(text2, a->word);
                double temp = freq1 - freq2;
                if (temp < 0.0) {
                    temp = -temp;
                }
                metr += temp;
            }
        }
        HashTableIterator *hi2 = hti_create(text2->ht);
        for (Node *a = ht_iter(hi2); a != NULL; a = ht_iter(hi2)) {
            bool b = text_contains(text1, a->word);
            if (b != false) {
                freq1 = text_frequency(text1, a->word);
                freq2 = text_frequency(text2, a->word);
                double temp = freq1 - freq2;
                if (temp < 0.0) {
                    temp = -temp;
                }
                metr += temp;
            }
        }
        return metr;
    }
    return 0;
}

double text_frequency(Text *text, char *word) {
    Node *n = ht_lookup(text->ht, word); // lookup the word and set it equal to the node
    if (n != NULL) { // if the node exists
        double word1 = (double) ht_lookup(text->ht, word)->count
                       / text->word_count; // looks up the word and divides by the word count
        return word1;
    }
    return 0;
}

bool text_contains(Text *text, char *word) {
    if (bf_probe(text->bf, word) == true) { // probes the bloom filter for word if true
        return ht_lookup(text->ht, word); // returns the word found from looking in the hash table
    }
    return false;
}

void text_print(Text *text) {
    printf("word_count = %d\n", text->word_count); // prints the word count
    ht_print(text->ht);
}
