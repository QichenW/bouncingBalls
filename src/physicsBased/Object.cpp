//
// Created by Qichen on 11/12/16.
//

#include "Object.h"


GLfloat Object::BOTTOM_WALL_Y;

Object::Object(int id, GLuint listId, GLfloat mass, bool isFixed, GLfloat *orientation, GLfloat *translation) {
    Object::id = id;
    Object::listId = listId;
    Object::mass = mass;
    Object::isFixed = isFixed;

    // set the bottom y of the space
    if(id == 3){
        BOTTOM_WALL_Y = *(translation + 1);
    }

    int i;
    for (i = 0 ; i < 3; i++) {
        *(Object::translation + i) = *(translation + i);
        *(Object::orientation + i) = *(orientation + i);
    }

    setFlattenedTransformationMatrix(RotationHelper::
                                     generateFlattenedTransformationMatrix(orientation,translation,false));

}

void Object::setFlattenedTransformationMatrix(GLfloat *flattenedTransformationMatrix) {
    int i;
    for (i = 0 ; i < 16; i++) {
        *(Object::flattenedTransformationMatrix + i) = *(flattenedTransformationMatrix + i);
    }
}

Object::Object() {}

GLuint Object::getListId() {
    return listId;
}

GLfloat *Object::getFlattenedTransformationMatrix() {
    return flattenedTransformationMatrix;
}

GLfloat *Object::getTranslation() {
    return translation;
}

GLfloat Object::getX() {
    return *translation;
}

GLfloat Object::getY() {
    return *(translation + 1);
}

GLfloat Object::getZ() {
    return *(translation + 2);
}
