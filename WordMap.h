#ifndef WORDMAP_H
#define WORDMAP_H

#include "StringFuncs.h"

class WordMap {

    struct Node {
        const char *word;
        unsigned int count;
        Node *next;
    };

    Node **buckets;
    unsigned int num_buckets;
    unsigned int size;

    void expand() {
    }

public:

    WordMap(){
    }

    void add(const char *word) {
    }

    unsigned int operator[](const char *word) {
    }

    void print() {
    }

    ~WordMap() {
    }
};

#endif
