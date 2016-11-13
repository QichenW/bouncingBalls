//
// Created by Qichen on 11/12/16.
//

#ifndef BOUNCINGBALLS_BALL_H
#define BOUNCINGBALLS_BALL_H
#include "Object.h"
#include "Geometry.h"
#include "matrix/RotationHelper.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

class Ball: public Object {
public:
    Ball(int id, int listId, GLfloat mass, bool isFixed, GLfloat *orientation,
         GLfloat *translation, GLfloat * velocity, GLfloat * angularVelocity);

    void changeAcceleration(GLfloat *acceleration);

    void changeAngluarAcclrtn(GLfloat *angularAcclrtn);

    void updateAcclrtn();

    void updateFlattenedTransformationMatrix();

    GLfloat radius;

    void reverseVelocity(const int direction, GLfloat ratio);

    GLfloat getVelocityIn(const int direction);

private:
    GLfloat * velocity;
    GLfloat * acceleration;
    GLfloat * angluarVelo;
    GLfloat * angularAcclrtn;
    GLfloat * unitTravelDirection;

    static const GLfloat airFrictionFactor;
    static const GLfloat groundFrictionAcclrtn;
    static const GLfloat GRAVITY[3];
    static const int X_DIRECTION;
    static const int Y_DIRECTION;
    static const int Z_DIRECTION;


    void setUnitTravelDirection();
};


#endif //BOUNCINGBALLS_BALL_H
