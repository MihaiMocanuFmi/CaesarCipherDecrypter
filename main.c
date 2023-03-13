#include <stdio.h>
#include <string.h>

#include "decrypter.h"


#define NO_LETTERS 26


int main()
{
    const char englishLetters[NO_LETTERS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                              'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const float englishFrequencies[NO_LETTERS] = {8.2f, 1.5f, 2.8f, 4.3f, 12.7f, 2.0f, 6.2f, 7.0f, 0.2f, 0.8f, 4.0f,
                                                 2.4f, 6.7f, 7.5f, 1.9f, 0.1f, 6.0f, 2.8f, 9.1f, 2.8f, 1.0f, 2.4f,
                                                 0.2f, 2.0f, 0.1f};

    char text[256] = "D rvn, D nvr, D y";
    Key bestKeys[NO_LETTERS];
    findBestDecryptionKeys(text, bestKeys);

    for (int i = 0; i < 3; ++i)
    {
        char newText[256];
        strcpy(newText, text);
        encrypt(newText, bestKeys[i].key);

        printf("%s\n\tKey Likelihood value:\t%f\n\n", newText, bestKeys[i].distance);
    }

    return 0;
}