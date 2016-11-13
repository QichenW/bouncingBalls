//
// Created by Qichen on 11/12/16.
//



#include "DrawObjects.h"

const char * DrawObjects::BALL_OBJ_NAME = "soccer_ball.obj";
const char * DrawObjects::WALL_OBJ_NAME= "wall.obj";
int DrawObjects::numberOfObjects;
const int DrawObjects::NUMBER_OF_WALLS = 6;



void DrawObjects::draw(Object **objects) {
    int i;

    for (i = 0; i < numberOfObjects; i++) {
        glPushMatrix();
        glMultMatrixf(objects[i] -> getFlattenedTransformationMatrix());
        glCallList(objects[i]->getListId());
        glPopMatrix();
    }
}

//TODO test this
/***
 *  called in upserInputManager, when input file is loaded in to prefs, initiate **object
 * @param pPrefs
 * @param pObjects
 */
void DrawObjects::prepareObjects(PhysicsPrefs *pPrefs, Object **pObjects) {
    DrawObjects::numberOfObjects = pPrefs->numberOfObjects;
    int i;
    GLfloat **orientations,**positions,** velocities, ** angularVelos;

    GLuint wallObjID = SimpleObjLoader::loadObj((char *) BALL_OBJ_NAME, 0, 1.0);

    GLuint ballObjID = SimpleObjLoader::loadObj((char *) WALL_OBJ_NAME, 1, 1.0);

    orientations = pPrefs->listOfEulerAngle;
    positions = pPrefs->listOfPositions;
    velocities = pPrefs->listOfVelocity;
    angularVelos = pPrefs->listOfAngularVelo;

    for (i = 0; i < numberOfObjects; i++){
        if(i < NUMBER_OF_WALLS){
            *(pObjects + i) = new Object(i,wallObjID, 0, true, *(orientations + i), *(positions + i));
        } else {
            *(pObjects + i) = new Ball(i,ballObjID, 1, false, *(orientations + i), *(positions + i),
                                      *(velocities + i - NUMBER_OF_WALLS), *(angularVelos + i - NUMBER_OF_WALLS));
        }
    }

}
