//
// Created by Qichen on 9/24/16.
//

#ifndef GLUTPROJECT_PREFERENCEMANAGER_H
#define GLUTPROJECT_PREFERENCEMANAGER_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>
#include <matrix/CoefficientMatrices.h>

#else
#include <GL/glut.h>
#endif
using namespace std;
class Preferences {
    /****
    * mode:
    * // orientationMode    -1: not chosen, 0 : euler angle, 1 : quaternion
    * // interpolationMode  -1: not chosen, 0 : Catmull-Rom, 1 : B-spline
    */
private:
    GLfloat timeProgress;

    bool areKeyFramesLoaded, isPlaying;
    int interpolationMode, orientationMode, keyFrameAmount;
    GLfloat **listOfPositions, **listOfEulerAngle, listOfQuaternion[4][4];

public:
    Preferences();
    CoefficientMatrices * pCoefficientMatrices;
    CoefficientMatrices *currentCoefficientMatrices;

    bool getAreKeyFramesLoaded();

    int getOrientationMode();

    int getInterpolationMode();

    void setKeyFramesLoaded(bool value);

    void setInterpolationMode(int mode);

    void setOrientationMode(int mode);

    void resetPreferences();

    void setKeyFrameAmount(int i);

    int getKeyFrameAmount() const;

    void addOnePosition(int index, GLfloat x, GLfloat y, GLfloat z);

    void addOneEulerAngle(int index, GLfloat pitch, GLfloat yaw, GLfloat roll);

    void printLoadedPreferences();

    void setIsPlaying(bool i);

    bool getIsPlaying();

    void calculateCoefficientMatrices();

    GLfloat getTimeProgress();

    void timeProceed(GLfloat d);

    void resetTimeProgress();
};


#endif //GLUTPROJECT_PREFERENCEMANAGER_H
