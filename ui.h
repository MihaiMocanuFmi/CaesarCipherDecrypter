#ifndef UI_H
#define UI_H

void printMenu(const char *menuFilePath);
void printLine(const char *message);

void askForFloat(const char *message, float *pResult);
void askForInt(const char *message, int *pResult);
void askForStr(const char *message, char *pResult);


void refreshMenu();

#endif //UI_H
