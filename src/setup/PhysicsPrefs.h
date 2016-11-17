//
// Created by Qichen on 9/24/16.
//

#ifndef BOUNCINGBALLS_PHYSICSPREFS_H
#define BOUNCINGBALLS_PHYSICSPREFS_H
#include <iostream>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>
#include <vector>
#else
#include <GL/glut.h>
#endif
using namespace std;
class PhysicsPrefs {
private:
    bool areInputLoaded, isPlaying;

public:
    PhysicsPrefs();

    bool getAreInputLoaded();

    void setInputLoaded(bool value);

    void resetPreferences();

    void printLoadedPreferences();

    void setIsPlaying(bool i);

    bool getIsPlaying();

    int numberOfObjects;
    vector<GLfloat*> listOfEulerAngle;
    vector<GLfloat*> listOfPositions;
    vector<GLfloat*> listOfVelocity;
    vector<GLfloat*> listOfAngularVelo;

    void setNumberOfObjects(int i);

    void addOneInitPosition(GLfloat *onePositions);

    void addOneInitOrientation(GLfloat *oneOrientation);

    void addOneVelocity(GLfloat *oneVelocity);

    void addOneAngularVelo(GLfloat *oneAngularVelo);
};


#endif //BOUNCINGBALLS_PHYSICSPREFS_H
