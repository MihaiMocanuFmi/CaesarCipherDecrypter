#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "decrypter.h"
#include "ui.h"

void startApp()
{
    printMenu();
    bool isRunning = true;

    while (isRunning)
    {
        char text[512];
        askForStr("Insert the text you want to decrypt:", text, 512);

        Key bestKeys[NO_LETTERS];
        findBestDecryptionKeys(text, bestKeys);

        bool tryNext = true;
        for (int i = 0; tryNext; i++)
        {
            char newText[512];
            strcpy(newText, text);
            encrypt(newText, bestKeys[i].key);

            printLine(newText);
            printf("\t\tKey %d has a likelihood value of: %f\n", bestKeys[i].key, bestKeys[i].distance);

            if (i < NO_LETTERS)
                askForYesNo("Do you want to see the next possible decryption?", false, &tryNext);
            else
            {
                printLine("Went through all possible decryptions");
                tryNext = false;
            }
        }

        askForYesNo("Do you want to decrypt another text?", false, &isRunning);
    }

    printLine("Exiting app...");
}

int main()
{
    startApp();

    return 0;
}