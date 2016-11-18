//
// Created by Qichen on 9/22/16.
//

#ifndef BOUNCINGBALLS_MATRIXGENERATOR_H
#define BOUNCINGBALLS_MATRIXGENERATOR_H
// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

class RotationHelper
{
public:
    static float* generateFlattenedTransformationMatrix(float *tuple, float *trip, bool isQuaternion);

private:
    static void getHomogeneousFromEulerAngle(float *eulerAngle);
    static void initTransformationMatrixAsIdentity();

    static void initEulerAngleMatrices(float * matrix1, float * matrix2, float * matrix3);

    static void applyRotation(float rotationMatrix[4][4]);

    static void getHomogeneousFromQuaternion(float *quaternion);
};
#endif //BOUNCINGBALLS_MATRIXGENERATOR_H
