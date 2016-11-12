//
// Created by Qichen on 9/24/16.
//

#include <iostream>
#include "Preferences.h"
#include "InterpolationHelper.h"
#include "QuaternionConverter.h"


/****
 * This class contains the setup for the animation.
 * The fields except the list of quaternions are interpreted from the user input script.
 * It also contains the coefficient matrices for the current time instance.
 */
Preferences::Preferences() {
    resetPreferences();
}

// setters
void Preferences::setKeyFramesLoaded(bool value) {
    areKeyFramesLoaded = value;
}

void Preferences::setInterpolationMode(int mode) {
    interpolationMode = mode;
}

void Preferences::setOrientationMode(int mode) {
    orientationMode = mode;
}

// getters
bool Preferences::getAreKeyFramesLoaded() {
    return areKeyFramesLoaded;
}

int Preferences::getOrientationMode() {
    return orientationMode;
}

int Preferences::getInterpolationMode() {
    return interpolationMode;
}

void Preferences::resetPreferences() {
    areKeyFramesLoaded = false;
    isPlaying = false;
    interpolationMode = -1;
    orientationMode = -1;
    keyFrameAmount = 0;
    timeProgress = 0;
}


void Preferences::setKeyFrameAmount(int i) {
    keyFrameAmount = i;
    listOfPositions = new GLfloat*[i];
    listOfEulerAngle = new GLfloat*[i];
    //listOfQuaternion = new GLfloat*[i];

    pCoefficientMatrices = new CoefficientMatrices(orientationMode == 0, 0, keyFrameAmount - 3);
}

int Preferences::getKeyFrameAmount() const {
    return keyFrameAmount;
}

void Preferences::addOnePosition(int index, GLfloat x, GLfloat y, GLfloat z) {
    listOfPositions[index] = new GLfloat[3];
    listOfPositions[index][0] = x;
    listOfPositions[index][1] = y;
    listOfPositions[index][2] = z;
}

void Preferences::addOneEulerAngle(int index, GLfloat pitch, GLfloat yaw, GLfloat roll) {
    listOfEulerAngle[index] = new GLfloat[3];
    listOfEulerAngle[index][0] = pitch;
    listOfEulerAngle[index][1] = yaw;
    listOfEulerAngle[index][2] = roll;
}

/****
 * print out the infomation for debug purposes
 */
void Preferences::printLoadedPreferences() {
    cout<< "number of key frames: "<< keyFrameAmount<<endl;
    cout<< "orientation / interpolation: "<< orientationMode << '/' << interpolationMode <<endl;
    int i ,j ;
    float l;
    for(i = 0; i < keyFrameAmount; i++) {
        for(j = 0; j < 3; j++) {
        l =listOfPositions[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }
    cout<< '\n';
    for(i = 0; i < keyFrameAmount; i++) {
        for(j = 0; j < 3; j++) {
            l =listOfEulerAngle[i][j];
            cout<< l << '\t';
        }
        cout<< '\n';
    }

}

void Preferences::setIsPlaying(bool i) {
    isPlaying = i;
}

bool Preferences::getIsPlaying() {
    return isPlaying;
}

/****
 *  get the coefficient matrices
 */
void Preferences::calculateCoefficientMatrices() {

    int i;
    currentCoefficientMatrices = pCoefficientMatrices;
    for (i = 0; i < keyFrameAmount - 3; i++){

        // calculate the position coefficient matrix for t
        // then store in translationCoefficientMatrix
        InterpolationHelper::calculate3dCoefficientMatrix(currentCoefficientMatrices->translation,
                                                          interpolationMode, listOfPositions, i);

        if (orientationMode == 0) {
            // calculate the euler angle coefficient matrix for t
            // then store in translationCoefficientMatrix
            InterpolationHelper::calculate3dCoefficientMatrix(currentCoefficientMatrices->eRotation,
                                                              interpolationMode, listOfEulerAngle, i);
        } else {
            //convert the user-provided euler angles to quaternions
            QuaternionConverter::eulerAngleToQuaternion(listOfQuaternion, listOfEulerAngle, i);
            //TODO then get the quaternion version of coefficient matrix
            InterpolationHelper::calculate4dCoefficientMatrix(currentCoefficientMatrices->qRotation,
                                                              interpolationMode, listOfQuaternion);
        }
        currentCoefficientMatrices = currentCoefficientMatrices->next;
    }
}

GLfloat Preferences::getTimeProgress() {
    return timeProgress;
}

void Preferences::timeProceed(GLfloat d) {
    timeProgress += d;
}

void Preferences::resetTimeProgress() {
    timeProgress = 0;

}
