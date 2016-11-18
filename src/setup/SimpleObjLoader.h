//
// Created by Qichen on 9/21/16.
//

#ifndef BOUNCINGBALLS_SIMPLEOBJLOADER_H
#define BOUNCINGBALLS_SIMPLEOBJLOADER_H

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
    static GLuint loadObj(char *fileName, GLuint objNo, float scale, bool isQuad, bool hasVt, bool hasVn);

    static void recordObjectAsQuads();

    static void recordObjectAsTrianglesWithNoVt();

    static void recordObjectAsTrianglesWithNoVtNoVn();

    static void recordObjectAsQuadsWithNoVtNoVn();
};

#endif //BOUNCINGBALLS_SIMPLEOBJHEADER_H
