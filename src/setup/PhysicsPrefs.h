//
// Created by Qichen on 9/24/16.
//

#ifndef BOUNCINGBALLS_PHYSICSPREFS_H
#define BOUNCINGBALLS_PHYSICSPREFS_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>

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
    GLfloat *listOfEulerAngle[3];
    GLfloat *listOfPositions[3];
    GLfloat *listOfVelocity[3];
    GLfloat *listOfAngularVelo[3];

    void setNumberOfObjects(int i);

    void addOneInitPosition(GLfloat *onePositions, int i);

    void addOneInitOrientation(GLfloat *oneOrientation, int i);

    void addOneVelocity(GLfloat *oneVelocity, int i);

    void addOneAngularVelo(GLfloat *oneAngularVelo, int i);
};


#endif //BOUNCINGBALLS_PHYSICSPREFS_H
