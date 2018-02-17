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
        Sentence *old = sentences;
        cap <<= 1;
        sentences = new Sentence[cap];
        for(unsigned int i=0; i<size; ++i) sentences[i] = old[i];
        delete[] old;
    }

public:

    SentenceArray(): cap(16), size(0) {
        sentences = new Sentence[16];
    }

    void add(Sentence sentence) {
        sentences[size++] = sentence;
        if(size == cap) expand();
    }

    void sort(unsigned int num) {
        Sentence temp;
        for(unsigned int i=0; i<size && i<num; ++i) {
            float max = sentences[i].score;
            unsigned int maxIndex = i;
            for(unsigned int j=i+1; j<size; ++j) {
                if(sentences[j].score > max) {
                    max = sentences[j].score;
                    maxIndex = j;
                }
            }
            temp = sentences[i];
            sentences[i] = sentences[maxIndex];
            sentences[maxIndex] = temp;
        }
    }

    unsigned int length() {
        return size;
    }

    Sentence& operator[](unsigned int index) {
        return sentences[index];
    }

    ~SentenceArray() {
        delete[] sentences;
    }
};

#endif
