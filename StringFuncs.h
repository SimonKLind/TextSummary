#ifndef STRINGFUNCS_H
#define STRINGFUNCS_H

#define toLower(c) ( (c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c) )
#define isAlpha(c) ( c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' )
#define isPunct(c) ( c == '.' || c == '!' || c == '?' )
#define sentenceEnd(c, i) ( isPunct(c[i]) && c[i+1] && !isAlpha(c[i+1]) )

unsigned int string_hash(const char *str) {
    unsigned int hash = 2166136261;
    while(isAlpha(*str)) {
        hash ^= toLower(*str);
        hash *= 16777619;
        ++str;
    }
    return hash;
}

bool string_equals(const char *a, const char *b) {
    while(isAlpha(*a) && isAlpha(*b) && toLower(*a) == toLower(*b)) {
        ++a;
        ++b;
    }
    return !(isAlpha(*a) || isAlpha(*b));
}

#endif
