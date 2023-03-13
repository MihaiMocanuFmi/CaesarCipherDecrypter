#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NO_LETTERS 26

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
        currentLetterDistribution[i] = (float)frequencyLetters[i] / totalNumberLetters;
}

void nextCircularPermutation(float currentPermutation[NO_LETTERS])
{
    float lastElement = currentPermutation[NO_LETTERS - 1];
    for (int i = NO_LETTERS - 1; i >= 1; --i)
        currentPermutation[i] = currentPermutation[i - 1];

    currentPermutation[0] = lastElement;
}


int findBestEncryptionKey(const char text[])
{
    float expectedLetterDistribution[NO_LETTERS];
    readLetterDistribution("distribution.txt", expectedLetterDistribution);

    float currentLetterDistribution[NO_LETTERS];
    computeLetterDistribution(text, currentLetterDistribution);

    float minDistance = computeChiSquared(currentLetterDistribution, expectedLetterDistribution);
    int minKey = 0;

    for (int i = 1; i < NO_LETTERS; ++i)
    {
        nextCircularPermutation(currentLetterDistribution);
        float currentDistance = computeChiSquared(currentLetterDistribution, expectedLetterDistribution);

        if (currentDistance < minDistance)
        {
            minDistance = currentDistance;
            minKey = i;
        }
    }


    return minKey;
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

int main()
{
    const char englishLetters[NO_LETTERS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                              'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const float englishFrequencies[NO_LETTERS] = {8.2f, 1.5f, 2.8f, 4.3f, 12.7f, 2.0f, 6.2f, 7.0f, 0.2f, 0.8f, 4.0f,
                                                 2.4f, 6.7f, 7.5f, 1.9f, 0.1f, 6.0f, 2.8f, 9.1f, 2.8f, 1.0f, 2.4f,
                                                 0.2f, 2.0f, 0.1f};

    char text[256] = "Xvznvm Xdkczm! dn vi diozmznodib xjyz dyzv wpo do vxopvggt npxfn hvi";
    int encryptionKey = findBestEncryptionKey(text);

    encrypt(text, encryptionKey);

    printf("%s", text);
    return 0;
}