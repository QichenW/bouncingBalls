//
// Created by Qichen on 10/14/16.
//

#include <matrix/RotationHelper.h>
#include "Part.h"


GLfloat ZERO_VECTOR[3] = {0,0,0};
void Part::setCombinedTransitions(GLfloat *t) {
    int i ;
    for (i = 0; i < 16; i ++){
        *(combinedTransformation + i) = *(t + i);
    }
}

/**
 *
 * @param id = link id
 * @param listID = the polygon drawing list of this object
 * @param fat = first align translate
 * @param sat = second align translate
 * @param p = parent part
 * @return
 */
Part::Part(GLuint id, GLuint listID, GLfloat *fat, GLfloat *sat, Part * p) {
    objectID = id;
    objListID = listID;
    parent = p;
    float *temp = RotationHelper::generateFlattenedTransformationMatrix(
            (float *) ZERO_VECTOR, fat, false);
    int i;
    for (i = 0; i< 16; i++){
        *(firstAlignFlatMatrix + i) = *(temp+ i);
    }
    temp = RotationHelper::generateFlattenedTransformationMatrix(
            (float *) ZERO_VECTOR, sat, false);
    for (i = 0; i< 16; i++){
        *(secondAlignFlatMatrix + i) = *( temp + i);
    }
}


void Part::setLocalRotation(GLfloat *lr) {
    int i ;
    for (i = 0; i < 3; i ++){
        *(localRotation + i) = *(lr + i);
    }
}

// only torso use this
void Part::setLocalTranslation(GLfloat *lt) {
    int i ;
    for (i = 0; i < 3; i ++){
        *(localTranslation + i) = *(lt + i);
    }
}
