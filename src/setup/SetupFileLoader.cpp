//
// Created by Qichen on 9/25/16.
//

#include <cstdio>
#include <iostream>
#include "SetupFileLoader.h"
using namespace std;
/****
 * This is called inside UserInputManager::loadUserInputFromFileDialog()
 * @param path is provided by UserInputManager::loadUserInputFromFileDialog()
 * @param pPreferences
 */
void SetupFileLoader::loadPreferencesFromTextFile(char *path, Preferences *pPreferences) {
    FILE *setupFilePointer;
    float tempFloat1, tempFloat2, tempFloat3;
    char firstWord[16];
    setupFilePointer = fopen(path, "r");
    if (!setupFilePointer) {
        printf("can't open file %s\n", path);
        exit(1);
    }
    int tempInteger, indexOfNextPosition = 0, indexOfNetEulerAngle = 0;
    while (1) {
        if (fscanf(setupFilePointer, "%s", firstWord) == EOF) {
            //TODO debug use only
            (*pPreferences).printLoadedPreferences();
            // read the next word, if returns EOF then break
            break;
        } else if (firstWord[0] == '#') {
            //TODO debug use only
            (*pPreferences).printLoadedPreferences();
            // if reach comment break
            break;
        }
        //The following chuck of code interpret user input from the file, how to write a user input script
        // is shown in the .txt files in /data
        if (strcmp(firstWord, "n") == 0) {
            fscanf(setupFilePointer, "%d", &tempInteger);
            // save number of key frames in preferences
            (*pPreferences).setKeyFrameAmount(tempInteger);
        } else if (strcmp(firstWord, "o") == 0) {
            //save interpolation mode in preferences
            fscanf(setupFilePointer, "%d", &tempInteger);
            (*pPreferences).setOrientationMode(tempInteger);
        } else if (strcmp(firstWord, "i") == 0) {
            //save interpolation mode in preferences
            fscanf(setupFilePointer, "%d", &tempInteger);
            (*pPreferences).setInterpolationMode(tempInteger);
        } else if (strcmp(firstWord, "p") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat1, &tempFloat2, &tempFloat3);
            // save positions in preferences
            (*pPreferences).addOnePosition(indexOfNextPosition++, tempFloat1, tempFloat2, tempFloat3);
        } else if (strcmp(firstWord, "e") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat1, &tempFloat2, &tempFloat3);
            //save euler angle in preferences
            (*pPreferences).addOneEulerAngle(indexOfNetEulerAngle++, tempFloat1, tempFloat2, tempFloat3);
        }
    }
    fclose(setupFilePointer);
}
