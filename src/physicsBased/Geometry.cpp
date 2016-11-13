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
