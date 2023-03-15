#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void printMenu()
{
    const char menu[] = "\nStarted Caesar's Cipher Decrypter.\n\n"
                        "Given an encrypted text, the program will try to decrypt it. Note that decryptions on longer tests are more accurate.\n";

    printf("%s\n", menu);
}

void printLine(const char *message)
{
    printf("%s\n", message);
}


void removeNewLineFromStr(char *str)
{
    char *pNewLine = strchr(str, '\n');
    if(pNewLine)
        *pNewLine = '\0';
}

void askForStr(const char *message, char *pResult, int length)
{
    printLine(message);
    printf(">>\t");

    fgets(pResult, length * sizeof(char), stdin);
    removeNewLineFromStr(pResult);
}

void askForYesNo(const char *message, bool yesIsDefault, bool *pResult)
{
    char newMessage[256];
    strcpy(newMessage, message);

    if (yesIsDefault)
    {
        strcat(newMessage, "\t[Y/n]");

        char option[8];
        askForStr(newMessage, option, 8);

        if (strlen(option) == 0 || (strlen(option) == 1 && tolower(option[0]) == 'y') )
            *pResult = 1;
        else
            *pResult = 0;
    }
    else
    {
        strcat(newMessage, "\t[y/N]");

        char option[8];
        askForStr(newMessage, option, 8);

        if (strlen(option) == 1 && tolower(option[0]) == 'y')
            *pResult = 1;
        else
            *pResult = 0;
    }
}