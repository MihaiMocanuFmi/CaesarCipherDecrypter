#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "decrypter.h"

float computeChiSquared(const float actualFrequencies[NO_LETTERS], const float expectedFrequencies[NO_LETTERS])
{
    float ChiSq = 0;

    for (int i = 0; i < NO_LETTERS; ++i)
    {
        const float Ci = actualFrequencies[i];
        const float Ei = expectedFrequencies[i];
        ChiSq += (Ci - Ei) * (Ci - Ei) / Ei;
    }

    return ChiSq;
}

void readLetterDistribution(const char *filePath, float letterDistribution[NO_LETTERS])
{
    FILE *pFile = fopen(filePath, "r");
    if (pFile == NULL)
    {
        //Clion build the executable in another folder
        char newPath[128] = "../";
        strcat(newPath, filePath);
        pFile = fopen(newPath, "r");

        if(pFile == NULL)
            printf("Error opening file");
    }


    char line[16];
    fgets(line, 16, pFile);

    for (int i = 0; i < NO_LETTERS; ++i)
    {
        float distribution = atof(line);
        letterDistribution[i] = distribution;
        fgets(line, 16, pFile);
    }
}

void computeLetterDistribution(const char text[], float currentLetterDistribution[NO_LETTERS])
{
    int frequencyLetters[NO_LETTERS] = {};
    int totalNumberLetters = 0;

    while (*text != '\0')
    {
        if (isalpha(*text))
        {
            char letter = tolower(*text);

            totalNumberLetters++;
            frequencyLetters[letter - 'a']++;
        }

        text++;
    }

    for (int i = 0; i < NO_LETTERS; ++i)
        currentLetterDistribution[i] = ((float)frequencyLetters[i] / totalNumberLetters) * 100;
}

void nextCircularPermutation(float currentPermutation[NO_LETTERS])
{
    float lastElement = currentPermutation[NO_LETTERS - 1];
    for (int i = NO_LETTERS - 1; i >= 1; --i)
        currentPermutation[i] = currentPermutation[i - 1];

    currentPermutation[0] = lastElement;
}


int compareFct(const void* a, const void* b)
{
    Key arg1 = *(const Key *)a;
    Key arg2 = *(const Key *)b;

    if (arg1.distance < arg2.distance) return -1;
    if (arg1.distance > arg2.distance) return 1;
    return 0;

}
void findBestDecryptionKeys(const char text[], Key decryptionKeys[NO_LETTERS])
{
    float expectedLetterDistribution[NO_LETTERS];
    readLetterDistribution("distribution.txt", expectedLetterDistribution);

    float currentLetterDistribution[NO_LETTERS];
    computeLetterDistribution(text, currentLetterDistribution);


    for (int i = 0; i < NO_LETTERS; ++i)
    {

        float currentDistance = computeChiSquared(currentLetterDistribution, expectedLetterDistribution);
        decryptionKeys[i].distance = currentDistance;
        decryptionKeys[i].key = i;


        nextCircularPermutation(currentLetterDistribution);
    }

    qsort(decryptionKeys, NO_LETTERS, sizeof(Key), compareFct);

}


void encrypt(char s[], int n)
{
    n = n % NO_LETTERS;
    //a negative number's equivalence class in MOD NO_LETTERS
    if (n < 0)
        n = NO_LETTERS + n;

    for(int i = 0; s[i] != '\0'; i++)
    {
        if (isupper(s[i]))
        {
            int originOffset = (s[i] - 'A' + n) % NO_LETTERS;
            s[i] = 'A' + (char)originOffset;
        }
        else if( islower(s[i]))
        {
            int originOffset = (s[i] - 'a' + n) % NO_LETTERS;
            s[i] = 'a' + (char)originOffset;
        }
    }

}
