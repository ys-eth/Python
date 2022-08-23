#include "node.h"
#include "ht.h"
#include <stdbool.h>
#include <stdint.h>
#include "salts.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "speck.h"

struct HashTable {
    uint64_t salt[2]; // The salt to use for the hash function.
    uint32_t size; // The number of slots in the hash table.
    Node **slots; // The array of hash table items.
};

struct HashTableIterator {
    HashTable *table; // The hash table to iterate over.
    uint32_t slot; // The current slot the iterator is on.
};

HashTable *ht_create(uint32_t size) {
    HashTable *hash
        = (HashTable *) calloc(1, sizeof(HashTable)); // allocates memory for the hash table
    if (hash != NULL) { // checks if the hash table is not null
        hash->salt[0] = SALT_HASHTABLE_LO; // initializes the low salt for hashtable
        hash->salt[1] = SALT_HASHTABLE_HI; // initializes the high salt for hashtable
        hash->size = size; // sets the size for hash table
        Node **slots = (Node **) calloc(size, sizeof(Node *)); // allocates memory for the slots
        hash->slots = slots; // initializes the slots
        return hash; // returns hash table
    }
    return NULL;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < ht_size(*ht); i++) { // loop through the hashtable size
        if ((*ht)->slots[i] != NULL) { // if the slots of the hashtable is not equal to null
            node_delete(
                &(*ht)->slots[i]); // delete the node from the hash table for each slot iterated
        }
    }
    free((*ht)->slots); // free the hashtable slots
    ((*ht)->slots) = NULL; // set the hashtable slots to NULL
    free((*ht)); // free the hashtable
    *ht = NULL; // set the hashtable to NULL
}

uint32_t ht_size(HashTable *ht) {
    return ht->size; // get the size for the hash table
}

Node *ht_lookup(HashTable *ht, char *word) {
    uint32_t count = 0;
    uint32_t index
        = hash(ht->salt, word) % ht->size; // call the hash function when calculating the index

    while (count < ht->size) { // loop through count when it is less than the size of the hash table
        Node *node2 = ht->slots[index]; // initialize the node
        if (node2
            && strcmp(node2->word, word) == 0) { // if the 2nd node and the word from node 1 equal 0
            return node2;
        }

        index = (index + 1) % ht->size; // update index
        count += 1; // update count
    }

    return NULL;
}

Node *ht_insert(HashTable *ht, char *word) {
    uint32_t count = 0;
    uint32_t index
        = hash(ht->salt, word) % ht->size; // call the hash function when calculating the index

    while (count < ht->size) { // loop through count less than the size of the hash table
        if (ht->slots[index] == NULL) { // checks if the index of slots is null
            ht->slots[index] = node_create(word); // creates a node using word
            ht->slots[index]->count = 1; // updates the count in slots to 1
            return ht->slots[index];
        }

        if (strcmp(ht->slots[index]->word, word) == 0) { // compares the index word with input word
            ht->slots[index]->count++; // adds to the count
            return ht->slots[index]; // returns slots to the index
        }

        index = (index + 1) % ht->size; // updates index
        count += 1; // adds to the count
    }

    return NULL;
}

void ht_print(HashTable *ht) {
    HashTableIterator *hti = hti_create(ht); // creates a hash table iterator
    Node *n = NULL;
    while ((n = ht_iter(hti)) != NULL) { // while the hash table iterator exists, print out the node
        node_print(n);
    }
    hti_delete(&hti); //delete the hash table iterator
}

HashTableIterator *hti_create(HashTable *ht) {
    HashTableIterator *hashit = (HashTableIterator *) malloc(
        sizeof(HashTableIterator)); //allocates memory for the hash table iterator
    hashit->slot = 0; // initializes the slot
    hashit->table = ht; // initializes the table to the hashtable
    if (hashit != NULL) { // if hash table iterator exists, then return it
        return hashit;
    }
    return NULL;
}

void hti_delete(HashTableIterator **hti) {
    free(*hti); // frees the hash table iterator
    *hti = NULL; // sets the hash table iterator to NULL
}

Node *ht_iter(HashTableIterator *hti) {
    while (hti->slot != hti->table->size) { // while the slot is not equal to the table size
        if (hti->table->slots[hti->slot]
            != NULL) { // if the slot of the hash table iterator exists, update slot
            hti->slot++;
            return hti->table
                ->slots[hti->slot - 1]; // subtract from the table of the hash table iterator
        } else {
            hti->slot++; // update slot
        }
    }
    return NULL;
}
