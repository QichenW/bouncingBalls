//
// Created by Qichen on 11/12/16.
//

#ifndef BOUNCINGBALLS_OBJECT_H
#define BOUNCINGBALLS_OBJECT_H
#include "matrix/RotationHelper.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

class Object {
public:
    Object(int id, GLuint listId, GLfloat mass, bool isFixed, GLfloat *orientation, GLfloat *translation);

    void setFlattenedTransformationMatrix(GLfloat *flattenedTransformationMatrix);

    GLfloat *getFlattenedTransformationMatrix();

    GLfloat *getTranslation();

    GLuint getListId();

    GLfloat getX();

    GLfloat getY();

    GLfloat getZ();


    bool isFixed;
    GLfloat mass;
    static GLfloat BOTTOM_WALL_Y;
protected:
    int id;
    GLuint listId;
    GLfloat orientation[3]={};  //3
    GLfloat translation[3]={};  //3
    GLfloat flattenedTransformationMatrix[16]={}; //16

};


#endif //BOUNCINGBALLS_OBJECT_H
