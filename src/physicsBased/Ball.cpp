//
// Created by Qichen on 11/12/16.
//

#include "Ball.h"
const int Ball::X_DIRECTION = 0;
const int Ball::Y_DIRECTION = 1;
const int Ball::Z_DIRECTION = 2;
const GLfloat Ball::GRAVITY[3] = {0, 9.8, 0};
const GLfloat Ball::airFrictionFactor = 0.3; // airFriction is totally related to speed
const GLfloat Ball::groundFrictionAcclrtn = 0.1; // groundFriction is totally related to mass

Ball::Ball(int oId, int lId, GLfloat om, bool isF, GLfloat *orienttn,
     GLfloat *translatn, GLfloat * velocity, GLfloat * angularVelocity)
        :Object(oId, lId, om, isF, orienttn, translatn){ // call the base class constructor first
    int i;
    radius = 2;
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

void Ball::updateFlattenedTransformationMatrix() {

    int i;
    for (i = 0 ; i < 3; i++){
        *(translation + i) += *(velocity + i);
        *(velocity + i) += *(acceleration + i);

        *(orientation + i) += *(angluarVelo + i);
        *(angluarVelo + i) += *(angularAcclrtn + i);
    }

    setFlattenedTransformationMatrix(RotationHelper::
                                     generateFlattenedTransformationMatrix(orientation,translation,false));
}

/**
 * Reverse the ball's velocity in one direction due to collision with walls
 * @param i identifies which direction
 * @param ratio the amount of velocity presists
 */
void Ball::reverseVelocity(const int direction, GLfloat ratio) {
    switch (direction){
        case X_DIRECTION:
            *translation *= -1 * ratio;
            break;
        case Y_DIRECTION:
            *(translation + 1) *= -1 * ratio;
            break;
        case Z_DIRECTION:
            *(translation + 2) *= -1 * ratio;
            break;
        default:
            break;
    }

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
    //TODO add ground friction using unit travel direction
 }
}

