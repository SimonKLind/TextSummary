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
		Sentence * copy = sentences;
		cap <<= 1;
		sentences = new Sentence[cap];
		for (int i = 0; i < size; i++) {
			sentence[i] = copy[i];
		}
		delete[] copy;
    }

public:

    SentenceArray(){
		size = 0;
		cap = 16;
		sentences = new Sentence[16];
    }

    void add(Sentence sentence) {
		sentences[size++] = sentence;
		if (size == cap) expand();
    }

	void sort(unsigned int num) {
		int min;
		int minIndex;
		for (int i = 0; i < num - 1; ++i) {
			min = sentences[i];
			minIndex = i;
			for (int j = i + 1; j < num; ++j) {
				if (sentences[j] < min) {
					min = sentences[j];
					minIndex = j;
				}
			}
			int temp = sentences[i];
			sentences[i] = sentences[minIndex];
			sentences[minIndex] = temp;
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
