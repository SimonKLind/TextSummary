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
        Node **old = buckets;
        unsigned int old_num = num_buckets;
        num_buckets <<= 1;
        buckets = new Node*[num_buckets];
        for(unsigned int i=0; i<num_buckets; ++i) buckets[i] = 0;
        Node *temp;
        for(unsigned int i=0, index; i<old_num; ++i) {
            temp = old[i];
            while(temp) {
                old[i] = old[i]->next;
                index = string_hash(temp->word)&(num_buckets-1);
                temp->next = buckets[index];
                buckets[index] = temp;
                temp = old[i];
            }
        }
        delete[] old;
    }

public:

    WordMap(): num_buckets(16), size(0) {
        buckets = new Node*[16];
        for(unsigned int i=0; i<16; ++i) buckets[i] = 0;
    }

    void add(const char *word) {
        unsigned int index = string_hash(word)&(num_buckets-1);
        Node *temp = buckets[index];
        while(temp) {
            if(string_equals(word, temp->word)) {
                ++temp->count;
                return;
            }
            temp = temp->next;
        }
        temp = buckets[index];
        buckets[index] = new Node;
        *buckets[index] = (Node) { word, 1, temp };
        if(++size >= 0.75f*num_buckets) expand();
    }

    unsigned int operator[](const char *word) {
        unsigned int index = string_hash(word)&(num_buckets-1);
        Node *temp = buckets[index];
        while(temp) {
            if(string_equals(word, temp->word)) {
                return temp->count;
            }
            temp = temp->next;
        }
        return 0;
    }

    void print() {
        for(unsigned int i=0; i<num_buckets; ++i) {
            Node *temp = buckets[i];
            std::cout << "Index " << i << ": ";
            while(temp) {
                for(unsigned int j=0; isAlpha(temp->word[j]); ++j) std::cout << temp->word[j];
                std::cout << " -> " << temp->count << "\t";
                temp = temp->next;
            }
            std::cout << '\n';
        }
    }

    ~WordMap() {
        Node *temp, *next;
        for(unsigned int i=0; i<num_buckets; ++i) {
            temp = buckets[i];
            while(temp) {
                next = temp->next;
                delete temp;
                temp = next;
            }
        }
        delete[] buckets;
    }
};

#endif
