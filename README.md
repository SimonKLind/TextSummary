# TextSummary
We are going to write a program to automatically summarize texts. The program will look through the text and count the occurences of words (i.e how many times a word appears in the text). It will then divide the text into sentences and score the sentences based on how many "important" words occur in each sentence; a word is deemed important if it is used alot in the text. Based on that score the program will then output the X best sentences in a new file as a summary for the text.

I have kept the main function intact, so the general structure of the program can be somewhat seen.

# StringFuncs.h
This is a small library of usefull string functions that can be used with char-array type strings (char*)

  - toLower(c) will return the lowercase equivalent of c if c is an uppercase letter, otherwise it returns c
  - isAlpha(c) Is true if c is an upper- or lowercase letter
  - isPunct(c) Is true if c is either of the following: . ! ?
    - To clarify: the above functions take a character as argument
  
  - sentenceEnd(c, i) Is true if c[i] is the end of a sentence (i.e if c[i] is a . and c[i+1] is not a letter)
    - To clarify: it takes a string (char* or char[]) and an index as arguments
    
  - string_hash(str)
    - This returns the hash-value of a string. It assumes that str is a pointer to the start of a word, 
    - and it will stop once it has reached the end of the word.
    - It will return the same value regardless if the word is upper- or lowercase
    - (I.e string_hash("hello") will be the same as string_hash("HeLLO"))
    
  - string_equals(a, b)
    - Assumes a and b are pointers to the start of words. Will only compare the words at a and b, i.e it will stop once a or b
    - reaches the end of the word.
    - It returns true if two words are equal regardless of case
    - (I.e string_equals("hello", "HeLLO") will return true)

# Task 1 - SentenceArray.h

  - The constructor (SentenceArray()) - EASY
    - Set size to 0
    - Set cap to 16
    - Make sentences a new array of 16 sentences
    
  - add(sentence) - EASY
    - Make sentences[size] = sentence
    - Add 1 to size
    - if size == cap -> expand
    
  - length() - EASY
    - return size
    
  - operator[](index) - EASY
    - return sentences[index]
    
  - The destructor (~SentenceArray()) - EASY
    - delete sentences
    
  - expand() - MEDIUM
    - Make copy of sentences
    - Multiply cap by 2
    - Make sentences a new array of cap sentences
    - Copy old sentences into new sentences
    - delete old sentences
    
  - sort(num) - MEDIUM
    - Find the sentence with highest score
    - Swap it to the front of array
    - Find the sentence with second highest score
    - Swap it to the second place in the array
    - etc... until num sentences have been swapped to the front
    
    
# Task 2 - WordMap.h

  - The constructor (WordMap()) - EASY
    - Set size to 0
    - Set num_buckets to 16
    - Make buckets new array of 16 Node*
    - Make each bucket = 0
    
  - add(word) - HARD
    - Get bucket index = string_hash(word)%num_buckets
    - Make temp Node = buckets[index]
    - while temp
      - if temp->word == word (Hint: string_equals())
        - Add 1 to temp->count
        - return
      - temp = temp_next
    - Make temp = buckets[index]
    - Make buckets[index] = new Node
    - Make buckets[index]->word = word
    - Make buckets[index]->count = 1
    - Make buckets[index]->next = temp
    - if size >= 0.75 * num_buckets -> expand
    
  - operator[](word) - MEDIUM
    - Get bucket index = string_hash(word)%num_buckets
    - Make temp Nodw = buckets[index]
    - while temp
      - if temp->word == word (Hint: string_equals())
        - return temp->count
      - temp = temp->next
    - return 0
    
  - The destructor (~WordMap()) - MEDIUM
    - Make Nodes temp and next
    - for each bucket
      - Make temp = bucket
      - while temp
        - Make next = temp->next
        - delete temp
        - make temp = next
    - delete buckets
    
  - expand() - VERY HARD
    - Feel free to try and figure it out on your own, it could be a fun challenge.
    - You might be able to do it by looking at old HashMap code.
    - Otherwise we'll just fill this in together later...
    
  - print() - MEDIUM (OPTIONAL)
    - This one is not technically needed, but it can be nice for debugging.
    - I'm going to let you figure it out on your own, it's not THAT hard...
    
    
# Task 3 - summary.cc

  - printSentence(out, sentence)
    - This one is already filled out, just because we haven't done much with ostream.
    - It will print a sentence and slap on a . and skip to a new line.
    - Example usage: printSentence(cout, sentence) will print to console using cout
    
  - getRaw(filename)
    - This opens the specified file and gives you the raw contents in a character string.
    - You shouldn't need to bother with this one...
    
  - save_summary(sentences, num_sentences, filename)
    - This uses the sort function in SentenceArray to get the num_sentences best sentences and saves them to the specified file.
    - You shouldn't need to worry about this one either...
    
  - count_words(str, words) - MEDIUM
    - Skip until first word in str
    - while not end of str
      - Add word to words-map (Hint: the StringFuncs are made to stop at the end of a word, so no word processing is needed)
      - Iterate through str until next word
      
  - get_sentences(str, words, sentences) - HARD
    - I will leave little description for this and let it be a harder challenge.
    - The gist of it is to make a sentence, and add the count of each word in the sentence to the score,
    - and finally add the sentence to sentences.
    - (Hint: sentenceEnd and isALpha are your friends)
    
  
