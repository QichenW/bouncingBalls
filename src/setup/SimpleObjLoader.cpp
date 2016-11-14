//
// Created by Qichen on 9/21/16.
//

#include "SimpleObjLoader.h"
#include <iostream>

using namespace std;

FILE *filePointer;
char firstWord[16];
vector<GLfloat> vx, vy,vz;

/****
 * The machanism to load an object file is to first while reading throught the .obj file,
 * store the coordinates of vertices and the identifiers of them.
 * Then read through the file again to look for faces (triangles represented by identifiers of vertices),
 * and use the information got from the first round, to create the opengl instructions to draw triangles,
 * and save these instructions in a list, to be later called in main.cpp, when it is ready to plot the object.
 * @param fileName
 * @return identifier of the object
 */
GLuint SimpleObjLoader::loadObj(char *fileName, GLuint objNo, float scale, bool isQuad, bool hasVt, bool hasVn) {

    GLfloat x, y, z;
    GLuint object;
    object = glGenLists(objNo);
    filePointer = fopen(fileName, "r");
    if (!filePointer) {
        printf("can't open file %s\n", fileName);
        exit(1);
    }

    while (1) {
        // read the first word of the line
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "v") == 0) {
            fscanf(filePointer, "%f %f %f", &x, &y, &z);
            // glVertex3f(x, y, z);
            vx.push_back(x*scale);
            vy.push_back(y*scale);
            vz.push_back(z*scale);
        }
    }

    fclose(filePointer);
    filePointer = fopen(fileName, "r");
    glNewList(object, GL_COMPILE);
        glLineWidth(1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // obj files may contain all vectors for rendering or part of them, read them depending on the bool parameters
        if(isQuad) {
            if(hasVt && hasVn) {
                recordObjectAsQuads();
            } else {
                recordObjectAsQuadsWithNoVtNoVn();
            }
        } else {
            if (hasVn){
                recordObjectAsTrianglesWithNoVt();
            } else{
                recordObjectAsTrianglesWithNoVtNoVn();
            }
        }
        vx.clear();
        vy.clear();
        vz.clear();
    glEndList();
    fclose(filePointer);


    return object;
}

/****
 * This function can load a obj file with no texture vector and describing the object in triangles
 */
void SimpleObjLoader::recordObjectAsTrianglesWithNoVt() {
    char dump1, dump2;
    unsigned long vIndex1, vIndex2, vIndex3, vnIndex;
    glBegin(GL_TRIANGLES);
    while (true) {
            // %s ignores /r /0 /n in between lines
            if (fscanf(filePointer, "%s", firstWord) == EOF) {
                break;
            }
            if (strcmp(firstWord, "f") == 0) {

                fscanf(filePointer, "%lu %c %c %lu", &vIndex1, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex2, &dump1, &dump2, &vnIndex);
                fscanf(filePointer, "%lu %c %c %lu", &vIndex3, &dump1, &dump2, &vnIndex);
                glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
                glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
                glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            }
        }
    glEnd();
}

/****
 * This function can load a obj file with no texture vector, no normal vector and describing the object in triangles
 */
void SimpleObjLoader::recordObjectAsTrianglesWithNoVtNoVn() {
    unsigned long vIndex1, vIndex2, vIndex3;
    glBegin(GL_TRIANGLES);
    while (true) {
        // %s ignores /r /0 /n in between lines
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "f") == 0) {

            fscanf(filePointer, "%lu %lu %lu", &vIndex1, &vIndex2, &vIndex3);
            glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
            glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
            glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
        }
    }
    glEnd();
}

/****
 * This function can load a obj file in quadrilaterals
 */
void SimpleObjLoader::recordObjectAsQuads() {
    char dump1, dump2;
    unsigned long vIndex1, vIndex2, vIndex3, vIndex4, vtIndex, vnIndex;
    glBegin(GL_QUADS);
    while (true) {
        // %s ignores /r /0 /n in between lines
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "f") == 0) {

            fscanf(filePointer, "%lu %c %lu %c %lu", &vIndex1, &dump1, &vtIndex, &dump2, &vnIndex);
            fscanf(filePointer, "%lu %c %lu %c %lu", &vIndex2, &dump1, &vtIndex, &dump2, &vnIndex);
            fscanf(filePointer, "%lu %c %lu %c %lu", &vIndex3, &dump1, &vtIndex, &dump2, &vnIndex);
            fscanf(filePointer, "%lu %c %lu %c %lu", &vIndex4, &dump1, &vtIndex, &dump2, &vnIndex);
            glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
            glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
            glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            glVertex3f(vx.at(vIndex4 - 1), vy.at(vIndex4 - 1), vz.at(vIndex4 - 1));
        }
    }
    glEnd();
}

/****
 * This function can load a obj file with no texture vector, no normal vector and describing the object in triangles
 */
void SimpleObjLoader::recordObjectAsQuadsWithNoVtNoVn() {
    unsigned long vIndex1, vIndex2, vIndex3, vIndex4;
    glBegin(GL_QUADS);
    while (true) {
        // %s ignores /r /0 /n in between lines
        if (fscanf(filePointer, "%s", firstWord) == EOF) {
            break;
        }
        if (strcmp(firstWord, "f") == 0) {

            fscanf(filePointer, "%lu %lu %lu %lu", &vIndex1, &vIndex2, &vIndex3, &vIndex4);
            glVertex3f(vx.at(vIndex1 - 1), vy.at(vIndex1 - 1), vz.at(vIndex1 - 1));
            glVertex3f(vx.at(vIndex2 - 1), vy.at(vIndex2 - 1), vz.at(vIndex2 - 1));
            glVertex3f(vx.at(vIndex3 - 1), vy.at(vIndex3 - 1), vz.at(vIndex3 - 1));
            glVertex3f(vx.at(vIndex4 - 1), vy.at(vIndex4 - 1), vz.at(vIndex4 - 1));
        }
    }
    glEnd();
}
