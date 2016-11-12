//
// Created by Qichen on 9/26/16.
//

#include <iostream>
#include <cmath>
#include "InterpolationHelper.h"
#include "QuaternionConverter.h"

/***
 * These two matrices are the G matrices for catmull-rom and b-spline
 */
static const GLfloat basisCatmullMatrix[4][4] = {
        {(const GLfloat) -0.5, 1.5, (const GLfloat) -1.5, 0.5},
        {1,                    (const GLfloat) -2.5, 2,  (const GLfloat) -0.5},
        {(const GLfloat) -0.5, 0,                    0.5,   0},
        {0, 1, 0, 0}
};
static const GLfloat basisBsplineMatrix[4][4] = {
        {(const GLfloat) (-1/6.0), 0.5, (const GLfloat) -0.5, (const GLfloat) (1/6.0)},
        {0.5,                    -1, 0.5,  0},
        {(const GLfloat) -0.5, 0,                    0.5,   0},
        {(const GLfloat) (1/6.0), (const GLfloat) (4/6.0), (const GLfloat) (1/6.0), 0}
};
/****
 * Get the coefficentMatrix for translation or euler angle interpolation
 * @param dest is where the coefficient matrix will be stored
 * @param interpolationMode suggest either catmull-rom or b-spline
 * @param controlPoints are either x-y-z coordinates or pitch, yaw, roll
 */
void InterpolationHelper::calculate3dCoefficientMatrix(GLfloat (*dest)[3], int interpolationMode,
                                                       float **controlPoints, int offset) {
    int i,j,k;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++){
        for (j = 0; j < POSITION_OR_EULER_DIMENSION; j++){
            dest[i][j] = 0;
            for (k = 0;  k< NUMBER_OF_CONTROL_POINTS; k++){
                if (interpolationMode == 0) {
                    //use catmull-rom for interpolation
                    dest[i][j] += basisCatmullMatrix[i][k] * controlPoints[k + offset][j];
                } else {
                    // use b-spline
                    dest[i][j] += basisBsplineMatrix[i][k] * controlPoints[k + offset][j];
                }
            }
        }
    }

    //TODO for debug only
    cout<< "the coefficient matrix is:"<< endl;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++) {
        for (j = 0; j< POSITION_OR_EULER_DIMENSION; j++) {

            cout<< dest[i][j] << '\t';
        }
        cout<< '\n';
    }

}


/****
 *  Calculate the coefficient matrix for quaternions interpolation
 * @param dest where the coeeficient matrix is stored
 * @param interpolationMode suggest either catmull-rom or b-spline
 * @param quaternionList
 */
void InterpolationHelper::calculate4dCoefficientMatrix(
        GLfloat (*dest)[4], int interpolationMode, GLfloat quaternionList[4][4]) {
    int i,j,k;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++){
        for (j = 0; j < QUATERNION_DIMENSION; j++){
            dest[i][j] = 0;
            for (k = 0;  k< NUMBER_OF_CONTROL_POINTS; k++){
                if (interpolationMode == 0) {
                    //use catmull-rom for interpolation
                    dest[i][j] += basisCatmullMatrix[i][k] * quaternionList[k][j];
                } else {
                    // use b-spline
                    dest[i][j] += basisBsplineMatrix[i][k] * quaternionList[k][j];
                }
            }
        }
    }

    //TODO for debug only
    cout<< "the quaternion coefficient matrix is:"<< endl;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++) {
        for (j = 0; j< QUATERNION_DIMENSION; j++) {

            cout<< dest[i][j] << '\t';
        }
        cout<< '\n';
    }
}

/****
 * This function prepares the time vector
 * @param tVector the address of the vector to store the time vector elements
 * @param t the current time ranging from 0 to 1
 */
void InterpolationHelper::prepareTimeVector(GLfloat *tVector, GLfloat t) {
    *tVector = (GLfloat) pow(t, 3);
    *(tVector + 1) = (GLfloat) pow(t,2);
    *(tVector + 2) = t;
    *(tVector + 3) = 1;
}

