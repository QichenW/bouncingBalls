//
// Created by Qichen on 11/12/16.
//



#include "DrawObjects.h"

const char * DrawObjects::BALL_OBJ_NAME = "soccer_ball.obj";
const char * DrawObjects::WALL_OBJ_NAME= "wall.obj";
int DrawObjects::numberOfObjects;
const int DrawObjects::NUMBER_OF_WALLS = 6;

void DrawObjects::prepareObjects(Object **objects, GLfloat **positions, GLfloat **orientations, int numberOfBalls) {
    DrawObjects::numberOfObjects = numberOfBalls + NUMBER_OF_WALLS;
    int i;
    GLuint wallObjID = SimpleObjLoader::loadObj((char *) BALL_OBJ_NAME, 0, 1.0);

    GLuint ballObjID = SimpleObjLoader::loadObj((char *) WALL_OBJ_NAME, 1, 1.0);

    for (i = 0; i < numberOfObjects; i++){
        if(i < NUMBER_OF_WALLS){
            *(objects + i) = new Object(i,wallObjID, 0, true, *(orientations + i), *(positions + i));
        } else {
            *(objects + i) = new Ball(i,ballObjID, 1, false, *(orientations + i), *(positions + i));
        }
    }

}

void DrawObjects::draw(Object **objects) {
    int i;

    for (i = 0; i < numberOfObjects; i++) {
        glPushMatrix();
        glMultMatrixf(objects[i] -> getFlattenedTransformationMatrix());
        glCallList(objects[i]->getListId());
        glPopMatrix();
    }
}

