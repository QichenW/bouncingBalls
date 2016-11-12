//
// Created by Qichen on 9/21/16.
//

#ifndef GLUTPROJECT_SIMPLEOBJLOADER_H
#define GLUTPROJECT_SIMPLEOBJLOADER_H

// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#include <string>
#include <vector>

#else
#include <GL/glut.h>
#endif

class SimpleObjLoader
{
public:
    static GLuint loadObj(char *fileName, int objNo, float scale);

    static void recordObjectAsTrianglesWithNoVt();

    static void recordObjectAsTrianglesWithNoVtNoVn();
};

#endif //GLUTPROJECT_SIMPLEOBJHEADER_H
