//
// Created by Qichen on 11/12/16.
//

#include "Ball.h"
const int Ball::X_DIRECTION = 0;
const int Ball::Y_DIRECTION = 1;
const int Ball::Z_DIRECTION = 2;
const GLfloat Ball::GRAVITY[3] = {0, -9.8, 0};
const GLfloat Ball::THRESHOLD = 0.5; // when slower that this, stop
const GLfloat Ball::FRICTION = -0.8; // groundFriction is totally related to mass

/**
 *  Ball is a subclass of Object
 * @param oId - id
 * @param lId - polygon list id
 * @param om - mass
 * @param isF - is fixed (should be false)
 * @param orienttn - initial orientation
 * @param translatn - initial translation
 * @param velocity - initial velocity
 * @param angularVelocity - initial angular velocity
 * @param r - radius
 */
Ball::Ball(int oId, int lId, GLfloat om, bool isF, GLfloat *orienttn,
     GLfloat *translatn, GLfloat * velocity, GLfloat * angularVelocity, GLfloat r)
        :Object(oId, lId, om, isF, orienttn, translatn){ // call the base class constructor first
    int i;
    radius = r;
    for (i = 0 ; i < 3; i++){
        *(acceleration + i) = *(GRAVITY + i);
        *(Ball::velocity + i) = *(velocity + i);
        *(Ball::angluarVelo + i) = *(angularVelocity + i);
        *(angularAcclrtn + i) = 0;
        *(directionOfCollision + i) = 0;
    }
    setUnitTravelDirection();
}

/***
 * update translation, rotation, velocity and angular velocity, then get the transformation matrix
 * @param t - delta t
 */
void Ball::updateFlattenedTransformationMatrix(GLfloat t) {
    setUnitTravelDirection();
    updateAcclrtn();
    int i;
    for (i = 0 ; i < 3; i++){
        *(translation + i) += *(velocity + i) * t;
        *(velocity + i) += *(acceleration + i) * t;

        *(orientation + i) += *(angluarVelo + i) * t;
        *(angluarVelo + i) += *(angularAcclrtn + i) * t;
    }

    setFlattenedTransformationMatrix(RotationHelper::
                                     generateFlattenedTransformationMatrix(orientation,translation,false));
}

/**
 * @param direction indicate x or y or z direction
 * @return  the velocity in one direction
 */
GLfloat Ball::getVelocityIn(const int direction) {
    switch (direction){
        case X_DIRECTION:
            return *velocity;
        case Y_DIRECTION:
            return *(velocity + 1);
        case Z_DIRECTION:
            return *(velocity + 2);
        default:
            return 0;
    }
}

/***
 * set unit travel direction, which is used to determine the acceleration caused by friction.
 */
void Ball::setUnitTravelDirection() {
    Geometry::getUnitDirection(unitTravelDirection, velocity);
}

/**
 * update the acceleration for every time instance, if ball is in the air, it has g, if not in the air, it has
 * acceleration caused by friction
 */
void Ball::updateAcclrtn() {
    // if rolling on the bottom wall, there is no acceleration in y direction
 if(*(translation + 1) <= BOTTOM_WALL_Y + radius){
     *(acceleration + 1) = 0; // rolling on the ground
    //add ground friction using unit travel direction
     *acceleration = unitTravelDirection[0] * FRICTION;
     *(acceleration + 2) = unitTravelDirection[2] * FRICTION;
 } else {
     *(acceleration + 1) = *(GRAVITY + 1);
     *acceleration = 0;
     *(acceleration + 2) = 0;
 }
}

/***
 * If the ball is moving slowly on floor,stop it
 */
void Ball::forceStopIfSlowOnFloor() {
    if(*(translation + 1) <= BOTTOM_WALL_Y + radius){
        if (sqrtf(powf(*velocity,2) + powf(*(velocity + 1),2) + powf(*(velocity + 2),2)) < THRESHOLD){
            int i;
            for(i = 0; i < 3; i++){
                *(velocity + i) = 0;
                *(angluarVelo + i) = 0;
                *(acceleration + i) = 0;
            }
        }
    }
}

