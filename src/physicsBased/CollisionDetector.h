//
// Created by Qichen on 11/12/16.
//

#ifndef BOUNCINGBALLS_COLLISIONDETECTOR_H
#define BOUNCINGBALLS_COLLISIONDETECTOR_H


#include "Object.h"
#include "Ball.h"
#include "matrix/RotationHelper.h"
#include "Geometry.h"
#include <cmath>
#if defined(__APPLE__)
#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

class CollisionDetector {
public:
    static void detectAll(Object **all, int numberOfObjects);
    static const int NUMBER_OF_WALLS;

    static const int X_DIRECTION;
    static const int Y_DIRECTION;
    static const int Z_DIRECTION;
    static const GLfloat ratio;
};


#endif //BOUNCINGBALLS_COLLISIONDETECTOR_H
