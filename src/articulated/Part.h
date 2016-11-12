//
// Created by Qichen on 10/14/16.
//

#ifndef ANIMATIONS_PART_H
#define ANIMATIONS_PART_H
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>

#else
#include <GL/glut.h>
#endif
using namespace std;

class Part {
public:
    Part(GLuint id, GLuint listID, GLfloat *fat, GLfloat *sat, Part * p);

private:
    int objectID;


public:
    void setLocalRotation(GLfloat *lr);

    void setLocalTranslation(GLfloat *lt);

    void setCombinedTransitions(GLfloat *t);
    Part * parent;
    GLfloat combinedTransformation[16];
    GLuint objListID;
    GLfloat localRotation[3];
    GLfloat localTranslation[3] = {0,0,0};

    GLfloat firstAlignFlatMatrix[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    GLfloat secondAlignFlatMatrix[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

};


#endif //ANIMATIONS_PART_H
