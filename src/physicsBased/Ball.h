//
// Created by Qichen on 11/12/16.
//

#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H
#include "Object.h"
#include "Geometry.h"
#include "matrix/RotationHelper.h"
#include <cstdlib>
#if defined(__APPLE__)
#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

class Ball: public Object {
public:

    Ball(int oId, int lId, GLfloat om, bool isF, GLfloat *orienttn, GLfloat *translatn, GLfloat *velocity,
             GLfloat *angularVelocity, GLfloat r);

    void updateAcclrtn();

    void updateFlattenedTransformationMatrix(GLfloat t);

    GLfloat radius;

    GLfloat getVelocityIn(const int direction);
    GLfloat velocity[3];
    GLfloat directionOfCollision[3];
    GLfloat angluarVelo[3];

    void forceStopIfSlowOnFloor();

private:

    GLfloat acceleration[3];
    GLfloat angularAcclrtn[3];
    //TODO this is not useful
    GLfloat unitTravelDirection[3];

    static const GLfloat THRESHOLD;
    static const GLfloat FRICTION;
    static const GLfloat GRAVITY[3];
    static const int X_DIRECTION;
    static const int Y_DIRECTION;
    static const int Z_DIRECTION;


    void setUnitTravelDirection();

};

#endif //BOUNCINGBALLS_BALL_H
