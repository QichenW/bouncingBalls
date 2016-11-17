//
// Created by Qichen on 9/25/16.
//

#include <cstdio>
#include <iostream>
#include "PhysicsSetupFileLoader.h"
using namespace std;
/****
 * This is called inside UserInputManager::loadUserInputFromFileDialog()
 * @param path is provided by UserInputManager::loadUserInputFromFileDialog()
 * @param pPreferences
 */
void PhysicsSetupFileLoader::loadPreferencesFromTextFile(char *path, PhysicsPrefs *prefs) {
    FILE *setupFilePointer;
    GLfloat tempFloat[3] = {};
    GLfloat tempMass = 0;
    int numberOfWalls = 6;
    int numberOfObjects = 6;
    char firstWord[16];
    setupFilePointer = fopen(path, "r");
    if (!setupFilePointer) {
        printf("can't open file %s\n", path);
        exit(1);
    }

    while (1) {
        if (fscanf(setupFilePointer, "%s", firstWord) == EOF) {
            // read the next word, if returns EOF then break
            break;
        } else if (firstWord[0] == '#') {
            // if reach comment break
            break;
        }
        //The following chuck of code interpret user input from the file, how to write a user input script
        // is shown in the .txt files in /data
        if (strcmp(firstWord, "n") == 0) {
            fscanf(setupFilePointer, "%d", &numberOfObjects);
            prefs->setNumberOfObjects(numberOfObjects);
        }  else if (strcmp(firstWord, "p") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat[0], &tempFloat[1], &tempFloat[2]);
            // save positions in preferences
            prefs->addOneInitPosition(tempFloat);
        } else if (strcmp(firstWord, "e") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat[0], &tempFloat[1], &tempFloat[2]);
            //save euler angle in preferences
            prefs->addOneInitOrientation(tempFloat);
        } else if(strcmp(firstWord, "v") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat[0], &tempFloat[1], &tempFloat[2]);
            prefs->addOneVelocity(tempFloat);
        }else if(strcmp(firstWord, "a") == 0) {
            fscanf(setupFilePointer, "%f %f %f", &tempFloat[0], &tempFloat[1], &tempFloat[2]);
            prefs->addOneAngularVelo(tempFloat);
        } else if (strcmp(firstWord, "m") == 0){
            int count;
            for(count = 0; count < numberOfObjects - numberOfWalls; count++){
                fscanf(setupFilePointer, "%f", &tempMass);
                prefs->addOneBallMass(tempMass);
            }

        }
    }
    fclose(setupFilePointer);
}
