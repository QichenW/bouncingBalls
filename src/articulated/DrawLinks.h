//
// Created by Qichen on 11/2/16.
//

#ifndef ANIMATIONS_DRAWLINKS_H
#define ANIMATIONS_DRAWLINKS_H

#include "SimpleObjLoader.h"
#include "setup/Preferences.h"
#include "articulated/Part.h"
#include "matrix/RotationHelper.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class DrawLinks {

public:
    static void prepareLinks(Part **links);

    static void drawLinks(Part **parts, GLfloat * rootQuat, GLfloat * rootTrans, bool isKeyFraming);
};


#endif //ANIMATIONS_DRAWLINKS_H
