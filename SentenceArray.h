#ifndef SENTENCEARRAY_H
#define SENTENCEARRAY_H

struct Sentence {
    const char *raw;
    float score;
};

class SentenceArray {

    Sentence *sentences;
    unsigned int cap;
    unsigned int size;

    void expand() {
    }

public:

    SentenceArray(){
    }

    void add(Sentence sentence) {
    }

    void sort(unsigned int num) {
    }

    unsigned int length() {
    }

    Sentence& operator[](unsigned int index) {
    }

    ~SentenceArray() {
    }
};

#endif
