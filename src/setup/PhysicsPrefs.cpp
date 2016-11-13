//
// Created by Qichen on 9/24/16.
//

#include <iostream>
#include "PhysicsPrefs.h"
#include "InterpolationHelper.h"
#include "QuaternionConverter.h"


/****
 * This class contains the setup for the animation.
 * The fields except the list of quaternions are interpreted from the user input script.
 * It also contains the coefficient matrices for the current time instance.
 */
PhysicsPrefs::PhysicsPrefs() {
    resetPreferences();
}

// setters
void PhysicsPrefs::setInputLoaded(bool value) {
    areInputLoaded = value;
}

// getters
bool PhysicsPrefs::getAreInputLoaded() {
    return areInputLoaded;
}


void PhysicsPrefs::resetPreferences() {
    areInputLoaded = false;
    isPlaying = false;
    numberOfObjects = 0;
}

/****
 * print out the infomation for debug purposes
 */
void PhysicsPrefs::printLoadedPreferences() {
    cout<< "number of objects: "<< numberOfObjects<<endl;
    int i ,j ;
    float l;
    for(i = 0; i < numberOfObjects; i++) {
        for(j = 0; j < 3; j++) {
        l =listOfPositions[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }
    cout<< '\n';
    for(i = 0; i < numberOfObjects; i++) {
        for(j = 0; j < 3; j++) {
            l =listOfEulerAngle[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }
}

void PhysicsPrefs::setIsPlaying(bool i) {
    isPlaying = i;
}

bool PhysicsPrefs::getIsPlaying() {
    return isPlaying;
}

void PhysicsPrefs::setNumberOfObjects(int i) {
    numberOfObjects = i;

}

void PhysicsPrefs::addOneInitPosition(GLfloat *onePositions, int i) {
    int j;
    listOfPositions[i] = new GLfloat[3];
    for (j = 0; j < 3; j++){
        listOfPositions[i][j] = *(onePositions + j);
    }
}

void PhysicsPrefs::addOneInitOrientation(GLfloat *oneOrientation, int i) {
    int j;
    listOfEulerAngle[i] = new GLfloat[3];
    for (j = 0; j < 3; j++){
        listOfEulerAngle[i][j] = *(oneOrientation + j);
    }
}

void PhysicsPrefs::addOneVelocity(GLfloat *oneVelocity, int i) {
    int j;
    listOfVelocity[i] = new GLfloat[3];
    for (j = 0; j < 3; j++){
        listOfVelocity[i][j] = *(oneVelocity + j);
    }
}

void PhysicsPrefs::addOneAngularVelo(GLfloat *oneAngularVelo, int i) {
    int j;
    listOfAngularVelo[i] = new GLfloat[3];
    for (j = 0; j < 3; j++){
        listOfAngularVelo[i][j] = *(oneAngularVelo + j);
    }
}
