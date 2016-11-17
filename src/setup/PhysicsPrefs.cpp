//
// Created by Qichen on 9/24/16.
//

#include "PhysicsPrefs.h"

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

void PhysicsPrefs::addOneInitPosition(GLfloat *onePositions) {
    int j;
    GLfloat *pv = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    for (j = 0; j < 3; j++){
        pv[j] = *(onePositions + j);
    }
    listOfPositions.push_back(pv);
}

void PhysicsPrefs::addOneInitOrientation(GLfloat *oneOrientation) {
    int j;
    GLfloat *ov = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    for (j = 0; j < 3; j++){
        ov[j] = *(oneOrientation + j);
    }
    listOfEulerAngle.push_back(ov);
}

void PhysicsPrefs::addOneVelocity(GLfloat *oneVelocity) {
    int j;
    GLfloat *vv = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    for (j = 0; j < 3; j++){
        vv[j] = *(oneVelocity + j);
    }
    listOfVelocity.push_back(vv);
}

void PhysicsPrefs::addOneAngularVelo(GLfloat *oneAngularVelo) {
    int j;
    GLfloat *av = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    for (j = 0; j < 3; j++){
        av[j] = *(oneAngularVelo + j);
    }
    listOfAngularVelo.push_back(av);
}

void PhysicsPrefs::addOneBallMass(GLfloat m) {
    listOfMass.push_back(m);
}
