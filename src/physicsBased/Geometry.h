//
// Created by Qichen on 11/13/16.
//

#ifndef BOUNCINGBALLS_GEOMETRY_H
#define BOUNCINGBALLS_GEOMETRY_H

#include "Object.h"
#include "Ball.h"
#include "matrix/RotationHelper.h"
#include <cmath>
#if defined(__APPLE__)
#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

class Geometry {

public:
    static GLfloat getDistance(GLfloat *pos1, GLfloat *pos2);

    static void getUnitDirection(GLfloat *des, GLfloat *src);

    static bool isZeroVector(GLfloat *v);
};


#endif //BOUNCINGBALLS_GEOMETRY_H