/****
 * calculate the translation OR euler angle vector for current time given the coefficient matrix
 * @param transOrEuler the address of the vector to store translation vector
 * @param tVector the time vector
 * @param coefficientMatrix the coefficient matrix [4][3]
 */
void InterpolationHelper::prepareTranslationOrEulerAngleVector(GLfloat *transOrEuler, GLfloat *tVector,
                                                               GLfloat coefficientMatrix[4][3]) {
    int i,j;
    for(i = 0; i < POSITION_OR_EULER_DIMENSION; i++) {
        *(transOrEuler + i) = 0;
        for (j = 0; j < NUMBER_OF_CONTROL_POINTS; j++) {
            *(transOrEuler + i) += *(tVector + j) * (*(coefficientMatrix + j))[i];
        }
    }
}


/****
 * calculate the quaternion for current time given the coefficient matrix
 * @param quaternion
 * @param tVector
 * @param coefficientMatrix [4][4]
 */
void
InterpolationHelper::prepareQuaternionVector(GLfloat *quaternion, GLfloat *tVector, GLfloat (*coefficientMatrix)[4]) {
    int i,j;
    for(i = 0; i < QUATERNION_DIMENSION; i++) {
        *(quaternion + i) = 0;
        for (j = 0; j < NUMBER_OF_CONTROL_POINTS; j++) {
            *(quaternion + i) += *(tVector + j) * (*(coefficientMatrix + j))[i];
        }
    }
    //For debug only
    //cout<< "the magnitude before is " <<QuaternionConverter::getMagnitudeOfQuaternion(quaternion)<< endl;

    // normalize the quaternion before using it to generate transformation matrix
    GLfloat magnitude = QuaternionConverter::getMagnitudeOfQuaternion(quaternion);
    for(i = 0; i < QUATERNION_DIMENSION; i++){
        *(quaternion + i) /= magnitude;
    }
    //For debug only
    //cout<< "the magnitude after is " <<QuaternionConverter::getMagnitudeOfQuaternion(quaternion)<< endl;
}


/****
 *  Calculate the coefficient matrix for cubic spline interpolation of 10 dimentions
 *  for articulated figures (2 upper-arms, 2 forarms, 2 thighs, 2 calfs each of them has 1 dof)
 * @param dest where the coeeficient matrix is stored
 * @param interpolationMode suggest either catmull-rom or b-spline
 * @param quaternionList
 */
void InterpolationHelper::calculate10dCoefficientMatrix(
        GLfloat (*dest)[10], int interpolationMode, GLfloat (*controlPointList)[10]) {
    int i,j,k;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++){
        for (j = 0; j < 10; j++){
            dest[i][j] = 0;
            for (k = 0;  k< NUMBER_OF_CONTROL_POINTS; k++){
                if (interpolationMode == 0) {
                    //use catmull-rom for interpolation
                    dest[i][j] += basisCatmullMatrix[i][k] * controlPointList[k][j];
                } else {
                    // use b-spline
                    dest[i][j] += basisBsplineMatrix[i][k] * controlPointList[k][j];
                }
            }
        }
    }

    //TODO for debug only
    cout<< "the coefficient matrix is:"<< endl;
    for (i = 0; i < NUMBER_OF_CONTROL_POINTS; i++) {
        for (j = 0; j< 10; j++) {

            cout<< dest[i][j] << '\t';
        }
        cout<< '\n';
    }
}


/****
 * calculate the 8-d vector for current time given the coefficient matrix for cubic spline of the articulated figure
 * @param dest the address of the vector to store translation vector
 * @param tVector the time vector
 * @param coefficientMatrix the coefficient matrix [4][10]
 */
void InterpolationHelper::prepare10dVector(GLfloat *dest, GLfloat *tVector,
                                           GLfloat coefficientMatrix[4][10]) {
    int i,j;
    for(i = 0; i < 10; i++) {
        *(dest + i) = 0;
        for (j = 0; j < NUMBER_OF_CONTROL_POINTS; j++) {
            *(dest + i) += *(tVector + j) * (*(coefficientMatrix + j))[i];
        }
    }
}
