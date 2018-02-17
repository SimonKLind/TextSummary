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
    while(*str && !isAlpha(*str)) ++str;
    while(*str) {
        words.add(str);
        while(isAlpha(*str)) ++str;
        while(*str && !isAlpha(*str)) ++str;
    }
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
    Sentence sentence;
    unsigned int num_words;
    while(*str && !isAlpha(*str)) ++str;
    while(*str) {
        sentence.raw = str;
        sentence.score = 0.0f;
        num_words = 0;
        while(*str) {
            sentence.score += words[str];
            ++num_words;
            while(isAlpha(*str)) ++str;
            if(sentenceEnd(str, 0)) break;
            while(*str && !isAlpha(*str)) ++str;
        }
        sentence.score /= num_words;
        sentences.add(sentence);
        // printSentence(cout, sentence);
        while(*str && !isAlpha(*str)) ++str;
    }
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
    const char *str = getRaw("text.txt");
    // cout << str << '\n';
    WordMap words;
    count_words(str, words);
    cout << "Counted Words\n";
    SentenceArray sentences;
    get_sentences(str, words, sentences);
    cout << "Got sentences\n";
    save_summary(sentences, 5, "test_out.txt");
    cout << "Saved Summary\n";
    delete[] str;
}
