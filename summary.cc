#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "WordMap.h"
#include "StringFuncs.h"
#include "SentenceArray.h"

using namespace std;

void printSentence(ostream &out, Sentence &sentence) {
    for(unsigned int i=0; !sentenceEnd(sentence.raw, i); ++i) {
        out.put(sentence.raw[i]);
    }
    out.write(".\n", 2);
}

void count_words(const char *str, WordMap &words) {
} 

const char* getRaw(const char *filename) {
    ifstream fin(filename);
    if(!fin) return 0;
    fin.seekg(0, fin.end);
    unsigned int length = fin.tellg();
    fin.seekg(0, fin.beg);
    char *str = new char[length+1];
    fin.read(str, length);
    str[length] = 0;
    fin.close();
    return str;
}

void get_sentences(const char *str, WordMap &words, SentenceArray &sentences) {
}

void save_summary(SentenceArray &sentences, unsigned int num_sentences, const char *filename) {
    sentences.sort(num_sentences);
    ofstream fout(filename);
    if(!fout) return;
    for(unsigned int i=0; i<num_sentences && i<sentences.length(); ++i) {
        printSentence(fout, sentences[i]);
    }
    fout.close();
}

int main() {

    // Get the raw string from file
    const char *str = getRaw("example.txt");
    
    // Make a WordMap
    WordMap words;

    // Use function count_words to fill our WordMap
    count_words(str, words);

    // Create a SentenceArray
    SentenceArray sentences;

    // Use get_sentences to fill our SentenceArray
    get_sentences(str, words, sentences);

    // Save a number of sentences to a file (in this case 5 sentences)
    save_summary(sentences, 5, "example_out.txt");

    // Don't forget to delete the string...
    delete[] str;
}
