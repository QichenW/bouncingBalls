//
// Created by Qichen on 10/25/16.
//

#ifndef ANIMATIONS_COEFFICIENTMATRIX_H
#define ANIMATIONS_COEFFICIENTMATRIX_H
// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#include <iostream>

#else
#include <GL/glut.h>
#endif
using namespace std;
class CoefficientMatrices {
private:
    int pos, totalLength;
public:
    bool isEuler;
    GLfloat translation[4][3] ={};
    GLfloat eRotation[4][3] ={};
    GLfloat qRotation[4][4]={};
    CoefficientMatrices * next;

    CoefficientMatrices(bool isEuler, int position, int total);

    void printCurrentCoefficientMatrices();
};


#endif //ANIMATIONS_COEFFICIENTMATRIX_H
