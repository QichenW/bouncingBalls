//
// Created by Qichen on 11/13/16.
//

#include "Geometry.h"

/****
 * get the distance bwtween two 3-d positions
 */
GLfloat Geometry::getDistance(GLfloat *pos1, GLfloat *pos2) {
    GLfloat result = 0;
    int i;
    for(i = 0; i < 3; i++){
        result += pow(*(pos1 + i) - *(pos2 + i),2);
    }
    return (GLfloat) sqrtf(result);
}

/***
 * used for getting acceleration caused by friction on groud
 * get the unit vector for a vector; if the vector is {0,0,0}, the unity vector is also {0,0,0}
 */
void Geometry::getUnitDirection(GLfloat *des, GLfloat *src) {
    if(isZeroVector(src)){
        des[0] = des[1] = des[2] = 0;
    } else{
        GLfloat magnitude = sqrtf(powf(src[0],2) + powf(src[1],2) + powf(src[2],2));
        int i;
        for (i = 0; i < 3; i++){
            *(des + i) = *(src + i)/ magnitude;
        }
    }
}

/****
 * get the direction of collision between balls
 * @param d1  where to store the result
 * @param d2  where to store the result
 * @param cSelf centroid of one ball
 * @param cOther  centroid of another ball
 */
void Geometry::getDirectionOfCollision(GLfloat *d1,GLfloat *d2, GLfloat *cSelf, GLfloat *cOther) {
    int i;
    for (i = 0; i < 3; i++) {
        *(d1 + i) = *(cOther + i) - *(cSelf + i);
        *(d2 + i) = *(d1 + i);
    }

}

/****
 * Get the portion of velocity to change in a collision(projection of the velocity to the vector connecting the
 * entroid of two balls)
 * @param des where the result is stored
 * @param from - the velocity vector
 * @param to - the vector connecting two balls
 */
void Geometry::getProjection(GLfloat *des, GLfloat *from,GLfloat *to) {
//TODo test this
    GLfloat magnitudeOfTo = sqrtf(powf(to[0],2) + powf(to[1],2) + powf(to[2],2));
    GLfloat temp = (from[0] * to[0] + from[1] * to[1] + from[2] * to[2])/powf(magnitudeOfTo,2);
    int i;
    for ( i = 0; i < 3; i++){
        *(des + i) = temp *  *(to + i);
    }
}

/***
 * test if a velocity or acceleration is {0,0,0}
 */
bool Geometry::isZeroVector(GLfloat *v) {
    int i;
    for(i = 0; i < 3; i++){
        if (*(v + i) != 0){
            return false;
        }
    }
    return true;
}
