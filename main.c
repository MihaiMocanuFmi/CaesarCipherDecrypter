#include <stdio.h>
#include <string.h>

#include "decrypter.h"


#define NO_LETTERS 26


int main()
{

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