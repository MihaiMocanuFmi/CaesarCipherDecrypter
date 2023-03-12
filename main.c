#include "stdio.h"

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


    char line[16];
    fgets(line, 16, pFile);

    while (line != EOF)
    {
        //TODO: Extract letter frequency

        fgets(line, 16, pFile);
    }
}

void computeLetterDistribution(const char text[], float currentLetterDistribution[NO_LETTERS]);

void nextCircularPermutation(float currentPermutation[NO_LETTERS]);


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

int main()
{
    const char englishLetters[NO_LETTERS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                              'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const float englishFrequencies[NO_LETTERS] = {8.2f, 1.5f, 2.8f, 4.3f, 12.7f, 2.0f, 6.2f, 7.0f, 0.2f, 0.8f, 4.0f,
                                                 2.4f, 6.7f, 7.5f, 1.9f, 0.1f, 6.0f, 2.8f, 9.1f, 2.8f, 1.0f, 2.4f,
                                                 0.2f, 2.0f, 0.1f};
    return 0;
}