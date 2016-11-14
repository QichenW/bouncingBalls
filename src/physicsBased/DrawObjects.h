//
// Created by Qichen on 11/12/16.
//

#ifndef BOUNCINGBALLS_DRAWOBJECTS_H
#define BOUNCINGBALLS_DRAWOBJECTS_H
#include "Ball.h"
#include "Object.h"
#include "setup/SimpleObjLoader.h"
#include "matrix/RotationHelper.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include "setup/PhysicsPrefs.h"
#include <vector>


#else
#include <GL/glut.h>
#endif

class DrawObjects {
public:
    static void draw(Object **objects);

    static int numberOfObjects;


    static void prepareObjects(PhysicsPrefs *pPrefs, Object **pObjects);

private:
    static const char* BALL_OBJ_NAME;

    static const char *WALL_OBJ_NAME;
    static const int NUMBER_OF_WALLS;
};


#endif //BOUNCINGBALLS_DRAWOBJECTS_H
