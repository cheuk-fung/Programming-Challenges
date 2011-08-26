/*
 *  SRC: POJ 3573
 * PROB: I18n
 * ALGO: String
 * DATE: Aug 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>

using std::string;

string abbr[26 * 26][40];

char* split(char* s, char* word)
{
    char* t = s;
    while (isalnum(*t)) t++;

    while (s != t) *word++ = *s++;
    *word = '\0';

    return s;
}

inline int next_int(char* s)
{
    int res = 0;
    while (isdigit(*s)) res = res * 10 + *s++ - '0';
    return res;
}

void deal(char* word)
{
    int len = strlen(word);
    if (len <= 2) {
        printf("%s", word);
        return ;
    }

    char a = word[0], b = word[len - 1];
    int idx = (tolower(a) - 'a') * 26 + (tolower(b) - 'a');

    for (char* t = word; *t; t++) {
        if (isdigit(*t)) {
            int num = next_int(word + 1);
            string new_word = abbr[idx][num];
            if (new_word == "" || new_word == "-1")
            {
                printf("%s", word);
                return ;
            }

            if ('a' <= a && a <= 'z') printf("%s", new_word.c_str());
            else {
                if ('a' <= b && b <= 'z') {
                    new_word[0] = toupper(new_word[0]);
                    printf("%s", new_word.c_str());
                }
                else {
                    for (int i = 0; i < new_word.length(); i++)
                        putchar(toupper(new_word[i]));
                }
            }
        
            return ;
        }
    }

    string new_word;
    for (char* t = word; *t; t++) new_word += tolower(*t);

    len -= 2;
    if (abbr[idx][len] == "") abbr[idx][len] = new_word;
    else if (new_word != abbr[idx][len]) abbr[idx][len] = "-1";

    printf("%s", word);
}

int main()
{
    char words[100], word[50];
    while (gets(words)) {
        char* s = words;
        while (*s) {
            s = split(s, word);
            if (*word) deal(word);
            if (*s) putchar(*s++);
        }
        putchar(10);
    }

    return 0;
}
