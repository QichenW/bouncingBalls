//
// Created by Qichen on 11/2/16.
//


#include <iostream>
#include "Kinematics.h"

float Kinematics::tInSegment;
GLfloat Kinematics::idleTorsoPos;
GLfloat Kinematics::idleSpeed;
int Kinematics::currentSegment;
GLfloat Kinematics::cubicTimeVector[4];
GLfloat Kinematics::currentRotations[NUMBER_OF_DOF_FOR_NON_TORSO];
GLfloat Kinematics::geometryMatrices[NUMBER_OF_SEGMENT][4][10];
GLfloat Kinematics::coefficientMatrices[NUMBER_OF_SEGMENT][4][10];
float const Kinematics::controlPoints_l_c[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_l_fore[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_l_t[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_l_u[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_r_c[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_r_fore[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_r_t[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_r_u[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_l_foot[NUMBER_OF_SEGMENT];
float const Kinematics::controlPoints_r_foot[NUMBER_OF_SEGMENT];

int const Kinematics::LINK_ID_TO_ROTATION_MAPPING[TOTAL_NUMBER_OF_LINKS];


void Kinematics::setLocalRotation(Part **parts, bool isStraightTrajectory) {

    InterpolationHelper::prepareTimeVector(cubicTimeVector, tInSegment);


    InterpolationHelper::prepare10dVector(currentRotations, cubicTimeVector, coefficientMatrices[currentSegment]);

    int i;

    for (i = 0; i < TOTAL_NUMBER_OF_LINKS; i++){
        if (i ==0 ) {
            if(isStraightTrajectory) {
                /* interpolated trajectory for torso is done in main.cpp */
                continue;
            }
            if (idleSpeed > 0){
                parts[i]->setLocalRotation((GLfloat [3]){0,270,0});
            } else {
                parts[i]->setLocalRotation((GLfloat [3]){0,90,0});
            }
        }else {
            if(LINK_ID_TO_ROTATION_MAPPING[i] < 0) {
                //if the link is not supposed to rotate
                parts[i]->setLocalRotation((GLfloat[3]) {0, 0, 0});
            } else {
                parts[i]->setLocalRotation((GLfloat[3]) {currentRotations[LINK_ID_TO_ROTATION_MAPPING[i]], 0, 0});
            }
        }
    }

    tInSegment += deltaT;
    if(tInSegment >= 1.0) {
        // if one segment ends, "modulus" tInSegment for next segment
        tInSegment -= 1.0;
        currentSegment += 1;
        if(currentSegment == NUMBER_OF_SEGMENT - 1) {
            // go back to the first segment
            currentSegment = 0;
        }
    }
}

/**
 * used only when displaying an idle walking-in-straight-line animation
 * @param torso
 */
void Kinematics::setLocalTranslation(Part *torso) {
    if (idleTorsoPos <= -51 || idleTorsoPos >= 51) {
        idleSpeed *= -1;
    }
    torso->setLocalTranslation((GLfloat [3]){idleTorsoPos+=idleSpeed,0,-50});
}


/**
 * calculated all coeffieient matrices for a cycle of two steps forward,
 * i.e. left leg fully streched then right leg fully streched
 * then store in coefficientMatrices[20][4][10] (there are 20 segments for one cycle)
 */

void Kinematics::calculateAllCoefficientMatrices() {

    initiate();

    float controlPointArray10d[NUMBER_OF_DOF_FOR_NON_TORSO][NUMBER_OF_SEGMENT] = {};
    int i,j,k;
    for ( i = 0; i < NUMBER_OF_DOF_FOR_NON_TORSO; i++) {
        for(j = 0; j < NUMBER_OF_SEGMENT; j++){
            switch (i) {
                case 0:
                    controlPointArray10d[i][j] = controlPoints_l_t[j];
                    break;
                case 1:
                    controlPointArray10d[i][j] = controlPoints_r_t[j];
                    break;
                case 2:
                    controlPointArray10d[i][j] = controlPoints_l_c[j];
                    break;
                case 3:
                    controlPointArray10d[i][j] = controlPoints_r_c[j];
                    break;
                case 4:
                    controlPointArray10d[i][j] = controlPoints_l_u[j];
                    break;
                case 5:
                    controlPointArray10d[i][j] = controlPoints_r_u[j];
                    break;
                case 6:
                    controlPointArray10d[i][j] = controlPoints_l_fore[j];
                    break;
                case 7:
                    controlPointArray10d[i][j] = controlPoints_r_fore[j];
                    break;
                case 8:
                    controlPointArray10d[i][j] = controlPoints_l_foot[j];
                    break;
                case 9:
                    controlPointArray10d[i][j] = controlPoints_r_foot[j];
                    break;
                default:
                    break;
            }
        }
    }
    // first prepare geometryMatrices GLfloat geometryMatrices[20][4][10] = {}
    for (k = 0; k < NUMBER_OF_SEGMENT; k++) {
        cout<<"\n";
        for (i = k; i < k + NUMBER_OF_CONTROL_POINT_FOR_CUBIC; i++) {
            cout<<"\n";
            for (j = 0; j < NUMBER_OF_DOF_FOR_NON_TORSO; j++) {
                geometryMatrices[k][i - k][j] =
                        (i < NUMBER_OF_SEGMENT)
                        ? controlPointArray10d[j][i] : controlPointArray10d[j][i % NUMBER_OF_SEGMENT];

                cout<<geometryMatrices[k][i - k][j]<<"\t";
            }
        }
        cout<<"\n";
    }

    // then prepare all coefficient matrices GLfloat coefficientMatrices[20][4][10] = {}
    for (i = 0; i < NUMBER_OF_SEGMENT; i++) {
        InterpolationHelper::calculate10dCoefficientMatrix(
                coefficientMatrices[i], 0, geometryMatrices[i]);
    }


}

void Kinematics::initiate() {

    // for idle straight line walking only
    idleTorsoPos = 50;
    idleSpeed = (GLfloat) -0.1;

    geometryMatrices[20][4][10] = {};
    coefficientMatrices[20][4][10] = {};
    currentRotations[10] = {};

    tInSegment = 0;
    cubicTimeVector[4] = {};
}
