#ifndef DECRYPTER_H
#define DECRYPTER_H

#define NO_LETTERS 26

float computeChiSquared(const float actualFrequencies[NO_LETTERS], const float expectedFrequencies[NO_LETTERS]);

void readLetterDistribution(const char *filePath, float letterDistribution[NO_LETTERS]);

void computeLetterDistribution(const char text[], float currentLetterDistribution[NO_LETTERS]);

void nextCircularPermutation(float currentPermutation[NO_LETTERS]);

typedef struct
{
    float distance;
    int key;
}Key;

void findBestDecryptionKeys(const char text[], Key decryptionKeys[NO_LETTERS]);

void encrypt(char s[], int n);
#endif //DECRYPTER_H
