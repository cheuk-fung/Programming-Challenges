#include <cstdio>
#include <string>

using namespace std;

class PikachuEasy {
    private:

    public:
        string check(string word)
        {
            for (int i = 0; i < word.length(); ) {
                switch (word[i]) {
                    case 'p':
                        if (word[i + 1] != 'i') return "NO";
                        i += 2;
                        break;
                    case 'k':
                        if (word[i + 1] != 'a') return "NO";
                        i += 2;
                        break;
                    case 'c':
                        if (word[i + 1] != 'h' || word[i + 2] != 'u') return "NO";
                        i += 3;
                        break;
                    default:
                        return "NO";
                }
            }
            return "YES";
        }
};
