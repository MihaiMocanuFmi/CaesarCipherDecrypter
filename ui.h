#ifndef UI_H
#define UI_H

#include <stdbool.h>

void printMenu();
void printLine(const char *message);
void printArrayInt(const int array[], int size);

void askForFloat(const char *message, float *pResult);
void askForInt(const char *message, int *pResult);
void askForStr(const char *message, char *pResult, int length);
void askForYesNo(const char *message, bool yesIsDefault, bool *pResult);

void refreshScreen();

#endif //UI_H
