//
// Created by Qichen on 9/27/16.
//

#include <math.h>
#include <iostream>
#include "QuaternionConverter.h"
//TODO Test this
/****
 *  The helper function to get quaternion from euler angle
 * @param dest point to the 2d array to store the list of quaternion
 * @param listOfEulerAngle the euler angle user input
 * @param amount how may frames are there
 */
void QuaternionConverter::eulerAngleToQuaternion(GLfloat dest[4][4], GLfloat **listOfEulerAngle, int offset) {
    GLfloat qx[4][4]={};
    GLfloat qy[4][4]={};
    GLfloat qz[4][4]={};
    GLfloat pitch[4], yaw[4], roll[4];
    int i;
    for (i = 0; i < 4; i++){
        pitch[i] = (float) M_PI / 180 * (listOfEulerAngle[i + offset][0]);
        yaw[i] = (float) M_PI / 180 * (listOfEulerAngle[i + offset][1]);
        roll[i] = (float) M_PI / 180 * (listOfEulerAngle[i + offset][2]);
        // get the quaternions for x,y,z axis, then combine them
        qx[i][0] = cosf(pitch[i] / 2);
        qy[i][0] = cosf(yaw[i] / 2);
        qz[i][0] = cosf(roll[i] / 2);
        qx[i][1] = sinf(pitch[i] / 2);
        qy[i][2] = sinf(yaw[i] / 2);
        qz[i][3] = sinf(roll[i] / 2);

    }
    // multiplications to get combined quaternion
    getQuaternionList(dest,qz, qy, qx);
}
/***
 * Hard coded multiplication, get the array of combined quaternions from
 * three arrays of quaternions representing the rotation about x,y,z axes respectively.
 *  dest = leftQuaternion * rightQuaternion
 * @param dest
 * @param middleQuaternion
 * @param rightQuaternion
 */
void QuaternionConverter::getQuaternionList(GLfloat dest[4][4], GLfloat leftQuaternion[4][4],
                                            GLfloat middleQuaternion[4][4], GLfloat rightQuaternion[4][4]) {
    GLfloat tempQ[4][4] ={};
    GLfloat crossProduct[3];
    int i;
    for (i = 0; i < 4; i++){
        tempQ[i][0] = middleQuaternion[i][0]*rightQuaternion[i][0] - (middleQuaternion[i][1]*rightQuaternion[i][1] +
                middleQuaternion[i][2]*rightQuaternion[i][2] + middleQuaternion[i][3]*rightQuaternion[i][3]);

        crossProduct[0] = middleQuaternion[i][2]*rightQuaternion[i][3] - middleQuaternion[i][3]*rightQuaternion[i][2];
        crossProduct[1] = middleQuaternion[i][3]*rightQuaternion[i][1] - middleQuaternion[i][1]*rightQuaternion[i][3];
        crossProduct[2] = middleQuaternion[i][1]*rightQuaternion[i][2] - middleQuaternion[i][2]*rightQuaternion[i][1];

        tempQ[i][1] = middleQuaternion[i][0]*rightQuaternion[i][1] + middleQuaternion[i][1]*rightQuaternion[i][0]
                      + crossProduct[0];
        tempQ[i][2] = middleQuaternion[i][0]*rightQuaternion[i][2] + middleQuaternion[i][2]*rightQuaternion[i][0]
                      + crossProduct[1];
        tempQ[i][3] = middleQuaternion[i][0]*rightQuaternion[i][3] + middleQuaternion[i][3]*rightQuaternion[i][0]
                      + crossProduct[2];

        //cout<< "the magnitude of this quaternion is " << getMagnitudeOfQuaternion(tempQ[i])<< endl;
    }

    for (i = 0; i < 4; i++){
        dest[i][0] = leftQuaternion[i][0]*tempQ[i][0] - (leftQuaternion[i][1]*tempQ[i][1] +
                leftQuaternion[i][2]*tempQ[i][2] + leftQuaternion[i][3]*tempQ[i][3]);

        crossProduct[0] = leftQuaternion[i][2]*tempQ[i][3] - leftQuaternion[i][3]*tempQ[i][2];
        crossProduct[1] = leftQuaternion[i][3]*tempQ[i][1] - leftQuaternion[i][1]*tempQ[i][3];
        crossProduct[2] = leftQuaternion[i][1]*tempQ[i][2] - leftQuaternion[i][2]*tempQ[i][1];

        dest[i][1] = leftQuaternion[i][0]*tempQ[i][1] + leftQuaternion[i][1]*tempQ[i][0]
                      + crossProduct[0];
        dest[i][2] = leftQuaternion[i][0]*tempQ[i][2] + leftQuaternion[i][2]*tempQ[i][0]
                      + crossProduct[1];
        dest[i][3] = leftQuaternion[i][0]*tempQ[i][3] + leftQuaternion[i][3]*tempQ[i][0]
                      + crossProduct[2];

        //cout<< "the magnitude of this quaternion is " <<getMagnitudeOfQuaternion(tempQ[i])<< endl;
    }

}
/***
 * This function is called when quaternions need to be normalized after interpolation
 * @param quaternion
 * @return
 */
GLfloat QuaternionConverter::getMagnitudeOfQuaternion(GLfloat quaternion[4]) {
    return (GLfloat)
            sqrt(pow(quaternion[0], 2) + pow(quaternion[1], 2) + pow(quaternion[2], 2) + pow(quaternion[3], 2));
}
