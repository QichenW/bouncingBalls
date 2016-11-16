//
// Created by Qichen on 11/12/16.
//

#include "Ball.h"
const int Ball::X_DIRECTION = 0;
const int Ball::Y_DIRECTION = 1;
const int Ball::Z_DIRECTION = 2;
const GLfloat Ball::GRAVITY[3] = {0, -9.8, 0};
const GLfloat Ball::airFrictionFactor = 0.3; // airFriction is totally related to speed
const GLfloat Ball::groundFrictionAcclrtn = 0.1; // groundFriction is totally related to mass

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
    }
    setUnitTravelDirection();
}

void Ball::changeAcceleration(GLfloat *acceleration) {
    int i;
    for (i = 0 ; i < 3; i++){
        *(Ball::acceleration + i) = *(acceleration + i);
    }
}

void Ball::changeAngluarAcclrtn(GLfloat *angularAcclrtn) {
    int i;
    for (i = 0 ; i < 3; i++){
        *(Ball::angularAcclrtn + i) = *(angularAcclrtn + i);
    }
}

void Ball::updateFlattenedTransformationMatrix(GLfloat t) {
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
 * reverse the velocity when there is a collsion.
 * r is set arbitarily to let bouncing stop at some point in time
 * Reverse the ball's velocity in one direction due to collision with walls
 * @param i identifies which direction
 * @param ratio the amount of velocity presists
 */
void Ball::reverseVelocity(GLfloat * veloInOneDirection) {
    GLfloat r;
    if(fabs(*veloInOneDirection) > 30){
        r = 0.9;
    }else if(fabs(*veloInOneDirection) > 14){
        r = 0.7;
    } else if(fabs(*veloInOneDirection) > 4){
        r = 0.5;
    } else {
        r = 0;
    }
    *veloInOneDirection *= -1*r;
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


void Ball::setUnitTravelDirection() {
    Geometry::getUnitDirection(unitTravelDirection, velocity);
}

void Ball::updateAcclrtn() {
    // TODO add air friction using unit travel direction

    // if rolling on the bottom wall, there is ground friction
 if(*(translation + 1) <= BOTTOM_WALL_Y + radius){
     *(acceleration + 1) = 0; // rolling on the ground
    //TODO add ground friction using unit travel direction
 } else {
     *(acceleration + 1) = *(GRAVITY + 1);
 }
}

