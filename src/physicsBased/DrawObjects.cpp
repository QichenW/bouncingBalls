//
// Created by Qichen on 11/12/16.
//



#include <iostream>
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
    unsigned long i;
    int j,k;
    GLfloat defaultScale = 3.0, tempMass;
    vector<GLfloat *> orientations, positions, velocities, angularVelos;

    GLuint wallObjID = SimpleObjLoader::loadObj((char *) WALL_OBJ_NAME, 1, 1.0, true, false, false);

    GLuint sBallObjID = SimpleObjLoader::loadObj((char *) BALL_OBJ_NAME, 2, defaultScale, true, true, true);

    GLuint mBallObjID = SimpleObjLoader::loadObj((char *) BALL_OBJ_NAME, 2, sqrtf(1.5)*defaultScale, true, true, true);

    GLuint lBallObjID = SimpleObjLoader::loadObj((char *) BALL_OBJ_NAME, 2, sqrtf(2.0)*defaultScale, true, true, true);

    orientations = pPrefs->listOfEulerAngle;
    positions = pPrefs->listOfPositions;
    velocities = pPrefs->listOfVelocity;
    angularVelos = pPrefs->listOfAngularVelo;
//TODO test only
    for(i = 0; i < numberOfObjects; i++){
        for(j = 0; j < 3; j++){
            if( i < NUMBER_OF_WALLS){
                cout<<orientations.at(i)[j] << "/" << positions.at(i)[j] << "\t";
            } else {
                cout<<orientations.at(i)[j] << "/" << positions.at(i)[j] << "/"
                    << velocities.at(i - NUMBER_OF_WALLS)[j]<< "/" <<angularVelos.at(i - NUMBER_OF_WALLS)[j]<< "\t";
            }
        }
        cout<<"\n";
    }

    for (k = 0; k < numberOfObjects; k++){
        if(k < NUMBER_OF_WALLS){
            *(pObjects + k) = new Object(k,wallObjID, 0, true, orientations.at(k), positions.at(k));
        } else {
            tempMass = pPrefs->listOfMass.at(k - NUMBER_OF_WALLS);
            if(tempMass<1.48){
                *(pObjects + k) = new Ball(k, sBallObjID, tempMass, false, orientations.at(k), positions.at(k),
                                           velocities .at(k - NUMBER_OF_WALLS), angularVelos.at(k- NUMBER_OF_WALLS),
                                           (GLfloat) (2.4 * defaultScale)); //the radius of the ball in .obj file is 2.4
            } else if(tempMass < 1.98){
                *(pObjects + k) = new Ball(k, mBallObjID, tempMass, false, orientations.at(k), positions.at(k),
                                           velocities .at(k - NUMBER_OF_WALLS), angularVelos.at(k- NUMBER_OF_WALLS),
                                           (GLfloat) (2.4 * sqrtf(tempMass)*  defaultScale));
            } else {
                *(pObjects + k) = new Ball(k, lBallObjID, tempMass, false, orientations.at(k), positions.at(k),
                                           velocities .at(k - NUMBER_OF_WALLS), angularVelos.at(k- NUMBER_OF_WALLS),
                                           (GLfloat) (2.4 * sqrtf(tempMass)*  defaultScale));
            }

        }
    }

}
